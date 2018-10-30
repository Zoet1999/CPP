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
	* ��ʼ������
	* ��ͷ�ڵ����ռ�
	* һ��ʼû�����ݣ�ͷ�ڵ�ָ����β�ڵ�ָ�붼ָ��ͷ�ڵ�
	*/
	LHead = new LNode;
	LHead->next = LHead;
	LEnd = LHead->next;

	/**
	* ��ʼ������
	* @param n int Ҫ�����������
	*/
	pLinkList L, N;
	L = LEnd;

	for (int i = 0; i < n; i++) {//ѭ��n�Σ�
		N = new LNode;
		L->next = N;
		L = N;
		L->next = LHead;
		std::cout << "��" << i + 1 << "���˵�����:";
		std::cin >> N->data;
		N->index = i + 1;
	}
}
void LinkList::NodeDelete(pLinkList L){
	/**
	* ɾ����㺯��
	* @param L pLinkList Ҫɾ������ǰ�����
	*/
	pLinkList a=L->next;
	L->next = L->next->next;
	delete a;
}

void LinkList::show() {
	/**
	* ��ӡ���������������Ԫ��
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
	* ʵ��Լɪ�򻷺���
	*/
	//��ʼ�� n m ��ÿ���˵�����
	std::cout << "������n��";
	int n;
	std::cin >> n;
	std::cout << "������m��";
	int m;
	std::cin >> m;
	std::cout << "������" << n << "������" << std::endl;
	InitLinkList(n);


	pLinkList L =LHead;//���ڱ���������������L->next
	int* ans = new int(n);//�����洢��
	int no = -1;
	while (LHead!=LHead->next->next)//LHead==LHead->next->nextʱ��������ֻʣ��һ��Ԫ��
	{
		no += 1;//��¼�ǵڼ�������������
		for (int i=0; i < m-1; i++)//�ƶ�m-1�Σ��൱�ڱ���m��
		{
			L = L->next;
			if (L->next == LHead)//ѭ����β��ʱ���ƶ�һ�Σ�����ͷ�ڵ�
			{
				L = L->next;
			}
		}
		ans[no] = L->next->index;
		m = L->next->data;
		NodeDelete(L);				//ɾ��L�ĺ�̽��
		//L->next = L->next->next;
		if (L->next == LHead)//ѭ����β��ʱ���ƶ�һ�Σ�����ͷ�ڵ�
		{
			L = L->next;
		}
		show();
	}
	ans[n - 1] = LHead->next->index;
	for (int i=0;i<n;i++)
	{
		std::cout << ans[i] << std::endl;//��ʾ��
	}
}