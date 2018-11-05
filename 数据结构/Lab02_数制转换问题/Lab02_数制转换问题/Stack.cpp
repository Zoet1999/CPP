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
	  初始化函数
	*/
	Top = new(SNode);
	Top->next = 0;
}
void Stack::DisposeStack()
{
	/*
	  摧毁栈
	*/
	MakeEmpty();
	delete Top;
}
bool Stack::isEmpty()
{
	/*
	判断栈是否为空，如果为空，返回true 否则返回false
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
	出栈,删除栈顶元素
	*/
	SLinkList a = Top->next;
	Top->next = a->next;
	delete a;
}
void Stack::push(int e)
{
	/*
	入栈，把e数据压入栈
	@param e int 要压入的数据
	*/
	SLinkList a = new(SNode);
	a->e = e;
	a->next = Top->next;
	Top->next = a;
}
int Stack::top()
{
	/*
	返回栈顶元素
	@return int 要压入的数据
	*/
	if (!isEmpty())//如果不为空，否则提示错误
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
	清空栈
	*/
	while (!isEmpty())//出栈，直到栈为空
	{
		pop();
	}
}