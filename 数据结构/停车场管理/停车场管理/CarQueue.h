#pragma once
#include "CarStack.h"


typedef struct Node
{
	CarElem e;//栈信息
	Node* next;//后继指针
}QNode, *QLinkList;

typedef struct
{
	QLinkList front;//队头指针
	QLinkList rear;//队尾指针
}LinkQueue;

class CarQueue
{
	LinkQueue Q;//队列结构体
public:
	CarQueue();
	~CarQueue();
	bool InitQueue();//初始化队列
	bool EnQueue(int n,int t);//入队
	bool DeQueue(int &n, int &t);//出队
	bool isEmply();//判断队列是否为空
};

