#pragma once
typedef struct Node
{
	/*
	链表结点
	*/
	int e;			//保存符号
	Node* next;		//后继指针
}SNode, *SLinkList;
class Stack
{
	/*
	栈类
	*/
	SLinkList Top;//栈顶指针
public:
	Stack();
	~Stack();
	void CreateStack(); //初始化函数
	bool isEmpty();		//判断是否为空
	void  pop();		//出栈
	void push(int e);	//入栈
	int top();			//返回栈顶元素
	void MakeEmpty();	//清空栈
	void DisposeStack();//摧毁栈
};

