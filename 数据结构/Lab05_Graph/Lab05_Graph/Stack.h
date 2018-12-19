#pragma once
typedef struct sNode
{
	int e;
	sNode* next;
}SNode, *SLinkList;
class Stack
{
	SLinkList Top;
public:
	Stack();
	~Stack();
	void CreateStack();
	bool isEmpty();
	void  pop();
	void push(int e);
	int top();
	void MakeEmpty();
	void DisposeStack();
};

