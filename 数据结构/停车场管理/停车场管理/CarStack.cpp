#include "pch.h"
#include "CarStack.h"


CarStack::CarStack(){
	InitStack();
}
CarStack::CarStack(int maxsize){
	/*
	有参构造函数，初始化栈数组，设置最大容量
	@param maxsize int 设置stack的最大容量
	*/
	stacksize = maxsize;
	InitStack();//初始化栈
}

CarStack::~CarStack(){
	/*
	摧毁栈
	*/
	DeleteStack();
}

void CarStack::InitStack() {
	/*
	初始化栈数组
	*/
	base = new CarElem[stacksize+1];//赋予stacksize+1，最后一位空出来用来判断栈是否满
	top = base;//栈顶指向底部
}

void CarStack::DeleteStack() {
	/*
	释放栈数组，空间
	*/
	delete base;
}

bool CarStack::Push(int n, int t) {
	/*
	入栈
	@param n int 车的号码
	@param t int 车的入库时间
	*/
	if (isFull())//如果满了返回入栈失败
		return false;
	top->number = n;//在栈顶附上数值
	top->timeIn = t;
	top++;//栈顶指针后移
	return true;
}

bool CarStack::Pop(int &n,int &t) {
	/*
	出栈
	@param n int 车的号码
	@param t int 车的入库时间
	*/
	if (isEmpty()) {//如果空了返回出栈失败
		return false;
	}
	top--;//栈顶指针后移
	n = top->number;//输出栈顶数值
	t = top->timeIn;
		return true ;
}

bool CarStack::Top(int &n, int &t) {
	/*
	返回栈顶指针
	@param n int 车的号码
	@param t int 车的入库时间
	*/
	if (isEmpty()) {//如果空了返回出栈失败
		return false;
	}
	n = (top - 1)->number;//输出栈顶数值
	t = (top - 1)->timeIn;
	return true;
}

bool CarStack::isEmpty() {
	/*
	判断是否栈为空
	*/
	if (top == base) {//如果头尾指针相同则为栈空
		return true;
	}
	else {
		return false;
	}
}
bool CarStack::isFull() {
	/*
	判断是否栈为满
	*/
	if (top - base == stacksize) {//如果头尾指针之差为stacksize，则栈为满
		return true;
	}
	else {
		return false;
	}
}
