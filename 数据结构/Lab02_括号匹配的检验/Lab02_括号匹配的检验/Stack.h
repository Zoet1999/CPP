#pragma once
typedef struct Node
{
	/*
	������
	*/
	int e;			//�������
	Node* next;		//���ָ��
}SNode, *SLinkList;
class Stack
{
	/*
	ջ��
	*/
	SLinkList Top;//ջ��ָ��
public:
	Stack();
	~Stack();
	void CreateStack(); //��ʼ������
	bool isEmpty();		//�ж��Ƿ�Ϊ��
	void  pop();		//��ջ
	void push(int e);	//��ջ
	int top();			//����ջ��Ԫ��
	void MakeEmpty();	//���ջ
	void DisposeStack();//�ݻ�ջ
};

