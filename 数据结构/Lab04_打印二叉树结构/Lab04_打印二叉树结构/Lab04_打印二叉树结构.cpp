// Lab04_打印二叉树结构.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

struct BiTreeNode {
	char element;
	BiTreeNode* left;
	BiTreeNode* right;
};


BiTreeNode* insert(BiTreeNode* T);

void printTable(BiTreeNode* p, int n);

int main()
{
	BiTreeNode* head = new BiTreeNode();
	head = insert(head);//创建树

	std::cout << "创建完毕\n";
	int n = -1;
	printTable(head, n);//打印表
	return 0;
}




BiTreeNode* insert(BiTreeNode* T) {
	//创建树
	char ch;
	scanf_s("%c", &ch);//读取一个字符
	if (ch == ' ') {//如果为空格，结点置为空
		T = NULL;
	}
	else {//如果不为空
		if (!(T = new BiTreeNode()))//新建结点
		{
			exit(OVERFLOW);
		}
		T->element = ch;			//给结点赋值
		T->left = insert(T->left);	//创建左结点
		T->right = insert(T->right);	//创建右结点
	}
	return T;//返回结点
}

void printTable(BiTreeNode* p, int n)
{
	//打印二叉树结构，p为当前结点，n为当前结点层数
	if (p == NULL)//如果当前结点为空，直接返回
		return;
	n += 1;//当前结点的层数加一
	std::string ss = "";//初始化画空格的字符串
	for (int i = 0; i < n; i++) {//每层要多画一段字符串
		ss += "    ";
	}
	printTable(p->right, n);//画出右子树
	std::cout << ss.c_str() << p->element << std::endl;//画出当前结点
	printTable(p->left, n);//画出左子树
}
