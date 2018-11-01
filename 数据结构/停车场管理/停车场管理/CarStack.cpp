#include "pch.h"
#include "CarStack.h"


CarStack::CarStack()
{
	InitStack();
}
CarStack::CarStack(int maxsize)
{
	stacksize = maxsize;
	InitStack();
}

CarStack::~CarStack()
{
	DeleteStack();
}

void CarStack::InitStack() {
	base = new CarElem[stacksize+1];
	top = base;
}

void CarStack::DeleteStack() {
	delete base;
}

bool CarStack::Push(int n, int t) {
	if (isFull())
		return false;
	top->number = n;
	top->timeIn = t;
	top++;
	return true;
}

bool CarStack::Pop(int &n,int &t) {
	if (isEmpty()) {
		return false;
	}
	top--;
	n = top->number;
	t = top->timeIn;
		return true ;
}

bool CarStack::Top(int &n, int &t) {
	if (isEmpty()) {
		return false;
	}
	n = (top - 1)->number;
	t = (top - 1)->timeIn;
	return true;
}

bool CarStack::isEmpty() {
	if (top == base) {
		return true;
	}
	else {
		return false;
	}
}
bool CarStack::isFull() {
	if (top - base == stacksize) {
		return true;
	}
	else {
		return false;
	}
}
