
#include "pch.h"
#include "CarQueue.h"


CarQueue::CarQueue(){
	InitQueue();
}


CarQueue::~CarQueue(){
	/*
	析构函数，清空队列，释放空间
	*/
	int a, b;
	while (Q.front != Q.rear)//不断出队，直到队列为空
	{
		DeQueue(a,b);
	}
	delete Q.front;//释放空间
	
}

bool CarQueue::InitQueue(){
	/*
	初始化队列
	*/
	Q.front = Q.rear = new QNode;//初始化空间
	Q.front->next = 0;		
	return true;
}

bool  CarQueue::EnQueue(int n, int t){
	/*
	入队函数
	@param n int 车的号码
	@param t int 车的入队时间
	*/
	QLinkList p = new QNode;//为新结点创建空间
	p->e.number = n;//把数据赋给新结点
	p->e.timeIn = t;
	p->next = 0;	
	Q.rear->next = p;//在链表尾部接上p
	Q.rear = p;
	return true;
}
bool  CarQueue::DeQueue(int &n, int &t){
	/*
	出队函数
	@param n int 车的号码
	@param t int 车的入队时间
	*/
	if (Q.front == Q.rear)//01
		return false;
	QLinkList p = Q.front->next;//指向头指针后面的结点，也就是队头
	n = p->e.number;
	t = p->e.timeIn;
	Q.front->next = p->next;	//删除队头结点
	if (Q.rear == p)			//如果p为队尾
		Q.rear = Q.front;		//把队尾指针指向头结点
	delete p;					//释放空间
	return true;
}
bool CarQueue::isEmply() {
	/*
	返回是否为空队
	*/
	if (Q.front == Q.rear)//如果队列为空返回true，否则返回false
		return true;
	else
		return false;
}
