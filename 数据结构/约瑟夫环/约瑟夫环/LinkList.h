#pragma once

typedef struct LNode
{
	/**
	* data int 密码
	* index int 下标
	* next LNode * 后继指针
	*/
	int data;
	int index;
	LNode * next;
}LNode, *pLinkList;



class LinkList
{
	/**
	*LHead 头指针
	*LEnd  尾指针
	*/
	pLinkList LHead;
	pLinkList LEnd;
public:
	LinkList();
	~LinkList();
	void InitLinkList(int n);
	void NodeDelete(pLinkList L);

	void show();
	
	void Joseph();
};

