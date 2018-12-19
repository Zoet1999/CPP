#pragma once
typedef struct qNode
{
	int e;
	qNode* next;
}QNode, *QLinkList;
typedef struct
{
	QLinkList front;
	QLinkList rear;
}LinkQueue;

class Queue
{
	LinkQueue Q;
public:
	Queue();
	~Queue();
	bool IntiQueue();
	bool EnQueue(int e);
	bool DeQueue(int &e);
	bool isEmpty();
	int GetHead();
};

