#pragma once
#include "UDGraph.h"
class DGraph
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
	DGraph();//初始化顶点。
	~DGraph();
	bool insert(int v1, int v2);//插入边
	int findNode(int v);//寻找顶点
	void showAL();//显示邻接表
	void BFS();//广度优先搜索
	void DFS();//深度优先搜索
	void DFS(int i);//深度优先搜索
};

