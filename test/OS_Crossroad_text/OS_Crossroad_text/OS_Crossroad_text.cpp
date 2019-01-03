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
#include<graphics.h>
using namespace std;
#pragma comment(lib, "pthreadVC2.lib")
#define MAX 100
#define PI 3.1415926535
IMAGE white;
IMAGE up, down, leftImage, rightImage;
IMAGE leftImageup, leftImagedown, rightImageup, rightImagedown;

//UI部分
void Initialize() {
	initgraph(960, 640);//设置边框大小
	HRGN rgn = CreateRectRgn(210, 50, 750, 590);
	setcliprgn(rgn);
	/*设置背景色，调用清屏刷新背景*/
	setbkcolor(0xffffff);
	cleardevice();
	float H = 220;		// 色相
	float S = 0.5;		// 饱和度
	float L = 0.7f;		// 亮度

	for (int y = 0; y < 200; y++)
	{
		L += 0.0003f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(0, y, 360, y);
	}

	for (int y = 0; y < 200; y++)
	{
		L += 0.0003f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(600, y, 960, y);
	}

	for (int y = 440; y < 640; y++)
	{
		L += 0.0003f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(0, y, 360, y);
	}

	for (int y = 440; y < 640; y++)
	{
		L += 0.0003f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(600, y, 960, y);
	}
	setlinecolor(BLACK);

	/*四部分的线*/
	moveto(0, 200);
	linerel(360, 0);
	linerel(0, -200);

	moveto(0, 440);
	linerel(360, 0);
	linerel(0, 200);

	moveto(960, 200);
	linerel(-360, 0);
	linerel(0, -200);

	moveto(960, 440);
	linerel(-360, 0);
	linerel(0, 200);

	/*画不同道之间的虚线*/
	setlinestyle(PS_DASH);
	line(0, 260, 360, 260);
	line(600, 260, 960, 260);

	line(0, 380, 360, 380);
	line(600, 380, 960, 380);

	line(420, 0, 420, 200);
	line(420, 440, 420, 640);

	line(540, 0, 540, 200);
	line(540, 440, 540, 640);

	setlinestyle(PS_SOLID);
	line(0, 320, 360, 320);
	line(600, 320, 960, 320);
	line(480, 0, 480, 200);
	line(480, 440, 480, 640);

	loadimage(&white, _T("./pic/white.jpg"));
	loadimage(&leftImage, _T("./pic/left.jpg"));
	loadimage(&rightImage, _T("./pic/right.jpg"));
	loadimage(&up, _T("./pic/up.jpg"));
	loadimage(&down, _T("./pic/down.jpg"));
	loadimage(&leftImageup, _T("./pic/左上.jpg"));
	loadimage(&leftImagedown, _T("./pic/左下.jpg"));
	loadimage(&rightImageup, _T("./pic/右上.jpg"));
	loadimage(&rightImagedown, _T("./pic/右下.jpg"));

}

void lane_one_stop() {
	for (int x = 110; x < 310; x++) {
		putimage(x, 325, &rightImage);
		Sleep(10);
	}
}

void lane_two_stop() {
	for (int x = 110; x < 310; x++) {
		putimage(x, 385, &rightImage);
		Sleep(10);
	}
}

void lane_one_turn_left() {
	for (int x = 310; x < 330; x++) {
		putimage(x, 325, &rightImage);
		Sleep(10);
	}
	putimage(330, 325, &white);
	for (int x = 360; x < 455; x++) {
		putimage(x, 750 - x * 1.2, &rightImageup);
		Sleep(10);
	}

	putimage(455, 204, &white);
	for (int y = 220; y > -50; y--) {
		putimage(490, y, &up);
		Sleep(10);
	}
}

void lane_two_turn_right() {
	for (int x = 310; x < 330; x++) {
		putimage(x, 385, &rightImage);
		Sleep(10);
	}
	putimage(330, 385, &white);
	putimage(360, 385, &rightImagedown);
	Sleep(30);
	putimage(360, 385, &white);
	for (int y = 420; y < 640; y++) {
		putimage(380, y, &down);
		Sleep(10);
	}

}

void lane_two_straight() {
	for (int x = 310; x < 800; x++) {
		putimage(x, 385, &rightImage);
		Sleep(10);
	}
}

void lane_three_stop() {
	for (int y = 640; y > 440; y--) {
		putimage(505, y, &up);
		Sleep(10);
	}
}

void lane_four_stop() {
	for (int y = 640; y > 440; y--) {
		putimage(565, y, &up);
		Sleep(10);
	}
}

void lane_three_turn_left() {
	for (int y = 440; y > 420; y--) {
		putimage(505, y, &up);
		Sleep(10);
	}
	putimage(485, 420, &white);

	for (int x = 485; x > 350; x--) {
		putimage(x, (x + 15) / 1.3, &leftImageup);
		Sleep(10);
	}
	putimage(350, 280, &white);

	for (int x = 310; x > -50; x--) {
		putimage(x, 275, &leftImage);
		Sleep(10);
	}
}

void lane_four_turn_right() {
	for (int y = 440; y > 420; y--) {
		putimage(565, y, &up);
		Sleep(10);
	}
	putimage(545, 420, &white);
	putimage(545, 400, &rightImageup);
	Sleep(30);
	putimage(545, 400, &white);
	for (int x = 590; x < 810; x++) {
		putimage(x, 385, &rightImage);
		Sleep(10);
	}

}

void lane_four_straight() {
	for (int y = 440; y > -50; y--) {
		putimage(565, y, &up);
		Sleep(10);
	}
}

void lane_five_stop() {
	for (int x = 800; x > 600; x--) {
		putimage(x, 265, &leftImage);
		Sleep(10);
	}
}

void lane_six_stop() {
	for (int x = 800; x > 600; x--) {
		putimage(x, 205, &leftImage);
		Sleep(10);
	}
}

void lane_five_turn_left() {
	for (int x = 600; x > 565; x--) {
		putimage(x, 265, &leftImage);
		Sleep(10);
	}
	putimage(565, 265, &white);
	for (int x = 550; x > 435; x--) {
		putimage(x, 815 - x, &leftImagedown);
		Sleep(10);
	}
	putimage(438, 380, &white);
	for (int y = 420; y < 640; y++) {
		putimage(440, y, &down);
		Sleep(10);
	}
}

void lane_six_straight() {
	for (int x = 600; x > 110; x--) {
		putimage(x, 205, &leftImage);
		Sleep(10);
	}
}

void lane_six_turn_right() {
	for (int x = 600; x > 580; x--) {
		putimage(x, 205, &leftImage);
		Sleep(10);
	}
	putimage(580, 205, &white);
	putimage(565, 201, &leftImageup);
	Sleep(50);
	putimage(565, 201, &white);

	for (int y = 190; y > -50; y--) {
		putimage(565, y, &up);
		Sleep(10);
	}
}

void lane_seven_stop() {
	for (int y = -50; y < 150; y++) {
		putimage(440, y, &down);
		Sleep(10);
	}
}

void lane_eight_stop() {
	for (int y = -50; y < 150; y++) {
		putimage(380, y, &down);
		Sleep(10);
	}
}

void lane_seven_turn_left() {
	for (int y = 150; y < 190; y++) {
		putimage(440, y, &down);
		Sleep(10);
	}
	putimage(425, 190, &white);
	for (int x = 430; x < 540; x++) {
		putimage(x, x - 220, &rightImagedown);
		Sleep(10);
	}
	putimage(540, 320, &white);
	for (int x = 600; x < 960; x++) {
		putimage(x, 330, &rightImage);
		Sleep(10);
	}
}

void lane_eight_straight() {
	for (int y = 150; y < 640; y++) {
		putimage(380, y, &down);
		Sleep(10);
	}
}

void lane_eight_turn_right() {
	for (int y = 150; y < 190; y++) {
		putimage(380, y, &down);
		Sleep(10);
	}
	putimage(380, 190, &white);
	putimage(365, 201, &leftImagedown);
	putimage(365, 201, &white);

	for (int x = 360; x > 120; x--) {
		putimage(x, 210, &leftImage);
		Sleep(10);
	}
}

void CarDrive(int carType) {
	switch (carType) {
	case 0:	lane_one_turn_left();
		break;
	case 1: lane_three_turn_left();
		break;
	case 2: lane_five_turn_left();
		break;
	case 3:lane_seven_turn_left();
		break;
	case 4: lane_two_straight();
		break;
	case 5:lane_four_straight();
		break;
	case 6:lane_six_straight();
		break;
	case 7:lane_eight_straight();
		break;
	case 8: lane_two_turn_right();
		break;
	case 9:lane_four_turn_right();
		break;
	case 10:lane_six_turn_right();
		break;
	case 11:lane_eight_turn_right();
		break;
	}
}

void newCar(int roadType) {
	switch (roadType) {
	case 0:lane_one_stop();
		break;
	case 1: lane_three_stop();
		break;
	case 2: lane_five_stop();
		break;
	case 3: lane_seven_stop();
		break;
	case 4:lane_two_stop();
		break;
	case 5: lane_four_stop();
		break;
	case 6: lane_six_stop();
		break;
	case 7: lane_eight_stop();
		break;
	}
}





//多线程通信部分
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
pthread_mutex_t mutex_first[8];
pthread_mutex_t mutex_new;
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
bool leftPriority[4];
pthread_t car[MAX];
struct neighbor {
	int getright(int x) {
		int n = x / 4;
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
void showCount() {
	int all = 0;
	printf("\n                 ");
	for (int i = 0; i < 8; i++) {
		printf("%d   ", road[i].count);
		all += road[i].count;
	}
	printf("		all:%d   ", all);
	printf("\n\n");
}
struct thread_body {
	void toLeft(int carType, int roadType) {
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

			if (is_run[nb.getopp(carType) + 4]) {//对面在直行
				is_block[carType] = true;
				//			printf("左转 东西  car:%d  等待对面直行的车\n", carType);
				pthread_cond_wait(&cond[carType], &mutex[carType]);
				//			printf("左转 东西  car:%d  取消等待对面直行的车，第%d次\n", carType, times);
			}
			is_block[carType] = false;
			pthread_mutex_unlock(&mutex[carType]);

			//开车
			pthread_mutex_lock(&mutex[nb.getopp(carType) + 4]);
			printf("左转 东西~~~car:%d  is going to drive\n", carType);
			CarDrive(carType);
			printf("左转 东西~~~car:%d  has drived out!!!!!!!!!!!!\n", carType);
			pthread_mutex_unlock(&mutex[nb.getopp(carType) + 4]);
			leftPriority[carType % 4] = false;

			//		printf("左转 东西~~~car:%d 东西优先的	锁2\n", carType);
			pthread_mutex_lock(&mutex_ew);
			num_ew--;
			is_run[carType] = false;
			if (num_ew == 0) {
				pthread_mutex_unlock(&mutex_ns);
				//			pthread_cond_broadcast(&cond_ns);
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

			pthread_mutex_lock(&mutex[carType]);
			if (is_run[nb.getopp(carType) + 4]) {//对面在直行
				is_block[carType] = true;
				//			printf("左转 南北  car:%d  等待对面直行的车\n", carType);
				pthread_cond_wait(&cond[carType], &mutex[carType]);
				//			printf("左转 南北  car:%d  取消等待对面直行的车，第%d次\n", carType,times);

			}is_block[carType] = false;
			pthread_mutex_unlock(&mutex[carType]);


			//开车
			pthread_mutex_lock(&mutex[nb.getopp(carType) + 4]);
			printf("左转 南北~~~car:%d  is going to drive\n", carType);
			CarDrive(carType);
			printf("左转 南北~~~car:%d  has drived out!!!!!!!!!!!!\n", carType);
			pthread_mutex_unlock(&mutex[nb.getopp(carType) + 4]);
			leftPriority[carType % 4] = false;


			//		printf("左转 南北~~~car:%d 南北优先的	锁1\n", carType);
			pthread_mutex_lock(&mutex_ns);
			num_ns--;
			is_run[carType] = false;
			if (num_ns == 0) {
				pthread_mutex_unlock(&mutex_ew);
				//			pthread_cond_broadcast(&cond_ew);
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
			//开车
			printf("直行 东西~~~car:%d  is going to drive\n", carType);
			CarDrive(carType);
			printf("直行 东西~~~car:%d  has drived out!!!!!!!!!!!!\n", carType);
			pthread_mutex_unlock(&mutex[carType]);

			if (is_block[nb.getopp(carType) - 4] && road[roadType].count == 1) {
				pthread_cond_signal(&cond[nb.getopp(carType) - 4]);//唤醒对面的左转
				printf("直行 东西~~~car:%d  唤醒对面的左转\n", carType);
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
				//			pthread_cond_broadcast(&cond_ns);
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

			//开车
			pthread_mutex_lock(&mutex[carType]);
			printf("直行 南北~~~car:%d  is going to drive\n", carType);
			CarDrive(carType);
			printf("直行 南北~~~car:%d  has drived out!!!!!!!!!!!!\n", carType);
			pthread_mutex_unlock(&mutex[carType]);
			if (is_block[nb.getopp(carType) - 4] && road[roadType].count == 1) {
				pthread_cond_signal(&cond[nb.getopp(carType) - 4]);//唤醒对面的左转
				printf("直行 东西~~~car:%d  唤醒对面的左转\n", carType);
			}
			if (is_block[nb.getright(carType) + 4] && (road[roadType].count <= 1)) {
				pthread_cond_signal(&cond[nb.getright(carType) + 4]);
				//右边右转等待，且这是本车道最后一辆车时
				//printf("直行 南北~~~car:%d  唤醒右边右转的车\n", carType)；
			}

			//	printf("直行 南北~~~car:%d 南北优先的	锁2\n", carType);
			pthread_mutex_lock(&mutex_ns);
			num_ns--;
			is_run[carType] = false;
			if (num_ns == 0) {
				pthread_mutex_unlock(&mutex_ew);
				//		pthread_cond_broadcast(&cond_ew);
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
		if (is_block[nb.getopp(carType) - 8]) {
			pthread_cond_signal(&cond[nb.getopp(carType) - 8]);//唤醒对面的左转
			printf("直行 南北~~~car:%d  唤醒对面的左转\n", carType);
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
		CarDrive(carType);
		printf("右转~~~car:%d  has drived out!!!!!!!!!!!!\n", carType);
		is_run[carType] = false;
	}
};
thread_body tb;
void *car_thread(void *arg) {

	int carType = *(int*)arg;
	int roadType;
	if (carType >= 8) {
		roadType = carType - 4;
	}
	else
		roadType = carType;

	printf("car:%d  ready to come\n", carType);
	// 新车进入
	Sleep(1000);

	pthread_mutex_lock(&mutex_first[carType]);
	road[roadType].count++;

	if (road[roadType].count > 1) {

		pthread_mutex_unlock(&mutex_first[carType]);
		pthread_mutex_lock(&wait[roadType]);
		printf("car:%d  等待被唤醒\n", carType);
		pthread_cond_wait(&firstCar[roadType], &wait[roadType]);//等待唤醒队首
		printf("car:%d  成功被唤醒\n", carType);
		pthread_mutex_unlock(&wait[roadType]);
	}
	else {
		pthread_mutex_unlock(&mutex_first[carType]);
	}
	newCar(roadType);
	printf("car:%d  has coming!!!!!!\n", carType);
	switch (carType / 4) {
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
	pthread_cond_signal(&firstCar[roadType]);//唤醒队首进程
	return 0;
}


void *come_new_car(void *arg) {
	srand((int)time(0));
	//create the thread
	int i = 0;
	while (true) {
		pthread_mutex_lock(&mutex_new);
		i++;
		int carType = rand() % 16;
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

		Sleep(2000);
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
		pthread_mutex_init(&mutex_first[i], NULL);
	}

	for (int i = 0; i < 4; i++)
		leftPriority[i] = false;
	pthread_mutex_init(&mutex_ns, NULL);
	pthread_mutex_init(&mutex_new, NULL);
	pthread_mutex_init(&mutex_ew, NULL);
	//	pthread_cond_init(&cond_ns, NULL);
	//	pthread_cond_init(&cond_ew, NULL);
}




int main()
{
	Initialize();
	init();
	pthread_t newCar;
	pthread_create(&newCar, NULL, come_new_car, NULL);
	pthread_join(newCar, NULL);
	return 0;
}

