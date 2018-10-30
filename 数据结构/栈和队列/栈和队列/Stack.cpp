#include "stdafx.h"
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
{
	Top = new(SNode);
	Top->next = 0;
}
void Stack::DisposeStack()
{
	MakeEmpty();
	delete Top;
}
bool Stack::isEmpty()
{
	if (Top->next == 0)
	{
		return true;
	}
	else
		return false;
}
void Stack::pop()
{
	SLinkList a = Top->next;
	Top->next = a->next;
	delete a;
}
void Stack::push(int e)
{
	SLinkList a = new(SNode);
	a->e = e;
	a->next = Top->next;
	Top->next = a;
}
int Stack::top()
{
	if (!isEmpty())
		return Top->next->e;
	else
	{
		std::cout << "error" << std::endl;
		return 0;
	}
}
void Stack::MakeEmpty()
{
	while (!isEmpty())
	{
		pop();
	}
}