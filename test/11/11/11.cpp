// OSLAB05.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <iomanip>

#define ins_num 320


int OPT(int ins[], int page_num);

int main()
{
	int ins[ins_num];
	for (int i = 0; i < ins_num; i++) {
		ins[i] = 5;
	}

	double hit = OPT(ins, 32);
	double inn = ins_num;
	double percent = hit / inn;
	int ans = percent * 100;
	printf("%f",percent);
	return 0;
}
int OPT(int ins[], int page_num) {
	int pages[320];
	int count[320];
	int hit = 0;
	bool flag = true;
	for (int i = 0; i < page_num; i++) {
		pages[i] = -1;
		count[i] = 1;
	}
	for (int i = 0; i < ins_num; i++) {
		flag = true;
		for (int j = 0; j < page_num; j++) {
			if (ins[i] == pages[j]) {//命中
				count[i]++;
				flag = false;
				hit++;
				break;
			}
		}
		if (flag) {//没找到
			int victim = 0;
			int victimCount = count[0];
			for (int j = 1; j < page_num; j++) {
				if (victimCount > count[j])
					victim = j;
			}
			count[victim] = 1;
			pages[victim] = ins[i];
		}
	}

	return hit;
}