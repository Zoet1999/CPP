// Lab05_Graph.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "UDGraph.h"
#include "DGraph.h"
#include <iostream>

int main()
{
	std::cout << "----------------------------无向图------------------------" << std::endl;
	UDGraph* ud = new UDGraph();
	ud->showAL();
	ud->BFS();
	ud->DFS();
	ud->DFSStack();

	std::cout << "\n----------------------------有向图------------------------" << std::endl;
	DGraph* d = new DGraph();
	d->showAL();
	d->BFS();
	d->DFS();
	
	return 0;
}
