// Lab06_哈希表设计.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string.h>
#include <iomanip>
#define TableLength 40
struct TableNode {
	std::string name;
	int key;
};

void Insert(TableNode hash[], std::string name);
int getKey(std::string name);//根据构造方法和关键字，得到地址
int getNewKey(int key);//根据冲突处理方法得到新的地址
void printHash(TableNode hash[]);
int searchHash(TableNode hash[], std::string name);
int main()
{
	std::string names[30] = { "YanJiaQuan" ,"WangYuXuan","PengWuLiang","ChenMengShi","LiuZiHao","ZhengMengDa","ZhengYanPei","LiShuang","YuLei","LiJian",
							"CuiYiQun","WuYuFeng","ZhouTingJiang","YaoChangHao", "YangHangLin","BuWenHang","SongYinDa","WeiSongYuan","DingHaoZhe","SunJingYang",
							"ChenShi","MiErKe","ChenYuanHong","WangChunZheng","LiuJiaHeng","YanZhaoMing","GongXingLe","YuanZhengYang","ChenZhiGang","LuXiangNan"};

	TableNode hash[TableLength];
	printf("除留余数法(平均查找长度低于2):\n");
	for (int i = 0; i < 30; i++) {
		Insert(hash,names[i]);
	}
	printHash(hash);

	return 0;
}


void Insert(TableNode hash[], std::string name) {
	//构造哈希表，用线性探测再散列法处理冲突。把名字插入到哈希表中。
	int key = getKey(name);//按照构造方法获得的地址
	if (strcmp(hash[key % TableLength].name.c_str(), "") == 0) {//如果该地址为空
		hash[key % TableLength].name = std::string(name);//把name放入该地址
		hash[key % TableLength].key = key;
	}
	else {//如果不为空
		int newKey = getNewKey(key);//根据线性探测再散列法处理冲突得到新地址
		while (strcmp(hash[newKey  % TableLength].name.c_str(), "") != 0) {//如果新地址不为空，再查找新地址
			newKey = getNewKey(newKey);
		}
		hash[newKey% TableLength].name = std::string(name);//把name放入找到的空地址
		hash[newKey % TableLength].key = key;
	}
}

int getNewKey(int key) {
	//线性探测再散列法根据冲突处理方法得到新的地址
	return key + 1;
}

int getKey(std::string name) {
	//按照除留余数法得到地址
	int key=0;
	int n = 0;
	for (char i:name) {//计算每一位的ASCII码值，累加
		n++;
		if (i < 'a')
			key += (i - 'A');
		else
			key += i - 'a';
	}
	return key%39;//ASCII码值之和除以素数39，作为地址
}


void printHash(TableNode hash[]) {
	//把创建好的哈希表，输出成表格，并显示查找长度，计算出平均查找长度
	int searchLength;
	int average = 0;
	std::cout.flags(std::ios::left);
	std::cout << std::setw(4) << "序号" << ":" << std::setw(15) << "关键词" << std::setw(15) << "姓名" << "   " << "查找长度" << std::endl;
	for (int i = 0; i < TableLength; i++) {//遍历哈希表
		if (strcmp(hash[i].name.c_str(), "") != 0) {//如果不为空
			searchLength = searchHash(hash, hash[i].name.c_str());//查找得到查找长度
			std::cout << std::setw(4) << (i + 1) << ":" << std::setw(15) << hash[i].key << std::setw(15) << hash[i].name.c_str() << "   " << searchLength << std::endl;//输出信息
			average += searchLength;//累加查找长度
		}
		else {
			std::cout << std::setw(4) << (i + 1) << ":" << std::setw(15) << 0 << std::setw(15) << "empty             " << 0 << std::endl;//输出空的信息

		}
	}
	std::cout << "average:" << double(average) / 30.0;//输出平均查找长度
}


int searchHash(TableNode hash[], std::string name) {
	//利用创建好的哈希表，用线性探测再散列法处理冲突。来查找要找的元素。并返回查找长度
	int key = getKey(name);//按照构造方法获得的地址
	int length = 2;
	if ((hash[key % TableLength].name.compare(name)) == 0) {//如果直接找到要找的name
		return 1;//直接返回查找次数1
	}
	else {//第一次得到的地址不是要找的name
		int i = 1;
		int newKey = getNewKey(key);//根据线性探测再散列法处理冲突得到新地址
		while ((hash[newKey % TableLength].name.compare(name)) != 0) {//如果新地址不是要找的name，再查找新地址
			i++;
			length++;//每次循环查找长度加一
			newKey = getNewKey(newKey);
			if (i >= TableLength) {
				printf("不存在\n");
				return 0;
			}
		}
		return length;//返回查找长度
	}
}