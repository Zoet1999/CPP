// Lab06_二叉排序树.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

typedef struct {
	int key;
	char info;
}ElemType;

struct BSTNode {
	ElemType data;
	BSTNode* left;
	BSTNode* right;
};
void Search(BSTNode* &T);
BSTNode* SearchBST(BSTNode* &T, int key, int& deep);//查找函数
void printBST(BSTNode* &p, int n);//格式化打印
void  CreatBST(BSTNode* &T);
void Insert(BSTNode* &T);
bool InsertBST(BSTNode* &T, int key);//插入函数
void Delete(BSTNode* &T);
bool DeleteBST(BSTNode* &T, int key);//删除函数
bool in_traversal(BSTNode* &T);//遍历二叉排序树输出
int main()
{
	BSTNode* T=NULL ;
	int choose;
	CreatBST(T);
	while (true) {
		printf("选择操作：1，查找  2，遍历  3，格式化打印  4，插入  5，删除  6，退出：");
		std::cin>>choose;
		switch (choose) {
		case 1:Search(T); break;
		case 2:	printf("遍历结果为："); in_traversal(T);	printf("\n"); break;
		case 3:	printf("以凹入表形式输出：\n"); printBST(T,0); break;
		case 4:Insert(T); break;
		case 5:Delete(T); break;
		case 6:return 0;
		default:printf("输入错误指令，请重新输入\n");
		}
		printf("\n");
	}
}
void  CreatBST(BSTNode* &T) {
	T = NULL;
	printf("请输入插入元素个数：");
	int n, key;

	std::cin >> n;//输入元素个数
	for (int i = 0; i < n; i++) {
		std::cout << "请输入第" << (i + 1) << "个元素:";
		std::cin >> key;//输入元素关键字
		if (!InsertBST(T, key)) {//插入，如果重复，则插入失败
			std::cout << "重复元素，请重新输入\n";
			i--;
		}
	}
}
void Search(BSTNode* &T) {
	int key;
	printf("请输入要查找的元素:");
	std::cin >> key;
	int deep = 1;	
	if (SearchBST(T, key, deep)) {//返回true说明查找成功
		printf("查找成功，查找长度为：%d\n", deep);
	}
	else {
		printf("查找失败\n");
	}
}


BSTNode* SearchBST(BSTNode* &T,int key,int& deep) {
	//key为要查找的关键字，deep记录查找长度
	if ((!T) || key == T->data.key) {//如果相等就返回该结点
		return T;
	}
	else if (key < T->data.key) {//如果目标值小于结点的值，就查找左结点
		return SearchBST(T->left, key,++deep);
	}
	else if (key > T->data.key) {//如果目标值大于结点的值，就查找右结点
		return SearchBST(T->right, key,++deep);
	}
	else if (!T) {//如果结点为NULL，说明查找失败，不存在这个结点。
		return NULL;
	}
}
bool in_traversal(BSTNode* &T) {
	//中序遍历输出
	if (T) {
		in_traversal(T->left);		//遍历左子树
		printf("%d ", T->data.key);	
		in_traversal(T->right);		//遍历右子树
	}
	return true;
}


void printBST(BSTNode* &p, int n){
	//打印二叉树结构，p为当前结点，n为当前结点层数
	if (p == NULL)//如果当前结点为空，直接返回
		return;
	n += 1;//当前结点的层数加一
	std::string ss = "";//初始化画空格的字符串
	for (int i = 0; i < n; i++) {//每层要多画一段字符串
		ss += "    ";
	}
	printBST(p->right, n);//画出右子树
	std::cout << ss.c_str() << p->data.key << std::endl;//画出当前结点
	printBST(p->left, n);//画出左子树
}

void Insert(BSTNode* &T) {
	printf("请输入插入元素个数：");
	int n, key;

	std::cin>>n;//输入元素个数
	for (int i = 0; i < n; i++) {
		std::cout << "请输入第" << (i + 1) << "个元素:";
		std::cin >> key;//输入元素关键字
		if (!InsertBST(T, key)) {//插入，如果重复，则插入失败
			std::cout << "重复元素，请重新输入\n";
			i--;
		}
	}
}

bool InsertBST(BSTNode* &T, int key) {
	//key为要插入结点的关键字
	if (!T) {//如果该结点为NULL，说明到了叶子结点，插入新结点
		BSTNode* S = new BSTNode();
		S->data.key = key;
		S->left = S->right = NULL;
		T = S;
		return true;
	}
	else if(key<T->data.key){//如果要插入的关键字小于当前结点的关键字，则去找左孩子
		return InsertBST(T->left,key);
	}
	else if (key > T->data.key) {//如果要插入的关键字大于当前结点的关键字，则去找右孩子
		return InsertBST(T->right, key);
	}
	else if (key == T->data.key) {//如果相等，说明出现重复元素，返回false
		return false;
	}
	
}

void Delete(BSTNode* &T) {
	int key;
	int deep = 1;
	printf("请输入要删除的元素:");
	std::cin >> key;
	if (SearchBST(T, key,deep)) {
		DeleteBST(T, key);
		printf("删除成功\n");
	}
	else {
		printf("未找到元素，删除失败\n");
	}
}


bool DeleteBST(BSTNode* &T, int key) {
	BSTNode* p = T;
	BSTNode* f = NULL;
	while (p) {//寻找要删除结点的位置
		if (p->data.key == key)//
			break;
		f = p;
		if (p->data.key > key)
			p = p->left;
		else
			p = p->right;
	}
	BSTNode* q = p;
	if ((p->left) && (p->right)) {//如果左右孩子都存在
		BSTNode*s = p->left;
		while (s->right) {//找到左子树的最右结点
			q = s;
			s = s->right;
		}
		p->data = s->data;//把要删除结点的关键字替换成左子树的最右结点的关键字
		if (q != p)//如果要删除结点的左孩子有右孩子
			q->right = s->left;//把左子树的最右结点的左孩子，移到左子树的最右结点原来的位置
		else//如果要删除结点的左孩子没有右孩子
			q->left = s->left;//把左子树的最右结点的左子树，作为要删除结点的左子树
		delete s;//释放删除的结点的空间
		return true;
	}
	else if (!p->right)//如果没有右孩子
		p = p->left;//左孩子移到要删除结点的位置
	else if (!p->left)//如果没有左孩子
		p = p->right;//右孩子移动到要删除结点的位置

	if (!f)//如果头结点就是要删除的结点
		T = p;//头指针指向新的头结点
	else if (q == f->left)//否则如果要删除结点是其父结点的左孩子，把新的结点接到其父结点的左指针上
		f->left = p;
	else f->right = p;//如果要删除结点是其父结点的右孩子，把新的结点接到其父结点的右指针上
	delete q;
	return true;
}
