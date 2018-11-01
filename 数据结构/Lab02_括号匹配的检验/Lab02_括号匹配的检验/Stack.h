#pragma once
typedef struct Node
{
	char e;
	Node* next;
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

