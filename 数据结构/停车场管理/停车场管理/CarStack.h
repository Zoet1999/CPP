#pragma once
typedef struct {
	int number;//�����
	int timeIn;//���ʱ������ʱ��
}CarElem;


class CarStack
{
	CarElem* base;//ջ��ָ��
	CarElem* top;//ջ��ָ�룬ָ��ջ��Ԫ�صĺ�һλ
	int stacksize = 0;//ջ�����������
public:
	CarStack();
	CarStack(int);//���캯������ʼ��ջ���飬�����������
	~CarStack();
	void InitStack();//��ʼ��ջ����
	void DeleteStack();//ɾ��ջ����
	bool Push(int n,int t);//��ջ
	bool Pop(int &n, int &t);//��ջ
	bool Top(int &n, int &t);//�õ�ջ��Ԫ��
	bool isEmpty();//�ж��Ƿ�Ϊ��
	bool isFull();//�ж��Ƿ���
};

