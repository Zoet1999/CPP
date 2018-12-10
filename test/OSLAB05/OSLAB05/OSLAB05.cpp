// OSLAB05.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <iomanip>

#define ins_num 320

int LRU(int ins[], int page_num);
int FIFO(int ins[], int page_num);
int LFR(int ins[], int page_num);
int OPT(int ins[], int page_num);

int main()
{
	int ins[ins_num];
	for (int i = 0; i < ins_num; i++) {
		ins[i] = 5;
	}

	double hit = LFR(ins, 32);
	double inn = ins_num;
	double percent = hit / inn;
	printf("%f", percent);
	return 0;
}
int LFR(int ins[], int page_num) {
	int pages[400];
	int count[400];
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
				count[i]++;//页命中次数加一
				flag = false;
				hit++;//总命中次数加一
				break;
			}
		}
		if (flag) {//没命中，发生页错误
			int victim = 0;
			int victimCount = count[0];
			for (int j = 1; j < page_num; j++) {//找到计数最大的作为牺牲者
				if (victimCount > count[j])
					victim = j;
			}
			count[victim] = 1;//重置计数
			pages[victim] = ins[i];//替换被选为牺牲者的页
		}
	}

	return hit;//返回击中次数
}

int OPT(int ins[], int page_num) {
	int pages[32];
	int future[32];
	int hit = 0;
	bool flag = true;
	for (int i = 0; i < page_num; i++) {
		pages[i] = -1;
	}
	for (int i = 0; i < ins_num; i++) {
		flag = true;
		for (int j = 0; j < page_num; j++) {
			if (ins[i] == pages[j]) {//命中
				flag = false;
				hit++;//命中次数加一
				break;
			}
		}
		if (flag) {//没命中，发生页错误
			for (int j = 0; j < page_num; j++) {
				flag = true;
				for (int k = i + 1; k < ins_num; k++) {//查找未来第一次遇到的
					if (ins[k] == pages[j]) {
						flag = false;
						future[j] = k;//在未来第几个将会需要这个页
						break;
					}
				}
				if (flag) {
					future[j] = 400;//如果未来不需要这个页，设为一个很大的数
				}
			}
			int victim = 0;
			int victimCount = future[0];
			for (int j = 1; j < page_num; j++) {//找到最晚被需要的页作为牺牲帧
				if (victimCount > future[j])
					victim = j;
			}
			pages[victim] = ins[i];//替换被选为牺牲者的页
		}
	}
	return hit;
}