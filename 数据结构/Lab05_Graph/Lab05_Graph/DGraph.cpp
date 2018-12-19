#include "pch.h"
#include "DGraph.h"


DGraph::DGraph()//初始化顶点。
{
	std::cout << "请输入顶点个数：";
	std::cin >> vexnum;//输入顶点个数
	while (vexnum > 30 || vexnum < 0) {
		std::cout << "输入错误！！！请输入 大于等于 0 小于等于 30 的数" << std::endl;
		std::cout << "请输入顶点个数：";
		std::cin >> vexnum;
	}
	for (int i = 0; i < vexnum; i++) {
		//std::cout << "请输入第"<<i+1<<"个顶点的顶点域：";
		//std::cin>>vertices[i].vertex;//初始化顶点域
		vertices[i].vertex = i + 1;
		vertices[i].firstedge = NULL;
	}
	std::cout << "请输入边个数：";
	std::cin >> arcnum;//输入边个数
	int v1, v2;
	for (int i = 0; i < arcnum; i++) {
		std::cout << "请输入第" << i + 1 << "条边的两个顶点：";
		std::cin >> v1 >> v2;
		if (insert(v1, v2) == false)//创建新的边到邻接表中
			i--;
	}
}

DGraph::~DGraph()
{
}

bool DGraph::insert(int v1, int v2)//插入边
{
	ArcNode* p = new ArcNode;
	ArcNode* p1 = new ArcNode;
	ArcNode* p2 = new ArcNode;
	v1 = findNode(v1);
	v2 = findNode(v2);
	if (v1 == -1 || v2 == -1) {
		std::cout << "请重新输入" << std::endl;
		return false;
	}
	if (v1 == v2) {
		std::cout << "不能相同,请重新输入" << std::endl;
		return false;
	}
	//查重
	p = vertices[v1].firstedge;
	while (p) {
		if (p->adjvex == v2) {
			std::cout << "该边已存在，请重新输入" << std::endl;
			return false;
		}
		p = p->next;
	}

	p1->adjvex = v2;
	p1->headNode = v1;
	p1->next = vertices[v1].firstedge;
	vertices[v1].firstedge = p1;
	return true;
}
int DGraph::findNode(int v)//寻找顶点
{
	for (int i = 0; i < vexnum; i++) {
		if (vertices[i].vertex == v) {
			return i;
		}
	}
	std::cout << "该顶点不存在" << std::endl;
	return 0;
}
void DGraph::showAL()//显示邻接表
{
	ArcNode* p;
	std::cout << "邻接表为：" << std::endl;
	for (int i = 0; i < vexnum; i++) {
		std::cout << i << ":" << vertices[i].vertex;
		p = vertices[i].firstedge;
		while (p != NULL) {
			std::cout << "->" << vertices[p->adjvex].vertex;
			p = p->next;
		}
		std::cout << std::endl;
	}
}
void DGraph::BFS()//广度优先搜索
{
	int m;
	//选择遍历开始的起点
	std::cout << "广度优先搜索" << std::endl;
	std::cout << "请选择从哪个顶点为起点：";
	std::cin >> m;
	m = findNode(m);
	for (int i = 0; i < vexnum; i++) {
		visited[i] = false;
	}
	q.IntiQueue();
	int v;
	ArcNode* p;
	int i;
	for (int j = 0; j < vexnum; j++) {//从选择的顶点开始循环
		i = (j + m) % vexnum;
		isPrint = false;
		if (!visited[i]) {// 如果遇到没访问过的点
			std::cout << "以结点" << vertices[i].vertex << "为根的生成树:";
			visited[i] = true;//标记为访问过
			q.EnQueue(i);//把该点加入队列
			while (!q.isEmpty()) {//当队列不为空时
				q.DeQueue(v);//把队首出队
				p = vertices[v].firstedge;//得到队首的邻接表的第一个邻接结点
				lastNode = vertices[v].vertex;
				while (p != NULL) {//循环找到队首结点的邻接表的每个未被访问过的邻接结点
					if (!visited[p->adjvex]) {
						visited[p->adjvex] = true;//标记为访问过
						std::cout << lastNode << "->" << vertices[p->adjvex].vertex << " ";//输出该边
						isPrint = true;
						q.EnQueue(p->adjvex);//把这个点入队
					}
					p = p->next;
				}
			}
			if (!isPrint) {//没有输出过边，就只输出顶点
				std::cout << vertices[i].vertex;
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}
void DGraph::DFS()//深度优先搜索
{
	int m;
	std::cout << "深度优先搜索" << std::endl;
	std::cout << "请选择从哪个顶点为起点：";
	std::cin >> m;//选择遍历开始的起点
	m = findNode(m);
	for (int i = 0; i < vexnum; i++) {
		visited[i] = false;
	}
	int i;
	for (int j = 0; j < vexnum; j++) {
		i = (j + m) % vexnum;//从选择的顶点开始循环
		if (!visited[i]) {//如果遇到没访问过的点
			std::cout << "以结点" << vertices[i].vertex << "为根的生成树:";
			flag = false;
			isPrint = false;
			DFS(i);//进入递归函数（参数为当前访问的点）
			if (!isPrint) {//没有输出过边，就只输出顶点
				std::cout << vertices[i].vertex;
			}
			std::cout << std::endl;
		}

	}
	std::cout << std::endl;
}
void DGraph::DFS(int i)//深度优先搜索
{
	ArcNode* p;
	visited[i] = true;
	if (flag) {//第一次遇到不输出
		std::cout << lastNode << "->" << vertices[i].vertex << " ";//输出参数中的点的边
		isPrint = true;
	}
	else {
		flag = true;
	}
	p = vertices[i].firstedge;

	while (p != NULL) {//循环找到访问结点的未被访问过邻接结点
		if (!visited[p->adjvex]) {
			lastNode = vertices[p->headNode].vertex;
			DFS(p->adjvex);//把该邻接结点作为递归函数的参数调用递归函数
		}
		p = p->next;
	}
}

