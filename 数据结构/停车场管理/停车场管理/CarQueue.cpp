
#include "pch.h"
#include "CarQueue.h"


CarQueue::CarQueue()
{
	InitQueue();
}


CarQueue::~CarQueue()
{
	int a, b;
	while (Q.front != Q.rear)
	{
		DeQueue(a,b);
	}
	delete Q.front;
	
}

bool CarQueue::InitQueue()
{
	Q.front = Q.rear = new QNode;
	Q.front->next = 0;
	return true;
}

bool  CarQueue::EnQueue(int n, int t)
{
	QLinkList p = new QNode;
	p->e.number = n;
	p->e.timeIn = t;
	p->next = 0;
	Q.rear->next = p;
	Q.rear = p;
	return true;
}
bool  CarQueue::DeQueue(int &n, int &t)
{
	if (Q.front == Q.rear)
		return false;
	QLinkList p = Q.front->next;
	n = p->e.number;
	t = p->e.timeIn;
	Q.front->next = p->next;
	if (Q.rear == p)
		Q.rear = Q.front;
	delete p;
	return true;
}

bool CarQueue::isEmply() {
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}
