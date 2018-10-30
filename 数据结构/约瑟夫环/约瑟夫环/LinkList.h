#pragma once

typedef struct LNode
{
	/**
	* data int ����
	* index int �±�
	* next LNode * ���ָ��
	*/
	int data;
	int index;
	LNode * next;
}LNode, *pLinkList;



class LinkList
{
	/**
	*LHead ͷָ��
	*LEnd  βָ��
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

