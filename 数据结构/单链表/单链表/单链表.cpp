// 单链表.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
typedef struct LNode
{
	int data;
	LNode * next;
}LNode,*LinkList;

bool InitList(LinkList &L);
bool GetElem(LinkList L, int i, int &e);
LinkList LocateElem(LinkList L, int e);
bool ListInsert(LinkList &L, int i, int e);
bool ListDelete(LinkList &L, int i, int e);
void CreateList_H(LinkList &L, int n);
void CreateList_R(LinkList &L, int n);
void MergeList_L(LinkList &LA, LinkList &LB, LinkList &LC);

int main()
{
	LinkList a,b,c;
	CreateList_R(a,3);
	CreateList_R(b, 4);
	InitList(c);
	MergeList_L(a, b, c);
    return 0;
}

bool InitList(LinkList &L)
{
	L = new LNode;//创建头结点
	L->next = 0;//头结点下一位指向空
	return true;
}
bool GetElem(LinkList L, int i, int &e)
{
	LinkList p = L->next;//指向头结点
	int j = 1;
	while (p&&j < i)
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)return false;
	e = p->data;
	return true;
}
LinkList LocateElem(LinkList L, int e)
{
	LinkList p = L->next;
	while (p && p->data != e)
		p = p->next;
	return p;
}
bool ListInsert(LinkList &L, int i, int e)
{
	LinkList p = L;
	int j = 0;
	while (p && (j < i - 1))
	{
		p = p->next; j++;//移到目标位置
	}
	if (!p || j > i - 1)return false;
	LinkList s = new LNode;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}
bool ListDelete(LinkList &L, int i, int e)
{
	LinkList p = L;
	int j = 0;
	while (p && (j < i - 1))
	{
		p = p->next; j++;//移到目标位置
	}
	if (!p || j > i - 1)return false;
	LinkList q = p->next;//为了释放被删除的结点
	p->next =q->next;
	delete q;
	return true;
}
void CreateList_H(LinkList &L, int n)
{
	L = new LNode;
	L->next = 0;
	LinkList p;
	for (int i = 0; i < n; i++)
	{
		p = new LNode;
		std::cin >> p->data;
		p->next = L->next; L->next = p;
	}
}
void CreateList_R(LinkList &L, int n)
{
	L = new LNode;
	L->next = 0;
	LinkList r=L;
	LinkList p;
	for (int i = 0; i < n; i++)
	{
		p = new LNode;
		std::cin >> p->data;
		p->next =NULL; r->next = p;
		r = p;
	}
}
void MergeList_L(LinkList &LA, LinkList &LB, LinkList &LC)
{
	LinkList pa = LA->next, pb = LB->nex;
	LC = LA;
	LinkList pc = LC;
	while (pa&&pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	delete LB;
}
