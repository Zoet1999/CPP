#pragma once
#define MaxVerNum 30
#include "Queue.h"
#include "Stack.h"
#include <iostream>
typedef struct ArcNode {
	int adjvex;//邻接点域
	int headNode;
	std::string Info;//边上的信息
	struct ArcNode *next;//指向下一个邻接点的指针域
}ArcNode;
typedef struct Vnode {
	int vertex;//顶点域
	ArcNode *firstedge;//边表头指针
}Vnode,AdjList[MaxVerNum];

class UDGraph
{
private:
	AdjList vertices;//邻接表
	bool visited[MaxVerNum];//遍历标志
	Queue q;
	Stack s;
	int temp;
	bool flag;
	bool isPrint;
	int lastNode;
	int vexnum;//顶点数
	int arcnum;//边数
public:
	UDGraph();//初始化顶点。
	~UDGraph();
	bool insert(int v1,int v2 );//插入边
	int findNode(int v);//寻找顶点
	void showAL();//显示邻接表
	void BFS();//广度优先搜索
	void DFS();//深度优先搜索
	void DFS(int i);//深度优先搜索
	void DFSStack();//深度优先搜索
	void DFSStack(int i);//深度优先搜索
};

