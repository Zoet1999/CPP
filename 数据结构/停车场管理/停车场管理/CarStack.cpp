#include "pch.h"
#include "CarStack.h"


CarStack::CarStack(){
	InitStack();
}
CarStack::CarStack(int maxsize){
	/*
	�вι��캯������ʼ��ջ���飬�����������
	@param maxsize int ����stack���������
	*/
	stacksize = maxsize;
	InitStack();//��ʼ��ջ
}

CarStack::~CarStack(){
	/*
	�ݻ�ջ
	*/
	DeleteStack();
}

void CarStack::InitStack() {
	/*
	��ʼ��ջ����
	*/
	base = new CarElem[stacksize+1];//����stacksize+1�����һλ�ճ��������ж�ջ�Ƿ���
	top = base;//ջ��ָ��ײ�
}

void CarStack::DeleteStack() {
	/*
	�ͷ�ջ���飬�ռ�
	*/
	delete base;
}

bool CarStack::Push(int n, int t) {
	/*
	��ջ
	@param n int ���ĺ���
	@param t int �������ʱ��
	*/
	if (isFull())//������˷�����ջʧ��
		return false;
	top->number = n;//��ջ��������ֵ
	top->timeIn = t;
	top++;//ջ��ָ�����
	return true;
}

bool CarStack::Pop(int &n,int &t) {
	/*
	��ջ
	@param n int ���ĺ���
	@param t int �������ʱ��
	*/
	if (isEmpty()) {//������˷��س�ջʧ��
		return false;
	}
	top--;//ջ��ָ�����
	n = top->number;//���ջ����ֵ
	t = top->timeIn;
		return true ;
}

bool CarStack::Top(int &n, int &t) {
	/*
	����ջ��ָ��
	@param n int ���ĺ���
	@param t int �������ʱ��
	*/
	if (isEmpty()) {//������˷��س�ջʧ��
		return false;
	}
	n = (top - 1)->number;//���ջ����ֵ
	t = (top - 1)->timeIn;
	return true;
}

bool CarStack::isEmpty() {
	/*
	�ж��Ƿ�ջΪ��
	*/
	if (top == base) {//���ͷβָ����ͬ��Ϊջ��
		return true;
	}
	else {
		return false;
	}
}
bool CarStack::isFull() {
	/*
	�ж��Ƿ�ջΪ��
	*/
	if (top - base == stacksize) {//���ͷβָ��֮��Ϊstacksize����ջΪ��
		return true;
	}
	else {
		return false;
	}
}
