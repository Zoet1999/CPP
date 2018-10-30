#include "pch.h"
#include "SeList.h"
#include <iostream>


SeList::SeList()
{
	size_ = 0;//��ʼ��sizeΪ0
}


SeList::~SeList()
{

}

void SeList::Init(int n) {
	/**
	* ��ʼ������
	* @param n int Ҫ�����������
	*/
	for (int i = 0; i < n; i++)
	{
		size_ += 1;
		std::cout << "��" << i + 1 << "���˵�����:";
		std::cin >> L_[i];
		Index_[i] = i + 1;
	}
}
void SeList::Delete(int index) {
	/**
	* ɾ����㺯��
	* @param index int Ҫɾ������±�
	*/
	for (int i = index; i < size_ - 1; i++)
	{
		L_[i] = L_[i + 1];
		Index_[i] = Index_[i + 1];
	}
	size_ -= 1;
}
void SeList::show() {
	/**
	* ��ӡ����˳����������Ԫ��
	*/
	std::cout << "-------" << std::endl;
	for (int i = 0; i < size_; i++)
	{

		std::cout << Index_[i] << "��" << L_[i] << std::endl;
	}
	std::cout << "-------" << std::endl;
}
void SeList::Joseph() {
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
	Init(n);
	int* ans = new int(n);
	int index = 0;
	int j = size_;
	for (int i = 0; i < j; i++)//ѭ��n��ѡ������
	{
		show();
		index += m - 1;
		index = index % size_;//���㱨��m�κ���±�
		ans[i] = Index_[index];
		m = L_[index];
		Delete(index);			//ɾ������m�κ���±�
	}
	for (int i = 0; i < n; i++)
	{
		std::cout << ans[i] << std::endl;
	}
}