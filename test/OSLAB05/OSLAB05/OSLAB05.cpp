// OSLAB05.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <iomanip>

#define ins_num 320

double LRU(int ins[], int page_num);
double FIFO(int ins[], int page_num);
double LFU(int ins[], int page_num);
double OPT(int ins[], int page_num);
void pageOrder(int ins[320]);

int main()
{
	int ins[ins_num] ;
	pageOrder(ins);	

	for (int n = 4; n <= 32; n++) {
		printf("\n页数目为%d时\n",n);
		printf("LFU: %f\n", LFU(ins, n));
		printf("OPT: %f\n", OPT(ins, n));
		printf("LRU: %f\n", LRU(ins, n));
		printf("FIFO:%f\n", FIFO(ins, n));
	}
	return 0;
}
double LFU(int ins[], int page_num) {
	int pages[400];
	int count[400];
	double hit = 0;
	bool flag = true;
	for (int i = 0; i < page_num; i++) {
		pages[i] = -1;
		count[i] = 0;
	}
	for (int i = 0; i < ins_num; i++) {
		flag = true;
		for (int j = 0; j < page_num; j++) {
			if (ins[i] == pages[j]) {//命中
				//printf("HIT\n");
				count[j]++;//页命中次数加一
				flag = false;
				hit++;//总命中次数加一
				break;
			}
		}
		if (flag) {//没命中，发生页错误
			//printf("MISS\n");
			int victim = 0;
			int victimCount = count[0];
			for (int j = 1; j < page_num; j++) {//找到计数最小的作为牺牲者
				if (victimCount > count[j]) {
					victim = j;
					victimCount = count[j];
				}
			}
			count[victim] = 1;//重置计数
			pages[victim] = ins[i];//替换被选为牺牲者的页
		}
	}
	double inn = ins_num;
	double percent = hit / inn;
	return percent;
}
double OPT(int ins[], int page_num) {
	int pages[32];
	int future[32];
	double hit = 0;
	bool flag = true;
	for (int i = 0; i < page_num; i++) {
		pages[i] = -1;
	}
	for (int i = 0; i < ins_num; i++) {
		flag = true;
		for (int j = 0; j < page_num; j++) {
			if (ins[i] == pages[j]) {//命中
				//printf("HIT\n");
				flag = false;
				hit++;//命中次数加一
				break;
			}
		}
		if (flag) {//没命中，发生页错误
			//printf("MISS\n");
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
				if (victimCount < future[j]) {
					victim = j;
				victimCount = future[j];
				}
			}
			pages[victim] = ins[i];//替换被选为牺牲者的页
		}
	}
	double inn = ins_num;
	double percent = hit / inn;
	return percent;
}
int find(int last[], int e, int page_num) {
	for (int i = 0; i < page_num; i++) {
		if (last[i] == e) {
			return i;
		}
	}
}
int Delete(int last[], int index,int page_num) {
	int temp;
	temp = last[index];
	for (int i = index; i < page_num-1; i++) {
		last[i] = last[i + 1];
	}
	return temp;
}
double LRU(int ins[], int page_num) {
	int pages[32];
	int last[32];//队列顺序队列
	double hit = 0;
	bool flag = true;
	for (int i = 0; i < page_num; i++) {
		pages[i] = -1;
		last[i] = i;
	}
	for (int i = 0; i < ins_num; i++) {
		flag = true;
		for (int j = 0; j < page_num; j++) {
			if (ins[i] == pages[j]) {//命中
				//printf("HIT\n");
				flag = false;
				hit++;//命中次数加一
				last[page_num-1]=Delete(last,find(last, j, page_num), page_num);//命中的移到队尾
				break;
			}
		}
		if (flag) {//没命中，发生页错误
			//printf("MISS\n");
			pages[last[0]] = ins[i];//替换被选为牺牲者的页
			last[page_num - 1]=Delete(last, find(last, last[0], page_num), page_num);//把队首选为牺牲者
			
		}
	}
	double inn = ins_num;
	double percent = hit / inn;
	return percent;
}
double FIFO(int ins[], int page_num) {
		double hits = 0;//页命中
		int i, x, y;
		int mc[33];
		for (i = 0; i <= page_num; i++) {
			mc[i] = -1;
		}//内存最大容量，实际容量为capacity
		int sum = 0;//mc中分配的个数，最大为capacity
		int flag;//判断是否命中
		int ep = 1;//置换出去的位置

		for (i = 0; i < ins_num; i++) {
			flag = 0;
			for (x = 1; x <= sum; x++) {			//查找是否命中
				if (mc[x] == ins[i]) {		//命中
					//printf("HIT\n");
					hits++;
					flag = 1;
					break;
				}
			}
			if (flag == 0) {		//没有命中就调入页
				//printf("MISS\n");
				if (sum < page_num) {	/*存在空页*/
					for (y = 1; y <= page_num; y++) {	/*查找第一个空页，放入指令*/
						if (mc[y] == -1) {
							mc[y] = ins[i];
							sum++;
							break;
						}
					}
				}
				else if (sum == page_num) {		/*不存在空页*/
					int temp = mc[ep];
					mc[ep] = ins[i];
					ep += 1;
					if (ep == page_num + 1)
						ep = 1;
				}
			}
		}
		double inn = ins_num;
		double percent = hits / inn;
		return percent;
}

void pageOrder(int ins[320]) {
	int m, flag = 0, yu;
	srand((unsigned)time(NULL));
	while (flag != 320) {
		m = rand() % 319;							//在[0，319]的指令地址之间随机选取一起点 M
		m++;										//执行地址为 M+1 的指令
		ins[flag] = m;								//顺序执行一条指令
		flag++;										//指令执行数+1
		if (flag == 320) break;						//执行320条指令后结束
		m = rand() % m;								//在前地址[0，M+1]中随机选取一条指令,M=M'
		ins[flag] = m;								//并执行
		flag++;										//指令执行数+1
		if (flag == 320) break;						//执行320条指令后结束
		m++;										//地址为 M'+1；
		ins[flag] = m;								//执行一条指令
		flag++;										//指令执行数+1
		if (flag == 320) break;						//执行320条指令后结束
		m++;										//后地址M'+2
		m = ((double)rand() / RAND_MAX)*(319 - m) + m;//在后地址[M’+2，319]中随机选取一条指令
		ins[flag] = m;								//执行
		flag++;										//指令执行数+1
		if (flag == 320) break;
	}
	for (int i = 0; i < 320; i++) {					//ins[]存放页顺序
		yu = ins[i] % 10;
		ins[i] = ins[i] / 10 - 0.1*yu;
	}
}