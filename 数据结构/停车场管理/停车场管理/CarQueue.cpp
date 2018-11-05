
#include "pch.h"
#include "CarQueue.h"


CarQueue::CarQueue(){
	InitQueue();
}


CarQueue::~CarQueue(){
	/*
	������������ն��У��ͷſռ�
	*/
	int a, b;
	while (Q.front != Q.rear)//���ϳ��ӣ�ֱ������Ϊ��
	{
		DeQueue(a,b);
	}
	delete Q.front;//�ͷſռ�
	
}

bool CarQueue::InitQueue(){
	/*
	��ʼ������
	*/
	Q.front = Q.rear = new QNode;//��ʼ���ռ�
	Q.front->next = 0;		
	return true;
}

bool  CarQueue::EnQueue(int n, int t){
	/*
	��Ӻ���
	@param n int ���ĺ���
	@param t int �������ʱ��
	*/
	QLinkList p = new QNode;//Ϊ�½�㴴���ռ�
	p->e.number = n;//�����ݸ����½��
	p->e.timeIn = t;
	p->next = 0;	
	Q.rear->next = p;//������β������p
	Q.rear = p;
	return true;
}
bool  CarQueue::DeQueue(int &n, int &t){
	/*
	���Ӻ���
	@param n int ���ĺ���
	@param t int �������ʱ��
	*/
	if (Q.front == Q.rear)//01
		return false;
	QLinkList p = Q.front->next;//ָ��ͷָ�����Ľ�㣬Ҳ���Ƕ�ͷ
	n = p->e.number;
	t = p->e.timeIn;
	Q.front->next = p->next;	//ɾ����ͷ���
	if (Q.rear == p)			//���pΪ��β
		Q.rear = Q.front;		//�Ѷ�βָ��ָ��ͷ���
	delete p;					//�ͷſռ�
	return true;
}
bool CarQueue::isEmply() {
	/*
	�����Ƿ�Ϊ�ն�
	*/
	if (Q.front == Q.rear)//�������Ϊ�շ���true�����򷵻�false
		return true;
	else
		return false;
}
