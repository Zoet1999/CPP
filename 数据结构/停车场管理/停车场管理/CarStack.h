#pragma once
typedef struct {
	int number;//车序号
	int timeIn;//入库时间
}CarElem;


class CarStack
{
	CarElem* base;//栈底指针
	CarElem* top;//栈顶指针
	int stacksize = 0;//栈可用最大容量
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

