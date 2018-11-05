#pragma once
typedef struct {
	int number;//车序号
	int timeIn;//入库时间或入队时间
}CarElem;


class CarStack
{
	CarElem* base;//栈底指针
	CarElem* top;//栈顶指针，指向栈顶元素的后一位
	int stacksize = 0;//栈可用最大容量
public:
	CarStack();
	CarStack(int);//构造函数，初始化栈数组，设置最大容量
	~CarStack();
	void InitStack();//初始化栈数组
	void DeleteStack();//删除栈数组
	bool Push(int n,int t);//入栈
	bool Pop(int &n, int &t);//出栈
	bool Top(int &n, int &t);//得到栈顶元素
	bool isEmpty();//判断是否为空
	bool isFull();//判断是否满
};

