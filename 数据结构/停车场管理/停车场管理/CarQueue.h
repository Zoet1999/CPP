#pragma once
#include "CarStack.h"


typedef struct Node
{
	CarElem e;
	Node* next;
}QNode, *QLinkList;

typedef struct
{
	QLinkList front;
	QLinkList rear;
}LinkQueue;

class CarQueue
{
	LinkQueue Q;
public:
	CarQueue();
	~CarQueue();
	bool InitQueue();
	bool EnQueue(int n,int t);
	bool DeQueue(int &n, int &t);
	bool isEmply();
};

