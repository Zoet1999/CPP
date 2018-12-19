#pragma once
#define MaxVerNum 30
#include "Queue.h"
#include "Stack.h"
#include <iostream>
typedef struct ArcNode {
	int adjvex;//�ڽӵ���
	int headNode;
	std::string Info;//���ϵ���Ϣ
	struct ArcNode *next;//ָ����һ���ڽӵ��ָ����
}ArcNode;
typedef struct Vnode {
	int vertex;//������
	ArcNode *firstedge;//�߱�ͷָ��
}Vnode,AdjList[MaxVerNum];

class UDGraph
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
	UDGraph();//��ʼ�����㡣
	~UDGraph();
	bool insert(int v1,int v2 );//�����
	int findNode(int v);//Ѱ�Ҷ���
	void showAL();//��ʾ�ڽӱ�
	void BFS();//�����������
	void DFS();//�����������
	void DFS(int i);//�����������
	void DFSStack();//�����������
	void DFSStack(int i);//�����������
};

