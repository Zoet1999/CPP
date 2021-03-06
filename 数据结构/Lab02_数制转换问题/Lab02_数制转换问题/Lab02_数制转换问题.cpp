// Lab02_数制转换问题.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "Stack.h"

int main()
{
	Stack s = Stack();//保存答案的栈
	int N, ans=0;
	while (1) {
		std::cout << "十进制转化为八进制" << std::endl;
		std::cout << "请输入要转换的数(输入负数退出)：";
		std::cin >> N;//得到要转换的数字
		if (N < 0) {//如果数字为负数退出
			break;
		}
		while (N > 0) {//当N不为0时，N处以8，把结果存入N，把余数压入栈
			s.push(N % 8);
			N = N / 8;
		}
		while (!s.isEmpty()) {//弹出栈里全部元素，先弹出的是高位
			ans = ans * 10 + s.top();//已有答案*10加上 栈顶
			s.pop();//删除栈顶
		}
		std::cout << "结果为：" << ans <<"\n"<< std::endl;
		ans = 0;
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
