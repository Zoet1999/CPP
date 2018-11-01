// Lab02_括号匹配的检验.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "Stack.h"
#include <iostream>

int main()
{
	Stack s = Stack();
	std::string expr;
	char str[100];
	bool flag=true;
	std::cout << "请输入表达式:";
	std::cin >> str;
	expr.assign(str);
	for (int i=0; i < expr.length(); i++) {
	
		switch (expr.at(i)){
		case '(':
			s.push(0);
			break;
		case ')':
			if (s.isEmpty()) {
				flag = false;
			}else
			if (s.top() != 0) {
				flag = false;
			}else {
				s.pop();
			}
			break;
		case '[':
			s.push(1);
			break;
		case ']':
			if (s.isEmpty()) {
				flag = false;
			}
			else
			if (s.top() != 1) {
				flag = false;
			} else{
				s.pop();
			}
			break;
		default:
			break;
		}
		if (!flag) {
			break;
		}
	}
	if (!s.isEmpty()) {
		flag = false;
	}

	if (flag) {
		std::cout << "correct" << std::endl;
	}
	else {
		std::cout << "error" << std::endl;
	}
	return 0;
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
