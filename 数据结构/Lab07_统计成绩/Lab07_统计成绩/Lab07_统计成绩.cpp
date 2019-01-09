// Lab07_统计成绩.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#define MAXSIZE 100
typedef int KeyType;
typedef struct {
	KeyType key;				//成绩总分关键字数据
	int score[100];				//考试成绩数据
	int number;					//学号
	char name[20];			//名字
	int m;						//考试数量
}RedType;						//数据类型
typedef struct {
	RedType r[MAXSIZE + 1];		//r[0]闲置或用做哨兵
	int length;					//顺序表长度
}SqList;						//顺序表类型

void procTable(SqList& L, int length,int m) {
	//srand(rand());
	//0号位闲置
	L.length = length;
	for (int i = 1; i <= length; i++) {//循环获得学生信息
		std::cout << "请输入第"<<i<<"个学生的"<<std::endl;
		std::cout << "姓名：";
		std::cin >> L.r[i].name;
		std::cout << "学号：";
		std::cin>>L.r[i].number;
		//L.r[i].number = i;
		L.r[i].m = m;
		L.r[i].key = 0;
		std::cout << m << "场考试的成绩：";
		for (int j=0; j < m; j++) {
			std::cin >> L.r[i].score[j];
			//L.r[i].score[j] = rand() % 100;
			L.r[i].key += L.r[i].score[j];
		}
	}
}
void printList(SqList L) {
	int i, j, rank = 0, same=0;;
	L.r[0].key = -1;
	printf("排名  学号 姓名     总分   各科成绩   \n");
	for (i = 1; i <= L.length; i++) {
		if (L.r[i].key == L.r[i - 1].key) {//根据与上一个学生的总分比较，判断排名
			same++;
			rank = i - same;
		}
		else {
			same = 0;
			rank = i;
		}
		printf("%-5d %-5d %-7s %-5d  ",rank,L.r[i].number ,L.r[i].name ,L.r[i].key);
		for (j = 0; j < L.r[i].m; j++) {
			printf("%-5d",L.r[i].score[j]);
		}
		printf("\n");
	}
	
}
SqList SelectionSort(SqList L) {
	//简单选择排序
	int i, j, k;
	RedType t;
	for (i = 1; i < L.length; i++) {		//在L.r[i..L.length]中选择关键字最大的记录
		k = i;
		for (j = i + 1; j <= L.length; j++) {
			if (L.r[j].key > L.r[k].key) {	//k指向此趟排序中关键字最大的记录
				k = j;
			}
		}
		if (k != i) {					//交换r[i]与r[k]
			t = L.r[i];
			L.r[i] = L.r[k];
			L.r[k] = t;
		}
	}
	return L;
}
int main()
{
	SqList L = SqList();
	std::cout << "请输入学生数量：";
	int n;
	std::cin >> n;
	std::cout << "请输入考试数量：";
	int m;
	std::cin >> m;
	procTable(L, n, m);//初始化信息
	printList(SelectionSort(L));//排序并输出
	return 0;
}
