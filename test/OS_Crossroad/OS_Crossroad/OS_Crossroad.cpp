// OS_Crossroad.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<iostream>
#include <pthread.h>
#include <stdio.h>  
#include <io.h>
#include <process.h>
#include <stdlib.h>
#include <string.h>
#include<Windows.h>

using namespace std;
#pragma comment(lib, "pthreadVC2.lib")
#define MAX 100

/*
Car的类型
````左 直行 右
东  0 	 4	 8
南	1	 5	 9
西	2	 6	 10
北	3	 7	 11

Road的类型
````左 直行+右
东	0 	4
南	1 	5
西	2 	6
北	3 	7
*/

struct roadQueue
{
	pthread_t thread[MAX];
	int num[MAX];//the id of the car
	int front;//front pointer
	int rear;//rear pointer

	int count;//the number of car in the queue
	roadQueue() {
		front = rear = count = 0;
	}
	void push(int n) {//push a car at the back with id n
		rear = (rear + 1) % MAX;
		num[rear] = n;
	}
	int pop() {//pop a car in the front,return the car id
		front = (front + 1) % MAX;
		return num[front];
	}

};

roadQueue road[8];
//mutex of the 4 cross//12个互斥变量 
pthread_mutex_t mutex[12];

pthread_mutex_t mutex_new;
pthread_mutex_t mutex_first;
pthread_mutex_t mutex_ns;
pthread_mutex_t mutex_ew;

//mutex of car waiting(in ready queue)
pthread_mutex_t wait[8];
//cond of each road
pthread_cond_t firstCar[8];
pthread_cond_t cond[12];
int num_ns = 0;//
int num_ew = 0;

//if each direction has a car leaving the ready queue /or coming to the first cross
bool is_run[12];
bool is_block[12];
bool is_deadlock = false;
bool leftPriority[4] ;
pthread_t car[MAX];
struct neighbor {
	int getright(int x) {
		int n=x / 4;
		n = ((x - n * 4) + 3) % 4 + n * 4;
		return n;
	}
	int getleft(int x) {
		int n = x / 4;
		n = ((x - n * 4) + 1) % 4 + n * 4;
		return n;
	}
	int getopp(int x) {
		int n = x / 4;
		n = ((x - n * 4) + 2) % 4 + n * 4;
		return n;
	}
};
neighbor nb;
void showCount(){
	printf("\n                 ");
	for (int i = 0; i < 8; i++) {
		printf("%d   ",road[i].count);
	}
	printf("\n\n");
}
struct thread_body {
	void toLeft(int carType,int roadType) {
		if (carType % 4 == 0 || carType % 4 == 2) {//东西方向
	//		printf("左转 东西~~~car:%d 东西优先的	锁1\n", carType);
			pthread_mutex_lock(&mutex_ew);
			if (num_ew == 0) {
				pthread_mutex_lock(&mutex_ns);
	//			printf("左转 东西~~~car:%d 南北优先的	锁\n", carType);

			}num_ew++;
			is_run[carType] = true;
			pthread_mutex_unlock(&mutex_ew);
	//		printf("左转 东西~~~car:%d 东西优先的	解锁1\n", carType);

			//饥饿
			pthread_mutex_lock(&mutex[carType]);
			int times=0;//让步次数
			while (is_run[nb.getopp(carType) + 4]) {//对面在直行
				is_block[carType] = true;
	//			printf("左转 东西  car:%d  等待对面直行的车\n", carType);
				pthread_cond_wait(&cond[carType], &mutex[carType]);
	//			printf("左转 东西  car:%d  取消等待对面直行的车，第%d次\n", carType, times);
				times++;
				if (times>3) {
					leftPriority[carType%4] = true;
					break;
				}
			}
			is_block[carType] = false;
			pthread_mutex_unlock(&mutex[carType]);
			
			//开车
			printf("左转 东西~~~car:%d  is going to drive\n", carType);
			Sleep(2000);
			printf("左转 东西~~~car:%d  has drived out!!!!!!!!!!!!\n", carType);
			leftPriority[carType % 4] = false;

			if (is_block[nb.getopp(carType) + 4]) {
				pthread_cond_signal(&cond[nb.getopp(carType) + 4]);//唤醒对面直行
	//			printf("左转 东西~~~car:%d 唤醒对面直行的车\n", carType);
			}


	//		printf("左转 东西~~~car:%d 东西优先的	锁2\n", carType);
			pthread_mutex_lock(&mutex_ew);
			num_ew--;
			is_run[carType] = false;
			if (num_ew == 0) {
				pthread_mutex_unlock(&mutex_ns);
	//			printf("左转 东西~~~car:%d 南北优先的	解锁\n", carType);
			}
			pthread_mutex_unlock(&mutex_ew);
	//		printf("左转 东西~~~car:%d 东西优先的	解锁2\n", carType);
		}
		else if (carType % 4 == 1 || carType % 4 == 3) {//南北方向
	//		printf("左转 南北~~~car:%d 南北优先的	锁1\n", carType);
			pthread_mutex_lock(&mutex_ns);
			if (num_ns == 0) {
				pthread_mutex_lock(&mutex_ew);
	//			printf("左转 南北~~~car:%d 东西优先的	锁\n", carType);
			}
	//		printf("左转 南北~~~car:%d 南北优先的	解锁1\n", carType);

			num_ns++;
			is_run[carType] = true;
			pthread_mutex_unlock(&mutex_ns);
			
			//饥饿
			pthread_mutex_lock(&mutex[carType]);
			int times = 0;//让步次数
			while (is_run[nb.getopp(carType) + 4]) {//对面在直行
				is_block[carType] = true;
	//			printf("左转 南北  car:%d  等待对面直行的车\n", carType);
				pthread_cond_wait(&cond[carType], &mutex[carType]);
				times++;
	//			printf("左转 南北  car:%d  取消等待对面直行的车，第%d次\n", carType,times);
				if (times > 3) {
					leftPriority[carType % 4] = true;
					break;
				}
			}is_block[carType] = false;
			pthread_mutex_unlock(&mutex[carType]);


			//开车
			printf("左转 南北~~~car:%d  is going to drive\n", carType);
			Sleep(2000);
			printf("左转 南北~~~car:%d  has drived out!!!!!!!!!!!!\n", carType);
			leftPriority[carType % 4] = false;
			//if(is_run[nb.getopp(carType) - 4]) 
			if (is_block[nb.getopp(carType) + 4]) {
			pthread_cond_signal(&cond[nb.getopp(carType) + 4]);//唤醒对面直行
	//		printf("左转 南北~~~car:%d 唤醒对面直行的车\n", carType);
			}

	//		printf("左转 南北~~~car:%d 南北优先的	锁1\n", carType);
			pthread_mutex_lock(&mutex_ns);
			num_ns--;
			is_run[carType] = false;
			if (num_ns == 0) {
				pthread_mutex_unlock(&mutex_ew);
	//			printf("左转 南北~~~car:%d 东西优先的	解锁\n", carType);
			}pthread_mutex_unlock(&mutex_ns);
	//		printf("左转 南北~~~car:%d 南北优先的	解锁1\n", carType);

		}
	}
	void toStraight(int carType, int roadType) {
		if (carType % 4 == 0 || carType % 4 == 2) {//东西方向
	//		printf("直行 东西~~~car:%d 东西优先的	锁1\n", carType);
			pthread_mutex_lock(&mutex_ew);
			if (num_ew == 0) {
				pthread_mutex_lock(&mutex_ns);
	//			printf("直行 东西~~~car:%d 南北优先的	锁\n", carType);
			}
	//		printf("直行 东西~~~car:%d 东西优先的	解锁1\n", carType);
			num_ew++;
			is_run[carType] = true;
			pthread_mutex_unlock(&mutex_ew);
			
			pthread_mutex_lock(&mutex[carType]);
			if (leftPriority[(carType+2)%4]) {//如果对面左转优先
				is_block[carType] = true;
		//		printf("直行 东西  car:%d  等待对面左转优先的车\n", carType);
				pthread_cond_wait(&cond[carType], &mutex[carType]);//等待
		//		printf("直行 东西  car:%d  取消等待对面左转优先的车\n", carType);
				is_block[carType] = false;
			}
			pthread_mutex_unlock(&mutex[carType]);

			//开车
			printf("直行 东西~~~car:%d  is going to drive\n", carType);
			Sleep(2000);
			printf("直行 东西~~~car:%d  has drived out!!!!!!!!!!!!\n", carType);

			if (is_block[nb.getopp(carType) - 4]) {
			pthread_cond_signal(&cond[nb.getopp(carType) - 4]);//唤醒对面的左转
	//		printf("直行 东西~~~car:%d  唤醒对面的左转\n", carType);
			}
			if (is_block[nb.getright(carType) + 4] && (road[roadType].count <= 1)) {
				pthread_cond_signal(&cond[nb.getright(carType) + 4]);
	//			printf("直行 东西~~~car:%d  唤醒右边右转的车\n", carType);

			}
	//		printf("直行 东西~~~car:%d 东西优先的	锁2\n", carType);
			pthread_mutex_lock(&mutex_ew);
			num_ew--;
			is_run[carType] = false;
			if (num_ew == 0) {
				pthread_mutex_unlock(&mutex_ns);
	//			printf("直行 东西~~~car:%d 南北优先的	解锁\n", carType);
			}pthread_mutex_unlock(&mutex_ew);
	//		printf("直行 东西~~~car:%d 东西优先的	解锁2\n", carType);

		}
		else if (carType % 4 == 1 || carType % 4 == 3) {//南北方向
	//		printf("直行 南北~~~car:%d 南北优先的	锁1\n", carType);
			pthread_mutex_lock(&mutex_ns);
			if (num_ns == 0) {
				pthread_mutex_lock(&mutex_ew);
	//			printf("直行 南北~~~car:%d 东西优先的	锁\n", carType);

			}
			num_ns++;
			is_run[carType] = true;
			pthread_mutex_unlock(&mutex_ns);
	//		printf("直行 南北~~~car:%d 南北优先的	解锁1\n", carType);

	//		printf("直行 南北~~~car:%d 左转优先的	锁\n", carType);
			pthread_mutex_lock(&mutex[carType]);
			if (leftPriority[(carType + 2) % 4]) {//如果对面左转优先
				is_block[carType] = true;
	//			printf("直行 南北  car:%d  等待对面左转优先的车\n", carType);
				pthread_cond_wait(&cond[carType], &mutex[carType]);//等待】
	//			printf("直行 南北  car:%d  取消等待对面左转优先的车\n", carType);
				is_block[carType] = false;
			}
			pthread_mutex_unlock(&mutex[carType]);
	//		printf("直行 南北~~~car:%d 左转优先的	解锁\n", carType);

			//开车
			printf("直行 南北~~~car:%d  is going to drive\n", carType);
			Sleep(2000);
			printf("直行 南北~~~car:%d  has drived out!!!!!!!!!!!!\n", carType);

			if (is_block[nb.getopp(carType) - 4]) {
				pthread_cond_signal(&cond[nb.getopp(carType) - 4]);//唤醒对面的左转
	//			printf("直行 南北~~~car:%d  唤醒对面的左转\n", carType);
			}
			if (is_block[nb.getright(carType)+4] &&(road[roadType].count <= 1)) {
				pthread_cond_signal(&cond[nb.getright(carType) + 4]);
	//			printf("直行 南北~~~car:%d  唤醒右边右转的车\n", carType);

			}

		//	printf("直行 南北~~~car:%d 南北优先的	锁2\n", carType);
			pthread_mutex_lock(&mutex_ns);
			num_ns--;
			is_run[carType] = false;
			if (num_ns == 0) {
				pthread_mutex_unlock(&mutex_ew);
		//		printf("直行 南北~~~car:%d 东西优先的	解锁\n", carType);
			}
			pthread_mutex_unlock(&mutex_ns);
		//	printf("直行 南北~~~car:%d 南北优先的	解锁2\n", carType);

		}
	}
	void toRight(int carType, int roadType) {
		is_run[carType] = true;
		if (is_run[nb.getright(carType)]) {//如果右边有右转等待，唤醒它
			pthread_cond_signal(&cond[nb.getright(carType)]);
	//		printf("右转  car:%d  唤醒右边等待的车\n", carType);
		}
	
		if (is_run[nb.getleft(carType) - 4]) {//左边在直行，等待
			is_block[carType] = true;
	//		printf("右转  car:%d  等待左边在直行的车\n", carType);
			pthread_cond_wait(&cond[carType], &mutex[carType]);
	//		printf("右转  car:%d  取消等待左边在直行的车\n", carType);
			is_block[carType] = false;
		}
		//开车
		printf("右转~~~car:%d  is going to drive\n", carType);
		Sleep(2000);
		printf("右转~~~car:%d  has drived out!!!!!!!!!!!!\n", carType);
		is_run[carType] = false;
	}
};
thread_body tb;

void *car_thread(void *arg) {

	int carType = *(int*)arg;
	int roadType;
	if (carType >= 8) {
		roadType = carType-4;
	}
	else
		roadType = carType; 
	
	printf("car:%d  ready to come\n",carType);
	Sleep(2000);
	//newCar(carType)  新车进入
 	pthread_mutex_lock(&mutex_first);
	road[roadType].count++;
	if (road[roadType].count > 1) {
		pthread_mutex_unlock(&mutex_first);
		pthread_mutex_lock(&wait[roadType]);
		printf("car:%d  等待被唤醒\n", carType);
		pthread_cond_wait(&firstCar[roadType], &wait[roadType]);//等待唤醒队首
		printf("car:%d  成功被唤醒\n", carType);
		pthread_mutex_unlock(&wait[roadType]);
	}
	else {
		pthread_mutex_unlock(&mutex_first);
	}
	
	printf("car:%d  has coming!!!!!!\n", carType);
	switch (carType/4) {
	case 0://左转
		tb.toLeft(carType, roadType);
		break;
	case 1://直走
		tb.toStraight(carType, roadType);
		break;
	case 2://右转
		tb.toRight(carType, roadType);
		break; 
	}

	road[roadType].pop();
	road[roadType].count--;
	pthread_cond_signal(&firstCar[roadType]);
	return 0;
}


void *come_new_car(void *arg) {
	srand((int)time(0));
	//create the thread
	int i = 0;
	while (true) {
		pthread_mutex_lock(&mutex_new);
		i++;
		int carType = rand()%16;
		if (carType >= 12) {
			carType -= 12;
		}
		int roadType;
		if (carType >= 8) {
			roadType = carType - 4;
		}
		else
			roadType = carType;

			showCount();

		road[roadType].push(i);

		car[(i) % MAX] = road[roadType].thread[road[roadType].front];
		pthread_create(&road[roadType].thread[road[roadType].front],
				NULL, car_thread, &carType);
	
		Sleep(700);
		pthread_mutex_unlock(&mutex_new);
	}
	
}

void init() {
	for (int i = 0; i < 12; i++) {
		is_run[i] = false;
		is_block[i] = false;
		pthread_cond_init(&cond[i], NULL);
		pthread_mutex_init(&mutex[i], NULL);
	}
	for (int i = 0; i < 8; i++) {
		pthread_cond_init(&firstCar[i], NULL);
		pthread_mutex_init(&wait[i], NULL);
	}
		
	for (int i = 0; i < 4; i++)
		leftPriority[i] = false;
	pthread_mutex_init(&mutex_ns,NULL);
	pthread_mutex_init(&mutex_new, NULL);
	pthread_mutex_init(&mutex_ew,NULL);
	pthread_mutex_init(&mutex_first, NULL);
}


int main()
{
	init();
	pthread_t newCar;
	pthread_create(&newCar, NULL, come_new_car, NULL);
	pthread_join(newCar, NULL);
	return 0;
}

