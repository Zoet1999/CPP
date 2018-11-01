// Lab02_数制转换问题.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "Stack.h"

int main()
{
	Stack s = Stack();
	int N, ans=0;
	std::cout << "十进制转化为八进制"<<std::endl;
	std::cout << "请输入要转换的数：";
	std::cin >> N;
	if (N < 0) {
		std::cout << "请输入正数：";
	}
	while (N > 0) {
		s.push(N % 8);
		N = N / 8;
	}
	while (!s.isEmpty()) {
		ans = ans * 10 + s.top();
		s.pop();
	}
	std::cout << "结果为："<<ans<<std::endl;
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
