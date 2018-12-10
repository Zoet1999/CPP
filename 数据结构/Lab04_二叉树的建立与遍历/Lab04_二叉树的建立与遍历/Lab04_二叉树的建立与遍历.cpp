// Lab04_二叉树的建立与遍历.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <stack>

struct BiTreeNode {
	char element;
	BiTreeNode* left;
	BiTreeNode* right;
};


BiTreeNode* insert(BiTreeNode* T);//创建树
bool pre_traversal(BiTreeNode* T);
bool post_traversal(BiTreeNode* T);
bool in_traversal(BiTreeNode* T);
bool pre_traversalE(BiTreeNode* T);
bool post_traversalE(BiTreeNode* T);
bool in_traversalE(BiTreeNode* T);

int main()
{
	BiTreeNode* head=new BiTreeNode();
	head=insert(head);

    std::cout << "创建完毕\n"; 
	std::cout << "先序:";
	pre_traversal(head);
	std::cout << "\n中序:";
	in_traversal(head);
	std::cout << "\n后序:";
    post_traversal(head);
	
	
	
	
	std::cout << "\n\n先序(非递归):";
	pre_traversalE(head);
	std::cout << "\n中序(非递归):";
	in_traversalE(head);
	std::cout << "\n后序(非递归):";
	post_traversalE(head);
	
	
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
		T->left=insert(T->left);	//创建左结点
		T->right=insert(T->right);	//创建右结点
	}
	return T;//返回结点
}
bool post_traversal(BiTreeNode* T) {
	//后序遍历输出
	if (T) {
		post_traversal(T->left);	//遍历左子树
		post_traversal(T->right);	//遍历右子树
		printf("%c", T->element);
	}
	return true;
}
bool pre_traversal(BiTreeNode* T) {
	//前序遍历输出
	if (T) {
		printf("%c", T->element);
		pre_traversal(T->left);		//遍历左子树
		pre_traversal(T->right);	//遍历右子树
	}
	return true;
}
bool in_traversal(BiTreeNode* T) {
	//中序遍历输出
	if (T) {
		in_traversal(T->left);		//遍历左子树
		printf("%c", T->element);
		in_traversal(T->right);		//遍历右子树
	}
 return true;
}


bool post_traversalE(BiTreeNode* T) {
	//后序遍历输出
	std::stack<std::pair<BiTreeNode*, bool>> s;//保存结点的栈，两个元素，第一个为结点，第二个为判断访问次数，false为未被访问过，true为已经被访问过
	s.push(std::pair<BiTreeNode*,bool>(T, false));//压入根结底入栈，设置为第一次访问
	BiTreeNode*p = T;
	bool isvisited;			//记录是否为第二次访问
	while ( s.empty() == 0) {//栈不为空时
		p = s.top().first;				//获得栈顶
		isvisited = s.top().second;
		s.pop();
		if (p == NULL) {//如果栈顶为空结点，进行下一个循环
			continue;
		}
		if (isvisited) {			//如果不为空，且已经被访问过一次，就输出
			printf("%c", p->element);
		}
		else {
			s.push(std::pair<BiTreeNode*, bool>(p, true));		//压入当前元素，标记为已访问过一次
			s.push(std::pair<BiTreeNode*, bool>(p->right, false));//压入右结点，标记为未访问过
			s.push(std::pair<BiTreeNode*, bool>(p->left, false));//压入左结点，标记为未访问过
		}
	}
	return true;
}
bool pre_traversalE(BiTreeNode* T) {
	//前序遍历输出
	std::stack<BiTreeNode*> s;//保存结点的栈
	BiTreeNode*p = T;			//指向树结点的指针
	while (p || s.empty() == 0) {//当结点不为空，或者栈不为空时
		if (p) {					//如果结点不为空，就输出结构，并压入栈，指针指向左结点
			printf("%c", p->element);
			s.push(p);
			p = p->left;
		}
		else {						//否则弹出栈顶元素，指针指向栈顶元素的右结点
			p = s.top();
			s.pop();
			p = p->right;
		}
	}
	return true;
}
bool in_traversalE(BiTreeNode* T) {
	//中序遍历输出
	std::stack<BiTreeNode*> s;//保存结点的栈
	BiTreeNode* p = T;//指向树结点的指针
	while (p || s.empty() == 0) {//当结点不为空，或者栈不为空时
		if (p) {		//如果结点不为空，就压入栈，指针指向左结点
			s.push(p);
			p = p->left;
		}
		else {			//否则弹出栈顶元素，并输出栈顶元素，指针指向栈顶元素的右结点
			p=s.top();
			s.pop();
			printf("%c",p->element);
			p = p->right;
		}
	}
	return true;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
