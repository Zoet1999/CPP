#pragma once
typedef struct Node
{
	int e;
	Node* next;
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
	int QueueLength();
	bool EnQueue(int e);
	bool DeQueue(int &e);
	int GetHead();
};

