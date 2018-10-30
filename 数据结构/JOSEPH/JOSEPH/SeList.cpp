#include "pch.h"
#include "SeList.h"
#include <iostream>


SeList::SeList()
{
	size_ = 0;//初始化size为0
}


SeList::~SeList()
{

}

void SeList::Init(int n) {
	/**
	* 初始化插入
	* @param n int 要加入结点的数量
	*/
	for (int i = 0; i < n; i++)
	{
		size_ += 1;
		std::cout << "第" << i + 1 << "个人的密码:";
		std::cin >> L_[i];
		Index_[i] = i + 1;
	}
}
void SeList::Delete(int index) {
	/**
	* 删除结点函数
	* @param index int 要删除结点下标
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
	* 打印现在顺序表里的所有元素
	*/
	std::cout << "-------" << std::endl;
	for (int i = 0; i < size_; i++)
	{

		std::cout << Index_[i] << "：" << L_[i] << std::endl;
	}
	std::cout << "-------" << std::endl;
}
void SeList::Joseph() {
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
	Init(n);
	int* ans = new int(n);
	int index = 0;
	int j = size_;
	for (int i = 0; i < j; i++)//循环n次选择密码
	{
		show();
		index += m - 1;
		index = index % size_;//计算报数m次后的下标
		ans[i] = Index_[index];
		m = L_[index];
		Delete(index);			//删除报数m次后的下标
	}
	for (int i = 0; i < n; i++)
	{
		std::cout << ans[i] << std::endl;
	}
}