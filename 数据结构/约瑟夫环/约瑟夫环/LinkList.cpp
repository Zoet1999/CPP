#include "pch.h"
#include "LinkList.h"
#include <iostream>



LinkList::LinkList()
{
}


LinkList::~LinkList()
{
}

void LinkList::InitLinkList(int n){
	/**
	* 初始化链表
	* 给头节点分配空间
	* 一开始没有数据，头节点指针与尾节点指针都指向头节点
	*/
	LHead = new LNode;
	LHead->next = LHead;
	LEnd = LHead->next;

	/**
	* 初始化插入
	* @param n int 要加入结点的数量
	*/
	pLinkList L, N;
	L = LEnd;

	for (int i = 0; i < n; i++) {//循环n次，
		N = new LNode;
		L->next = N;
		L = N;
		L->next = LHead;
		std::cout << "第" << i + 1 << "个人的密码:";
		std::cin >> N->data;
		N->index = i + 1;
	}
}
void LinkList::NodeDelete(pLinkList L){
	/**
	* 删除结点函数
	* @param L pLinkList 要删除结点的前驱结点
	*/
	pLinkList a=L->next;
	L->next = L->next->next;
	delete a;
}

void LinkList::show() {
	/**
	* 打印现在链表里的所有元素
	*/
	pLinkList  L=LHead;
	std::cout << "-----------" << std::endl;
	while (L->next!=LHead) {
		std::cout << L->next->index << ":" << L->next->data << std::endl;
		L = L->next;
	}
	std::cout << "-----------" << std::endl;
}

void LinkList::Joseph() {
	/**
	* 实现约瑟夫环函数
	*/
	//初始化 n m 和每个人的密码
	std::cout << "请输入n：";
	int n;
	std::cin >> n;
	std::cout << "请输入m：";
	int m;
	std::cin >> m;
	std::cout << "请输入" << n << "个密码" << std::endl;
	InitLinkList(n);


	pLinkList L =LHead;//用于遍历，操作对象是L->next
	int* ans = new int(n);//用来存储答案
	int no = -1;
	while (LHead!=LHead->next->next)//LHead==LHead->next->next时，链表中只剩下一个元素
	{
		no += 1;//记录是第几个读出的密码
		for (int i=0; i < m-1; i++)//移动m-1次，相当于报数m次
		{
			L = L->next;
			if (L->next == LHead)//循环到尾部时多移动一次，跳过头节点
			{
				L = L->next;
			}
		}
		ans[no] = L->next->index;
		m = L->next->data;
		NodeDelete(L);				//删除L的后继结点
		//L->next = L->next->next;
		if (L->next == LHead)//循环到尾部时多移动一次，跳过头节点
		{
			L = L->next;
		}
		show();
	}
	ans[n - 1] = LHead->next->index;
	for (int i=0;i<n;i++)
	{
		std::cout << ans[i] << std::endl;//显示答案
	}
}