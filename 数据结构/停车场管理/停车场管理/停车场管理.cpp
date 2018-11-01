// 停车场管理.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "CarStack.h"
#include "CarQueue.h"
#include <iostream>

int main()
{
	int n = 0;
	std::cout << "请输入停车场大小n:";
	std::cin >> n;
	CarQueue waitQ = CarQueue();
	CarStack parkS = CarStack(n);
	CarStack tempS = CarStack(n);
	char action;
	int number;
	int time;
	int tempn;
	int tempt;
	int numOfPark=0;
	int numOfWait=0;
	std::cin >> action;
	while (action!='E') {
		std::cin >> number;
		std::cin >> time;
		switch (action) {
		case 'A':
			if (parkS.isFull()) {
				numOfWait++;
				std::cout << "No." << number << " 进入" << numOfWait << "号便道" << std::endl;
				waitQ.EnQueue(number, time);
			}
			else {
				numOfPark++;
				std::cout << "No."<<number<<" 进入"<< numOfPark <<"号车库"<< std::endl;
				parkS.Push(number, time);
			}
			break;
		case 'D':
			while (!parkS.isEmpty()) {
				parkS.Pop(tempn, tempt);
				if (tempn == number) {
					numOfPark--;
					std::cout<<"No."<< number<<" Time:"<<time-tempt<<" Fee:" << 5*(time - tempt)<<std::endl;
					while (!tempS.isEmpty()) {
						tempS.Pop(tempn, tempt);
						parkS.Push(tempn, tempt);
					}
					if (!waitQ.isEmply())
					{
						numOfWait--;
						numOfPark++;
						waitQ.DeQueue(tempn, tempt);
						parkS.Push(tempn, time);
					}break;
				}
				else {
					tempS.Push(tempn, tempt);
				}
			}
			if (parkS.isEmpty()) {
				std::cout << "DON`T FIND" << std::endl;
			}
			break;
		}
		std::cin >> action;
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
