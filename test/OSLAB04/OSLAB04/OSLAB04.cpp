// OSLAB04.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<exception>
#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#define RESOURSNUM 5
typedef enum Status {
	Ready,                  //就绪
	Run,					//运行
	End						//结束
}Status;
typedef enum SCHED {
	SCHED_OTHER,			
	SCHED_FIFO,
	SCHED_RR
}SCHED;

struct process_Message {
	std::string PName;	//名字
	int prio_num;		//优先度
	int cost[RESOURSNUM];//需要每个资源的时钟周期数
	Status status;		//进程当前状态
};

class ProcSche {
private:
	std::queue<process_Message> ProcQueue;
	std::queue<process_Message> EndProcQueue;
	std::vector<process_Message> ProcList;
	SCHED sche;
	int clock;//时间片长度
public:
	ProcSche();
	~ProcSche();
	void createSche();//选择调度方式并设置时间片长度
	void createProc();//创建新的进程
	void clockCycle();//继续一个时钟循环
	void printProc();//打印所有进程的状态
	bool compare(const process_Message &a, const process_Message &b);
	bool isAllEnd();
	void Sort(std::vector<process_Message>& pl);
};
void ProcSche::Sort(std::vector<process_Message>& pl) {
	
		process_Message temp;
		int len = pl.size();
		int flag = 1;
		while (len > 0 && flag == 1) {
			flag = 0;
			for (int i = 0; i < len-1; i++) {
				if (pl.at(i).prio_num < pl.at(i + 1).prio_num){
					flag = 1;
					temp = pl.at(i);
					pl.at(i) = pl.at(i + 1);
					pl.at(i + 1) = temp;
				}
			}
			--len;
		}
	
}
bool ProcSche::isAllEnd() {
	process_Message pm;
	bool flag = true;
	switch (sche) {
	case SCHED_OTHER:
		for (int i = 0; i < ProcList.size(); i++) {
			pm = ProcList.front();
			ProcList.erase(ProcList.begin());
			if (pm.status != End) {
				flag = false;
			}
			ProcList.push_back(pm);
		}
		break;
	case SCHED_FIFO:
	case SCHED_RR:
		for (int i = 0; i < ProcQueue.size(); i++) {
			pm = ProcQueue.front();
			ProcQueue.pop();
			if (pm.status != End) {
				flag= false;
			}ProcQueue.push(pm);
		}
		break;
	default:
		std::cout << "调度模式error" << std::endl;
		break;
	}
	return flag;
}
bool ProcSche::compare(const process_Message &a,const process_Message &b){
	return a.prio_num > b.prio_num; //降序
}
ProcSche::ProcSche() {
	char c;
	int choose;
	while (true) {
	createSche();
	while (true) {
		std::cout << "请选择要进行的操作——1，创建新进程\t2，进行时间片轮转:   ";
		std::cin >> choose;
		switch (choose) {
		case 1:
			createProc();
			printProc();
			break;
		case 2:
			clockCycle();
			break;
		default:
			break;
		}
		if (isAllEnd()) {
			printProc();
			std::cout << "所有进程运行结束" << std::endl;
			break;
		}
	}
	std::cout << "进行下一次循环？(Y OR N)" << std::endl;
	std::cin >> c;
	if (c == 'N'||c=='n') {
		break;
	} 
	EndProcQueue = std::queue<process_Message>();
	ProcQueue = std::queue<process_Message>();
	ProcList = std::vector<process_Message>();
	}
}
ProcSche::~ProcSche() {

}
void ProcSche::createSche() {
	//选择调度方式并设置时间片长度
	bool flag = true;
	while (flag) {
		flag = false;
		std::cout << "请选择调度方式:\n1.SCHED_OTHER  2.SCHED_FIFO  3.SCHED_RR" << std::endl;
		int choose;
		std::cin >> choose;
		switch (choose) {
		case 1:
			this->sche = SCHED_OTHER;
			std::cout << "已选择调度模式:SCHED_OTHER"  << std::endl;
			break;
		case 2:
			this->sche = SCHED_FIFO;
			std::cout << "已选择调度模式:SCHED_FIFO" << std::endl;
			break;
		case 3:
			this->sche = SCHED_RR;
			std::cout << "已选择调度模式:SCHED_RR" << std::endl;
			break;
		default:
			std::cout << "非法选择，请重新输入" << std::endl;
			flag = true;
		}
	}
	flag = true;
	while (flag) {
		flag = false;
		std::cout << "设置时间片长度:" << std::endl;
		try {
		std::cin >>clock;
		}
		catch (std::exception e) {
			std::cout << "非法选择，请重新输入" << std::endl;
			flag = true;
		}
	}

}
void ProcSche::createProc(){
	//创建新的进程
	process_Message pm;
	bool flag = true;
	char c[45];
	int cos;
	while (flag) {
		flag = false;
		try {
			std::cout << "---------------------------------------------" << std::endl;
			std::cout << "请输入要创建进程的信息" << std::endl;
			std::cout << "---------------------------------------------" << std::endl;
			std::cout << "名称：";
			std::cin >> c;
			pm.PName.assign(c);
			std::cout << "需要各个资源的量" << std::endl;
			for (int i = 0; i < RESOURSNUM; i++) {
				std::cout << "资源" << (i + 1) << ":";
				std::cin >> cos;
				pm.cost[i] = cos;
			}
			std::cout << "进程优先度：";
			std::cin >> pm.prio_num;
			pm.status = Ready;
		}
		catch (std::exception e) {
			std::cout << "非法选择，请重新输入" << std::endl;
			flag = true;
		}
	}

	switch (sche) {
	case SCHED_OTHER:
		ProcList.push_back(pm);
		break;
	case SCHED_FIFO:
	case SCHED_RR:
		ProcQueue.push(pm);
		break;
	default:
		std::cout << "调度模式error"<<std::endl;
		break;
	}
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "进程创建完毕！" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	

}
void ProcSche::clockCycle(){
	//继续一个时钟循环
	
	process_Message pm;
	int sum=0;
	switch (sche) {
	case SCHED_OTHER:
		if (ProcList.size() == 0) {
			std::cout << "无进程" << std::endl;
			return;
		}
		Sort(ProcList);
		pm = ProcList.front();
		ProcList.front().status = Run;
		printProc();
		if (pm.prio_num > 0) {
			pm.prio_num -= 1;
		}
		for (int i = 0; i < RESOURSNUM; i++) {
			pm.cost[i] -= clock;
			if (pm.cost[i] <= 0) {
				pm.cost[i] = 0;
				sum += 1;
			}
		}
		if (sum == RESOURSNUM) {
			pm.prio_num = -1;
			pm.status = End;
		}
		else {
			pm.status = Ready;
		}
		ProcList.erase(ProcList.begin());
		ProcList.push_back(pm);
		break;
	case SCHED_FIFO:
		if (ProcQueue.size() == 0) {
			std::cout << "无进程" << std::endl;
			return;
		}
		
		ProcQueue.front().status = Run;
		for (int i = 0; i < RESOURSNUM; i++) {
			ProcQueue.front().cost[i] -= clock;
			if (ProcQueue.front().cost[i] <= 0) {
				ProcQueue.front().cost[i] = 0;
				sum += 1;
			}
		}
		printProc();
		if (sum == RESOURSNUM) {
			ProcQueue.front().status = End;
			pm = ProcQueue.front();
			ProcQueue.pop();
			EndProcQueue.push(pm);
		}
		else {
			pm.status = Ready;
		}	
		break;
	case SCHED_RR:
		pm = ProcQueue.front();
		ProcQueue.front().status = Run;
		for (int i = 0; i < RESOURSNUM; i++) {
			pm.cost[i] -= clock;
			if (pm.cost[i] <= 0) {
				pm.cost[i] = 0;
				sum += 1;
			}
		}
		printProc();
		if (sum == RESOURSNUM) {
			pm.status = End;
			ProcQueue.pop();
			EndProcQueue.push(pm);
		}
		else {
			pm.status = Ready;
			ProcQueue.pop();
			ProcQueue.push(pm);
		}
		
		break;
	default:
		std::cout << "调度模式error" << std::endl;
		break;
	}
}
void ProcSche::printProc() {
	//打印所有进程的状态
	process_Message pm;
	switch (sche) {
	case SCHED_OTHER:
		Sort(ProcList);
		std::cout << "名字\t|进程需要资源\t|优先级\t|进程状态" << std::endl;
		for (int i = 0; i < ProcList.size(); i++) {
			pm = ProcList.front();
			ProcList.erase(ProcList.begin());
			std::cout << pm.PName.c_str() << "\t|(";
			for (int j = 0; j < RESOURSNUM; j++) {
				std::cout << pm.cost[j] << " ";
			}
			std::cout << ")\t|";
			std::cout << pm.prio_num << "\t|";
			switch (pm.status) {
			case Run:
				std::cout << "Run" << std::endl;
				break;
			case Ready:
				std::cout << "Ready" << std::endl;
				break;
			case End:
				std::cout << "End" << std::endl;
				break;
			}
			ProcList.push_back(pm);
		}
	
		break;
	case SCHED_FIFO:
	case SCHED_RR:
		std::cout << "名字\t|进程需要资源\t|进程状态" << std::endl;
		for (int i = 0; i <ProcQueue.size(); i++) {
			process_Message pm=ProcQueue.front();
			
			std::cout << pm.PName.c_str() << "\t|(";
			for (int j = 0; j < RESOURSNUM; j++) {
				std::cout << pm.cost[j]<<" ";
			}
			std::cout << ")\t|";
			switch (pm.status) {
			case Run:
				std::cout << "Run" << std::endl;
				break;
			case Ready:
				std::cout << "Ready" << std::endl;
				break;
			case End:
				std::cout << "End" << std::endl;
				break;
			}
			ProcQueue.pop();
			ProcQueue.push(pm);
		}
		for (int i = 0; i < EndProcQueue.size(); i++) {
			process_Message pm = EndProcQueue.front();

			std::cout << pm.PName.c_str() << "\t|(";
			for (int j = 0; j < RESOURSNUM; j++) {
				std::cout << pm.cost[j] << " ";
			}
			std::cout << ")\t|";
			switch (pm.status) {
			case Run:
				std::cout << "Run" << std::endl;
				break;
			case Ready:
				std::cout << "Ready" << std::endl;
				break;
			case End:
				std::cout << "End" << std::endl;
				break;
			}
			EndProcQueue.pop();
			EndProcQueue.push(pm);
		}

		break;
	default:
		std::cout << "调度模式error" << std::endl;
		break;
	}
	std::cout << std::endl;
}

int main()
{
	ProcSche* ps = new ProcSche();
    std::cout << "Hello World!\n"; 
}
