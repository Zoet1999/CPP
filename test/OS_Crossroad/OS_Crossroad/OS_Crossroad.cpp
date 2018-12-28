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



class car {
	int n = 0;
	pthread_mutex_t mutex;

	car(int i) {
		
	}
};

//mutex of the 4 cross//12个互斥变量 
pthread_mutex_t mutex[12];

//mutex of deadlock thread
pthread_mutex_t mutex_e;

//mutex of car waiting(in ready queue)
pthread_mutex_t wait[8];

//mutex of car waiting(in the first cross)
pthread_mutex_t block[8];


//cond when deadlock happen(to wake up the deadlock thread)
pthread_cond_t cond_deadlock;
//cond when deadlock happen(to wake up the car on the right)
pthread_cond_t cond_lock;


typedef enum { west_left, north, south, east }dir_t;
dir_t dir;//indicate the direction of the new car that comes to the cross
int Size = 0;//count the number of car
int Empty;//record the number of empty cross



int current_north;
int current_south;
int current_east;
int current_west;

pthread_t car[MAX];

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

queue car_south_sr;//从南边开来直行或右转的车
queue car_east_sr;
queue car_north_sr;
queue car_west_sr;
queue car_south_l;//从南边开来左转的车
queue car_east_l;
queue car_north_l;
queue car_west_l;


void *car_from_south_(void *arg) {




}



int main()
{

    std::cout << "Hello World!\n"; 
}

