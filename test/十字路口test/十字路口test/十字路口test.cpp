// 十字路口test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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

//mutex of the 4 cross//4个互斥变量 
pthread_mutex_t mutex_a;
pthread_mutex_t mutex_b;
pthread_mutex_t mutex_c;
pthread_mutex_t mutex_d;

//mutex of deadlock thread
pthread_mutex_t mutex_e;

//mutex of car waiting(in ready queue)
pthread_mutex_t wait_east;
pthread_mutex_t wait_west;
pthread_mutex_t wait_north;
pthread_mutex_t wait_south;

//mutex of car waiting(in the first cross)
pthread_mutex_t block_east;
pthread_mutex_t block_west;
pthread_mutex_t block_north;
pthread_mutex_t block_south;

//cond of each direction(in the first cross)
pthread_cond_t cond_w;
pthread_cond_t cond_e;
pthread_cond_t cond_n;
pthread_cond_t cond_s;

//cond of each direction(in the ready queue)
pthread_cond_t firstEast;
pthread_cond_t firstWest;
pthread_cond_t firstSouth;
pthread_cond_t firstNorth;

//cond when deadlock happen(to wake up the deadlock thread)
pthread_cond_t cond_deadlock;
//cond when deadlock happen(to wake up the car on the right)
pthread_cond_t cond_lock;

typedef enum { west, north, south, east }dir_t;
dir_t dir;//indicate the direction of the new car that comes to the cross
int Size = 0;//count the number of car
int Empty;//record the number of empty cross

//indicate the current id of car in each direction
int current_north;
int current_south;
int current_east;
int current_west;

//save all the thread
pthread_t car[MAX];

//a data structure:queue, that descirbes the car in each direction
struct queue
{
	pthread_t thread[MAX];
	int num[MAX];//the id of the car
	int front;//front pointer
	int rear;//rear pointer
	int count;//the number of car in the queue
	queue() {
		front = rear = count = 0;
	}
	void push(int n) {//push a car at the back with id n
		count++;
		rear = (rear + 1) % MAX;
		num[rear] = n;
	}
	int pop() {//pop a car in the front,return the car id
		count--;
		front = (front + 1) % MAX;
		return num[front];
	}
};

//the queue of car
queue car_south;
queue car_east;
queue car_north;
queue car_west;

//if each direction has a car leaving the ready queue /or coming to the first cross
bool is_west;
bool is_south;
bool is_east;
bool is_north;
//if deadlock happens
bool is_deadlock = false;

//wake up all car in the front of the ready queue
void wakeupall()
{
	is_deadlock = false;
	if (car_south.count > 0) {
		current_south = car_south.pop();
		//I think this variable has better be designed as a member variable of the class queue
		//but I am too lazy.
		pthread_cond_signal(&firstSouth);
	}
	if (car_north.count > 0) {
		current_north = car_north.pop();
		pthread_cond_signal(&firstNorth);
	}
	if (car_west.count > 0) {
		current_west = car_west.pop();
		pthread_cond_signal(&firstWest);
	}
	if (car_east.count > 0) {
		current_east = car_east.pop();
		pthread_cond_signal(&firstEast);
	}
}
void *car_from_south(void *arg) {
	//bool deadlock_flag = false;
	//add a wait lock
	pthread_mutex_lock(&wait_south);
	pthread_cond_wait(&firstSouth, &wait_south);
	pthread_mutex_unlock(&wait_south);

	//has come to the cross
	is_south = true;//set is_come to be true
					//add a lock to the cross
	pthread_mutex_lock(&mutex_a);
	printf("car %d from South arrives at crossing\n", current_south);
	//the resource minus 1
	Empty--;
	//indicate current direction
	dir = south;

	bool flag = false;
	//if the resource is used up
	if (Empty == 0) {
		//deadlock happened, send a signal to deadlock thread
		pthread_cond_signal(&cond_deadlock);
		//wait until the deadlock is solved
		pthread_cond_wait(&cond_lock, &mutex_a);

		Sleep(2000);
		pthread_mutex_lock(&mutex_b);
		pthread_mutex_unlock(&mutex_a);
		printf("car %d from South leaves at crossing\n", current_south);
		is_south = false;
		//resource add 1.
		Empty++;
		Sleep(2000);
		pthread_mutex_unlock(&mutex_b);
		wakeupall();
		return NULL;
	}

	//if it find a car on its right
	else if (is_east) {
		//  printf("a car on south's right\n");
		flag = true;
		//it will wait for the car to go first
		pthread_cond_wait(&cond_s, &block_south);
		//the car is gone, remember to call the new car
		//and it is wake up, and find that deadlock happend
		//it has to wake up the left car
		if (is_deadlock) {
			Sleep(2000);
			pthread_mutex_lock(&mutex_b);
			pthread_mutex_unlock(&mutex_a);
			printf("car %d from South leaves at crossing\n", current_south);
			if (dir == west)pthread_cond_signal(&cond_lock);
			else pthread_cond_signal(&cond_w);
			is_south = false;
			//resource add 1.
			Empty++;
			Sleep(2000);
			pthread_mutex_unlock(&mutex_b);
			return NULL;
		}
	}
	Sleep(2000);

	//come to the second cross
	pthread_mutex_lock(&mutex_b);

	//if flag, remember to call
	if (car_east.count > 0 && flag) {
		current_east = car_east.pop();
		pthread_cond_signal(&firstEast);
	}

	//release the lock
	pthread_mutex_unlock(&mutex_a);
	is_south = false;
	//resource add 1.
	Empty++;
	printf("car %d from South leaves at crossing\n", current_south);

	//if a car is waiting on the left, let it go
	//and the waiting car in the queue is waked up by it
	if (is_west)pthread_cond_signal(&cond_w);
	//or it's waked up by itself
	else if (!is_south && car_south.count > 0) {
		current_south = car_south.pop();
		pthread_cond_signal(&firstSouth);
	}
	Sleep(2000);

	//unlock
	pthread_mutex_unlock(&mutex_b);
}
void *car_from_east(void *arg) {
	//add a wait lock
	pthread_mutex_lock(&wait_east);
	pthread_cond_wait(&firstEast, &wait_east);
	pthread_mutex_unlock(&wait_east);
	//has come to the cross
	is_east = true;//setis_come to be true
				   //add a lock to cross
	pthread_mutex_lock(&mutex_b);
	printf("car %d from East arrives at crossing\n", current_east);
	Empty--;
	dir = east;
	bool flag = false;
	if (Empty == 0) {
		pthread_cond_signal(&cond_deadlock);
		pthread_cond_wait(&cond_lock, &mutex_b);

		Sleep(2000);
		pthread_mutex_lock(&mutex_c);
		pthread_mutex_unlock(&mutex_b);
		printf("car %d from East leaves at crossing\n", current_east);
		is_east = false;
		//resource add 1.
		Empty++;
		Sleep(2000);
		pthread_mutex_unlock(&mutex_c);
		wakeupall();
		return NULL;
	}
	// if it find a car on its right
	else if (is_north) {
		flag = true;
		//it will wait for the car to go first
		pthread_cond_wait(&cond_e, &block_east);
		//it will wait for the car to go first

		//the car is gone, remember to call the new car
		//and it is wake up, and find that deadlock happend
		//it has to wake up the left car
		if (is_deadlock) {
			Sleep(2000);
			pthread_mutex_lock(&mutex_c);
			pthread_mutex_unlock(&mutex_b);
			printf("car %d from East leaves at crossing\n", current_east);
			//if it find a car on its left is the deadlock car,wake up it
			if (dir == south)pthread_cond_signal(&cond_lock);
			//otherwise wake up the one on the left
			else pthread_cond_signal(&cond_s);
			is_east = false;
			//resource add 1.
			Empty++;
			Sleep(2000);
			pthread_mutex_unlock(&mutex_c);
			return NULL;
		}
	}

	Sleep(2000);
	//come to the second cross
	pthread_mutex_lock(&mutex_c);

	//if flag, remember to call
	if (!is_north && car_north.count > 0 && flag) {
		current_north = car_north.pop();
		pthread_cond_signal(&firstNorth);
	}

	//release the lock
	Empty++;
	pthread_mutex_unlock(&mutex_b);
	is_south = false;

	printf("car %d from East leaves at crossing\n", current_east);

	if (is_east)pthread_cond_signal(&cond_s);
	else if (!is_east && car_east.count > 0) {
		current_east = car_east.pop();
		pthread_cond_signal(&firstEast);
	}

	Sleep(2000);

	pthread_mutex_unlock(&mutex_c);
}
void *car_from_north(void *arg) {
	//  printf("create north\n");
	//add a wait lock
	pthread_mutex_lock(&wait_north);
	pthread_cond_wait(&firstNorth, &wait_north);
	pthread_mutex_unlock(&wait_north);
	is_north = true;
	pthread_mutex_lock(&mutex_c);
	printf("car %d from North arrives at crossing\n", current_north);
	Empty--;
	dir = north;

	bool flag = false;
	if (Empty == 0) {
		//deadlock happened, send a signal to deadlock thread
		pthread_cond_signal(&cond_deadlock);
		//wait until the deadlock is solved

		pthread_cond_wait(&cond_lock, &mutex_c);

		pthread_cond_signal(&cond_e);
		Sleep(2000);
		pthread_mutex_lock(&mutex_d);
		pthread_mutex_unlock(&mutex_c);
		printf("car %d from West leaves at crossing\n", current_north);
		is_north = false;
		//resource add 1.
		Empty++;
		Sleep(2000);
		pthread_mutex_unlock(&mutex_d);

		wakeupall();
		return NULL;
	}
	//if it find a car on its right
	else if (is_west) {
		// printf("a car on north's right\n");
		flag = true;
		//it will wait for the car to go first
		pthread_cond_wait(&cond_n, &block_north);
		//the car is gone, remember to call the new car
		//and it is wake up, and find that deadlock happend
		//it has to wake up the left car
		if (is_deadlock) {
			Sleep(2000);
			pthread_mutex_lock(&mutex_d);
			pthread_mutex_unlock(&mutex_c);
			printf("car %d from North leaves at crossing\n", current_north);
			if (dir == east)pthread_cond_signal(&cond_lock);
			else pthread_cond_signal(&cond_e);
			is_north = false;
			//resource add 1.
			Empty++;
			Sleep(2000);
			pthread_mutex_unlock(&mutex_d);
			return NULL;
		}
	}
	Sleep(2000);

	pthread_mutex_lock(&mutex_d);
	//if flag, remember to call the right car
	if (car_west.count > 0 && flag) {
		current_west = car_west.pop();
		pthread_cond_signal(&firstWest);
	}

	Empty++;
	pthread_mutex_unlock(&mutex_c);
	is_north = false;
	printf("car %d from North leaves at crossing\n", current_north);

	if (is_east)pthread_cond_signal(&cond_e);
	//or it's waked up by itself
	else if (!is_north && car_north.count > 0) {
		current_north = car_north.pop();
		pthread_cond_signal(&firstNorth);
	}

	Sleep(2000);

	pthread_mutex_unlock(&mutex_d);


}
void *car_from_west(void *arg) {
	//add a wait lock
	pthread_mutex_lock(&wait_west);
	pthread_cond_wait(&firstWest, &wait_west);
	pthread_mutex_unlock(&wait_west);


	//has come to the cross
	is_west = true;//set is_come to be true
	pthread_mutex_lock(&mutex_d);
	printf("car %d from West arrives at crossing\n", current_west);

	//the resource minus 1
	Empty--;
	//indicate current direction
	dir = west;

	bool flag = false;
	//if the resource is used up
	if (Empty == 0) {
		//deadlock happened, send a signal to deadlock thread
		pthread_cond_signal(&cond_deadlock);
		//wait until the deadlock is solved

		pthread_cond_wait(&cond_lock, &mutex_d);
		Sleep(2000);
		pthread_mutex_lock(&mutex_a);
		pthread_mutex_unlock(&mutex_d);
		printf("car %d from West leaves at crossing\n", current_west);
		is_south = false;
		//resource add 1.
		Empty++;
		Sleep(2000);
		pthread_mutex_unlock(&mutex_a);
		wakeupall();
		return NULL;
	}
	//if it find a car on its right
	else if (is_south) {
		flag = true;
		//it will wait for the car to go first

		pthread_cond_wait(&cond_w, &block_west);
		//the car is gone, remember to call the new car
		//and it is wake up, and find that deadlock happend
		//it has to wake up the left car
		if (is_deadlock) {
			Sleep(2000);
			pthread_mutex_lock(&mutex_a);
			pthread_mutex_unlock(&mutex_d);
			printf("car %d from West leaves at crossing\n", current_west);
			if (dir == north)pthread_cond_signal(&cond_lock);
			else pthread_cond_signal(&cond_n);
			is_west = false;
			//resource add 1.
			Empty++;
			Sleep(2000);
			pthread_mutex_unlock(&mutex_a);
			return NULL;
		}
	}
	Sleep(2000);
	//come to the second cross
	pthread_mutex_lock(&mutex_a);

	//if flag, remember to call
	if (!is_north && car_north.count > 0 && flag) {
		current_north = car_north.pop();
		pthread_cond_signal(&firstNorth);
	}

	Empty++;
	pthread_mutex_unlock(&mutex_d);
	is_west = false;

	printf("car %d from West leaves at crossing\n", current_west);
	if (is_north)pthread_cond_signal(&cond_n);
	else if (!is_west && car_west.count > 0) {
		current_west = car_west.pop();
		pthread_cond_signal(&firstWest);
	}

	Sleep(2000);
	pthread_mutex_unlock(&mutex_a);
}

void *check_dead_lock(void *arg) {
	//wait....
	Sleep(4000);
	//at first wake up all the car;
	wakeupall();

	while (1) {
		pthread_mutex_lock(&mutex_e);
		//wait for deadlock
		pthread_cond_wait(&cond_deadlock, &mutex_e);
		//deadlock happen,set is_deadlock true
		is_deadlock = true;
		printf("DEADLOCK: car jam detected, signalling");
		//ask a car to go first,according to the latest car direction.
		switch (dir) {
		case north: {printf(" East "); pthread_cond_signal(&cond_e); break; }
		case east: {printf(" South "); pthread_cond_signal(&cond_s); break; }
		case west: {printf(" North "); pthread_cond_signal(&cond_n); break; }
		case south: {printf(" West "); pthread_cond_signal(&cond_w); break; }
		}
		printf("to go\n");

		pthread_mutex_unlock(&mutex_e);
	}
}

int main(int argc, char** argv) {

	int num[100];

	pthread_t check;//a thread for deadlock checking

	//initialize(it seems that it doesn't matter whether I intialize)
	pthread_cond_init(&cond_lock, NULL);
	pthread_cond_init(&cond_deadlock, NULL);
	pthread_cond_init(&cond_w, NULL);
	pthread_cond_init(&cond_s, NULL);
	pthread_cond_init(&cond_e, NULL);
	pthread_cond_init(&cond_n, NULL);
	pthread_cond_init(&firstEast, NULL);
	pthread_cond_init(&firstWest, NULL);
	pthread_cond_init(&firstSouth, NULL);
	pthread_cond_init(&firstNorth, NULL);

	pthread_mutex_init(&mutex_a, NULL);
	pthread_mutex_init(&mutex_b, NULL);
	pthread_mutex_init(&mutex_c, NULL);
	pthread_mutex_init(&mutex_d, NULL);
	pthread_mutex_init(&mutex_e, NULL);
	pthread_mutex_init(&wait_north, NULL);
	pthread_mutex_init(&wait_south, NULL);
	pthread_mutex_init(&wait_east, NULL);
	pthread_mutex_init(&wait_west, NULL);
	pthread_mutex_init(&block_north, NULL);
	pthread_mutex_init(&block_east, NULL);
	pthread_mutex_init(&block_west, NULL);
	pthread_mutex_init(&block_south, NULL);
	//char s[100];
	//scanf_s("%s", s);
	//printf("%s",s);
	char s[] = "wewesnnsewnsewn";
	printf("%s", s);
	int len = strlen(s);
	printf("%d", len);
	Empty = 4;
	//create the thread
	for (int i = 0; i < len; i++)num[i] = i + 1;
	for (int i = 0; i < len; i++) {
		switch (s[i]) {
		case 'w': {
			is_west = true;
			car_west.push(num[i]);
			car[Size++] = car_west.thread[car_west.front];
			pthread_create(&car_west.thread[car_west.front],
				NULL, car_from_west, NULL);
			break;
		}
		case 'e': {
			is_east = true;
			car_east.push(num[i]);
			car[Size++] = car_east.thread[car_east.front];
			pthread_create(&car_east.thread[car_east.rear],
				NULL, car_from_east, NULL);
			break;
		}
		case 's': {
			is_south = true;
			car_south.push(num[i]);
			car[Size++] = car_south.thread[car_south.rear];
			pthread_create(&car_south.thread[car_south.rear],
				NULL, car_from_south, NULL);
			break;
		}
		case 'n': {
			is_north = true;
			car_north.push(num[i]);
			car[Size++] = car_north.thread[car_north.rear];
			pthread_create(&car_north.thread[car_north.rear],
				NULL, car_from_north, NULL);
			break;
		}
		}
	}




	pthread_create(&check, NULL, check_dead_lock, NULL);
	//join the thread
	for (int i = 0; i < Size; i++) {
		pthread_join(car[i], NULL);
	}
}

