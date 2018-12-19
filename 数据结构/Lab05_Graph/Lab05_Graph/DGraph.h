#pragma once
#include "UDGraph.h"
class DGraph
{
private:
	AdjList vertices;//�ڽӱ�
	bool visited[MaxVerNum];//������־
	Queue q;
	Stack s;
	int temp;
	bool flag;
	bool isPrint;
	int lastNode;
	int vexnum;//������
	int arcnum;//����
public:
	DGraph();//��ʼ�����㡣
	~DGraph();
	bool insert(int v1, int v2);//�����
	int findNode(int v);//Ѱ�Ҷ���
	void showAL();//��ʾ�ڽӱ�
	void BFS();//�����������
	void DFS();//�����������
	void DFS(int i);//�����������
};

