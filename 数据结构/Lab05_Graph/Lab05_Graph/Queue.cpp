#include "pch.h"
#include "Queue.h"


Queue::Queue()
{
	IntiQueue();
}


Queue::~Queue()
{
	int e;
	while (Q.front != Q.rear)
	{
		DeQueue(e);
	}
	delete Q.front;
	delete Q.rear;
}

bool Queue::IntiQueue()
{
	Q.front = Q.rear = new QNode;
	Q.front->next = 0;
	return true;
}

bool  Queue::EnQueue(int e)
{
	QLinkList p = new QNode;
	p->e = e;
	p->next = 0;
	Q.rear->next = p;
	Q.rear = p;
	return true;
}
bool  Queue::DeQueue(int & e)
{
	if (Q.front == Q.rear)
		return false;
	QLinkList p = Q.front->next;
	e = p->e;
	Q.front->next = p->next;
	if (Q.rear == p)
		Q.rear = Q.front;
	delete p;
	return true;
}
int  Queue::GetHead()
{
	if (Q.front != Q.rear)
		return Q.front->next->e;
}
bool Queue::isEmpty() {
	if (Q.front == Q.rear) {
		return true;
	}
	else
		return false;
}

