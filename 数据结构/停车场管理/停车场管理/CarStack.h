#pragma once
typedef struct {
	int number;//�����
	int timeIn;//���ʱ��
}CarElem;


class CarStack
{
	CarElem* base;//ջ��ָ��
	CarElem* top;//ջ��ָ��
	int stacksize = 0;//ջ�����������
public:
	CarStack();
	CarStack(int);
	~CarStack();
	void InitStack();
	void DeleteStack();
	bool Push(int n,int t);
	bool Pop(int &n, int &t);
	bool Top(int &n, int &t);
	bool isEmpty();
	bool isFull();
};

