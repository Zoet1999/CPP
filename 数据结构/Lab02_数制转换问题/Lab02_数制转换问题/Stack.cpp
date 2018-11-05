#include "pch.h"
#include "Stack.h"
#include <iostream>

Stack::Stack()
{
	CreateStack();
}


Stack::~Stack()
{
	DisposeStack();
}

void Stack::CreateStack()
{	/*
	  ��ʼ������
	*/
	Top = new(SNode);
	Top->next = 0;
}
void Stack::DisposeStack()
{
	/*
	  �ݻ�ջ
	*/
	MakeEmpty();
	delete Top;
}
bool Stack::isEmpty()
{
	/*
	�ж�ջ�Ƿ�Ϊ�գ����Ϊ�գ�����true ���򷵻�false
	@return bool
	*/
	if (Top->next == 0)
	{
		return true;
	}
	else
		return false;
}
void Stack::pop()
{
	/*
	��ջ,ɾ��ջ��Ԫ��
	*/
	SLinkList a = Top->next;
	Top->next = a->next;
	delete a;
}
void Stack::push(int e)
{
	/*
	��ջ����e����ѹ��ջ
	@param e int Ҫѹ�������
	*/
	SLinkList a = new(SNode);
	a->e = e;
	a->next = Top->next;
	Top->next = a;
}
int Stack::top()
{
	/*
	����ջ��Ԫ��
	@return int Ҫѹ�������
	*/
	if (!isEmpty())//�����Ϊ�գ�������ʾ����
		return Top->next->e;
	else
	{
		std::cout << "error" << std::endl;
		return 0;
	}
}
void Stack::MakeEmpty()
{
	/*
	���ջ
	*/
	while (!isEmpty())//��ջ��ֱ��ջΪ��
	{
		pop();
	}
}