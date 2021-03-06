// Lab02_括号匹配的检验.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "Stack.h"
#include <iostream>

int main()
{
	Stack s = Stack();//初始化栈
	std::string expr;//保存表达式
	char str[100];
	bool flag=true;//判断表达式是否正确
	std::cout << "请输入表达式:";
	std::cin >> str;
	expr.assign(str);//输入表达式
	for (int i=0; i < expr.length(); i++) {//遍历表达式，根据不同元素进行不同操作
	
		switch (expr.at(i)){
		case '('://如果为前括号就直接压栈，0代表小括号
			s.push(0);
			break;
		case ')'://如果为后括号，先判断栈是否为空，栈顶是不是0，如果不为空，且栈顶为0，则把前括号出栈，否则，flag置为false
			if (s.isEmpty()) {
				flag = false;
			}else
			if (s.top() != 0) {
				flag = false;
			}else {
				s.pop();
			}
			break;
		case '['://如果为前括号就直接压栈，1代表中括号
			s.push(1);
			break;
		case ']'://如果为后括号，先判断栈是否为空，栈顶是不是1，如果不为空，且栈顶为1，则把前括号出栈，否则，flag置为false
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
	if (!s.isEmpty()) {//遍历完，如果栈里还留有元素，那就说明有前括号没有匹配的后括号，flag置为失败
		flag = false;
	}

	if (flag) {//如果flag为true则输出正确，否则输出错误
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
