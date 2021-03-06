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
	CarQueue waitQ = CarQueue();	//等待队列
	CarStack parkS = CarStack(n);	//车库栈
	CarStack tempS = CarStack(n);	//交换栈
	char action;					//保存操作代号
	int number;						//车序号
	int time;						//到达时间
	int tempn;						//暂存车序号
	int tempt;						//暂存到达时间
	int numOfPark=0;				//停车场序号
	int numOfWait=0;				//便道序号
	std::cout << "请输入操作指令：";
	std::cin >> action;				
	while (action!='E') {			//如果输入E，退出
		std::cin >> number;			
		std::cin >> time;
		switch (action) {			//判断操作
		case 'A':					//入库请求操作
			if (parkS.isFull()) {	//如果车库满，压入等待队列
				numOfWait++;		//等待队列序号加一
				std::cout << "No." << number << " 进入" << numOfWait << "号便道" << std::endl;
				waitQ.EnQueue(number, time);
			}
			else {					//如果车库不满，压入车库栈
				numOfPark++;		//车库栈队列加一
				std::cout << "No."<<number<<" 进入"<< numOfPark <<"号车库"<< std::endl;
				parkS.Push(number, time);
			}
			break;
		case 'D':					//出库请求操作
			while (!parkS.isEmpty()) {//循环弹出车库栈中元素，寻找与要出库的车
				parkS.Pop(tempn, tempt);//出栈数据存到tempn, tempt变量中
				if (tempn == number) {//如果找到序号相等的车，之前移到交换栈里的车移回栈
					numOfPark--;//出栈后车库序号减一
					std::cout<<"No."<< number<<" Time:"<<time-tempt<<" Fee:" << 5*(time - tempt)<<std::endl;
					while (!tempS.isEmpty()) {//之前移到交换栈里的车移回栈
						tempS.Pop(tempn, tempt);
						parkS.Push(tempn, tempt);
					}
					if (!waitQ.isEmply())//如果等待队列不为空，就把队列出队，压入车库栈
					{
						numOfWait--;
						numOfPark++;
						waitQ.DeQueue(tempn, tempt);
						parkS.Push(tempn, time);
					}break;
				}
				else {//如果不是要找的车，就压入交换栈
					tempS.Push(tempn, tempt);
				}
			}
			if (parkS.isEmpty()) {//如果车库栈为空，则说明没有找到要出库的车
				std::cout << "DON`T FIND" << std::endl;
			}
			break;
		}
		std::cout << "请输入操作指令：";
		std::cin >> action;//再次输入出栈
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
