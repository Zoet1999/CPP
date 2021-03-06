// Lab03_字符串的模式匹配.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <stdio.h>
#include "pch.h"
#include <iostream>

int Index(std::string str, std::string sub, int pos);
int main()
{
	std::string s1;
	std::string s2;
	int pos;
	char str1[128];
	char str2[128];

	while (1) {
		std::cout << "请输入主串：";
		std::cin >> str1;
		std::cout << "请输入子串：";
		std::cin >> str2;
		s1.assign(str1);
		s2.assign(str2);
		std::cout << "请输入起始位置（输入负数退出）：";
		std::cin >> pos;

		if (pos < 0) {
			break;
		}

		int pos1 = Index(s1, s2, pos);

		std::cout << pos1 << "\n" << std::endl;
		
	}
}

int Index(std::string str,std::string sub, int pos) {
	//寻找从pos开始的第一个sub子串
	int sublen = sub.length();//子串长度
	int len = str.length();//主串长度
	int i = pos;//主串的开始查找位置
	int j = 0; //用来变量子串的下标 
		while (j < sublen) {//循环直到变量完子串
			if (str[i + j] == sub[j]) {
				j++;//进行下一位比较
			}
			else {
				j = 0;//回到子串开头
				i++;//主串的开始查找位置加一
			}
			if (i > len - sublen) {//如果为true说明遍历完主串
				return -1;//匹配失败
			}
		}
			return i+1;//	循环结束，说明匹配成功，返回下标i+1
	
}
