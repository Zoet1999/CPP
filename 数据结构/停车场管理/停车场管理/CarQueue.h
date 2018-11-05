#pragma once
#include "CarStack.h"


typedef struct Node
{
	CarElem e;//ջ��Ϣ
	Node* next;//���ָ��
}QNode, *QLinkList;

typedef struct
{
	QLinkList front;//��ͷָ��
	QLinkList rear;//��βָ��
}LinkQueue;

class CarQueue
{
	LinkQueue Q;//���нṹ��
public:
	CarQueue();
	~CarQueue();
	bool InitQueue();//��ʼ������
	bool EnQueue(int n,int t);//���
	bool DeQueue(int &n, int &t);//����
	bool isEmply();//�ж϶����Ƿ�Ϊ��
};

