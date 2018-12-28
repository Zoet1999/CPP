// Lab06_哈希表选择2and4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string.h>
#include <iomanip>
#include <stdlib.h>
#define TableLength 40
struct TableNode {
	std::string name;
	TableNode* next=NULL;
	int key;
};
std::string names[30] = { "YanJiaQuan" ,"WangYuXuan","PengWuLiang","ChenMengShi","LiuZiHao","ZhengMengDa","ZhengYanPei","LiShuang","YuLei","LiJian",
							"CuiYiQun","WuYuFeng","ZhouTingJiang","YaoChangHao", "YangHangLin","BuWenHang","SongYinDa","WeiSongYuan","DingHaoZhe","SunJingYang",
							"ChenShi","MiErKe","ChenYuanHong","WangChunZheng","LiuJiaHeng","YanZhaoMing","GongXingLe","YuanZhengYang","ChenZhiGang","LuXiangNan" };
int searchTemp;
int HashFunctions=1;//表示构造方法类型
int CollisionResolution=1;//表示冲突处理方法类型
double averages[6][5];//保存平均查找长度
void Insert(TableNode hash[], std::string name);
int getKey(std::string name);
void getAverageHash(TableNode hash[]);
int searchHash(TableNode hash[], std::string name);
int getNewKey(int key);
void clearTable(TableNode hash[]);
int main()
{

	
	TableNode hash[TableLength]; 
	
	for (int i = 0; i < 6; i++) {//循环6种构造方法
		for (int j = 0; j < 5; j++) {//循环5种冲突处理方法
			clearTable(hash);
			HashFunctions = i+1;
			CollisionResolution = j+1;
			for (int i = 0; i < 30; i++) {
				Insert(hash, names[i]);
			}
			getAverageHash(hash);
		}
	}
	//打印平均查找长度表
	std::string HashFunctionsNames[6] = { "直接定址法","数字分析法","平方取中法","折叠法","除留余数法","乘余取整法" };
	std::string CollisionResolutionNames[5] = { "线性探测法","二次探测法","伪随机探测法","二次散列","链地址法" };
	std::cout << std::setw(15) << "平均查找长度";
	for (int j = 0; j < 5; j++) {
		std::cout << std::setw(12) << CollisionResolutionNames[j].c_str();
	}std::cout << std::endl;
	for (int i = 0; i < 6; i++) {
		std::cout << std::setw(15) << HashFunctionsNames[i].c_str();
		for (int j = 0; j < 5; j++) {
			std::cout <<std::setw(12)<< averages[i][j];
		}
		std::cout << std::endl;
	}
	
	return 0;
}
void clearTable(TableNode hash[]) {
	//清空hash表
	for (int i = 0; i < TableLength; i++) {
		hash[i].name = "";
		hash[i].key = 0;
		hash[i].next = NULL;
	}
}

void Insert(TableNode hash[], std::string name) {
	//按照构造方法构造哈希表，根据冲突处理方法处理冲突。把名字插入到哈希表中。
	int key = getKey(name);//按照构造方法获得的地址
	if (strcmp(hash[key % TableLength].name.c_str(), "") == 0) {//如果该地址为空
		hash[key % TableLength].name = std::string(name);//把name放入该地址
		hash[key % TableLength].key = key;
	}
	else {//如果不为空
		if (CollisionResolution != 5) {//如果冲突处理方法不是链地址法
		int i = 0;
		searchTemp = 0;
		srand(100);//初始化随机种子
		int newKey = getNewKey(key);//根据线性探测再散列法处理冲突得到新地址
		while (strcmp(hash[newKey  % TableLength].name.c_str(), "") != 0) {//如果新地址不为空，再查找新地址
			i++;
			newKey = getNewKey(newKey);
			if (i >= TableLength) {
				printf("哈希表已满，插入失败\n");
				return;
			}
		}
		hash[newKey% TableLength].name = std::string(name);//把name放入找到的空地址
		hash[newKey % TableLength].key = key;
		}
		else {//如果冲突处理方法是链地址法
			TableNode* p = &hash[key % TableLength];
			while (p->next) {//找到链表尾部
				p = p->next;
			}
			p->next = new TableNode();//插入新结点
			p->next->name = std::string(name);
			p->next->key = key;
		}
	}
}

int getNewKey(int key) {
	//根据参数选择冲突处理方法，根据冲突处理方法得到新的地址
	switch (CollisionResolution) {
	case 1: //	线性探测法
		key = key + 1;
		break;
	case 2: //	二次探测法
		if (searchTemp >= 0) {
		searchTemp ++ ;
		}
		else{
			searchTemp--;
		}
		key += searchTemp;
		searchTemp = -searchTemp;
		while (key < 0) {
			key += TableLength;
		}
		break;
	case 3: //	伪随机探测法
		key+=rand()% TableLength;
		break;
	case 4: //	二次散列
		searchTemp++;
		key += searchTemp * searchTemp;
		break;
	case 5: //	链地址法
		break;
	default: 
		break;
	}


	return key;
}

int getKey(std::string name) {
	//根据参数选择构造方法，根据构造方法和关键字，得到地址
	int key = 0;
	int n = 0;
	double a = 0.6180339;
	for (char i : name) {
		n++;
		if (i < 'a')
			key += (i - 'A');
		else
			key += i - 'a';
	}

	switch (HashFunctions) {
	case 1: key = key;//	直接定址法
		break;
	case 2: //	数字分析法
		key = key % 100;//取个位和十位
		key = key % 10 * 10 + key / 10;//倒转十位和个位
		break;
	case 3: //	平方取中法
		key = key * key;
		key = key % 1000;
		key = key / 10;
		break;
	case 4: //	折叠法
		for (char i : name) {
			n++;
			if (i < 'a')
				key += (i);
			else
				key += i ;
		}
		key = key % 100 + key / 100;
		break;
	case 5: key=key%39;	//除留余数法
		break;
	case 6: //	乘余取整法
		key = 100 * (a*key-(int(a*key) / 1));
		break;
	default:
		break;
	}
	
	return key;
}


void getAverageHash(TableNode hash[]) {
	//计算平均查找长度
	int searchLength;
	int average = 0;
	std::cout.flags(std::ios::left);
	//std::cout << std::setw(4) << "序号" << ":" << std::setw(15) << "关键词" << std::setw(15) << "姓名" << "   " << "查找长度" << std::endl;
	for (int i = 0; i < 30; i++) {//遍历名字
			searchLength = searchHash(hash, names[i]);//用查找函数得到查找长度
			average += searchLength;//累加查找长度
	}
	//std::cout << "average:" << double(average) / 30.0<<std::endl;
	averages[HashFunctions-1][CollisionResolution-1] = double(average) / 30.0;//把平均查找长度
}


int searchHash(TableNode hash[], std::string name) {
	//查找目标name
	int key = getKey(name);//按照构造方法获得的地址
	int length = 2;
	if ((hash[key % TableLength].name.compare(name)) == 0) {//如果直接找到要找的name
		return 1;//直接返回查找次数1
	}
	else {//第一次得到的地址不是要找的name
		if (CollisionResolution != 5) {//如果冲突处理方法不是链地址法
			int i = 1;
			searchTemp = 0;
			srand(100);
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
			return length;
		}
		else {//如果冲突处理方法是链地址法
			TableNode* p = &hash[key % TableLength];
			while (p->next) {//循环链表查找目标name
				p = p->next;
				if ((p->name.compare(name)) != 0) {
					length++;//每次循环查找长度加一
				}
				else {
					return length;//找到后返回查找长度
				}
			}
			printf("不存在\n");//如果没找到，输出不存在
			return 0;
		}
	
	}
}