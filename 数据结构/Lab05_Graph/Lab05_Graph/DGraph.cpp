#include "pch.h"
#include "DGraph.h"


DGraph::DGraph()//��ʼ�����㡣
{
	std::cout << "�����붥�������";
	std::cin >> vexnum;//���붥�����
	while (vexnum > 30 || vexnum < 0) {
		std::cout << "������󣡣��������� ���ڵ��� 0 С�ڵ��� 30 ����" << std::endl;
		std::cout << "�����붥�������";
		std::cin >> vexnum;
	}
	for (int i = 0; i < vexnum; i++) {
		//std::cout << "�������"<<i+1<<"������Ķ�����";
		//std::cin>>vertices[i].vertex;//��ʼ��������
		vertices[i].vertex = i + 1;
		vertices[i].firstedge = NULL;
	}
	std::cout << "������߸�����";
	std::cin >> arcnum;//����߸���
	int v1, v2;
	for (int i = 0; i < arcnum; i++) {
		std::cout << "�������" << i + 1 << "���ߵ��������㣺";
		std::cin >> v1 >> v2;
		if (insert(v1, v2) == false)//�����µıߵ��ڽӱ���
			i--;
	}
}

DGraph::~DGraph()
{
}

bool DGraph::insert(int v1, int v2)//�����
{
	ArcNode* p = new ArcNode;
	ArcNode* p1 = new ArcNode;
	ArcNode* p2 = new ArcNode;
	v1 = findNode(v1);
	v2 = findNode(v2);
	if (v1 == -1 || v2 == -1) {
		std::cout << "����������" << std::endl;
		return false;
	}
	if (v1 == v2) {
		std::cout << "������ͬ,����������" << std::endl;
		return false;
	}
	//����
	p = vertices[v1].firstedge;
	while (p) {
		if (p->adjvex == v2) {
			std::cout << "�ñ��Ѵ��ڣ�����������" << std::endl;
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
int DGraph::findNode(int v)//Ѱ�Ҷ���
{
	for (int i = 0; i < vexnum; i++) {
		if (vertices[i].vertex == v) {
			return i;
		}
	}
	std::cout << "�ö��㲻����" << std::endl;
	return 0;
}
void DGraph::showAL()//��ʾ�ڽӱ�
{
	ArcNode* p;
	std::cout << "�ڽӱ�Ϊ��" << std::endl;
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
void DGraph::BFS()//�����������
{
	int m;
	//ѡ�������ʼ�����
	std::cout << "�����������" << std::endl;
	std::cout << "��ѡ����ĸ�����Ϊ��㣺";
	std::cin >> m;
	m = findNode(m);
	for (int i = 0; i < vexnum; i++) {
		visited[i] = false;
	}
	q.IntiQueue();
	int v;
	ArcNode* p;
	int i;
	for (int j = 0; j < vexnum; j++) {//��ѡ��Ķ��㿪ʼѭ��
		i = (j + m) % vexnum;
		isPrint = false;
		if (!visited[i]) {// �������û���ʹ��ĵ�
			std::cout << "�Խ��" << vertices[i].vertex << "Ϊ����������:";
			visited[i] = true;//���Ϊ���ʹ�
			q.EnQueue(i);//�Ѹõ�������
			while (!q.isEmpty()) {//�����в�Ϊ��ʱ
				q.DeQueue(v);//�Ѷ��׳���
				p = vertices[v].firstedge;//�õ����׵��ڽӱ�ĵ�һ���ڽӽ��
				lastNode = vertices[v].vertex;
				while (p != NULL) {//ѭ���ҵ����׽����ڽӱ��ÿ��δ�����ʹ����ڽӽ��
					if (!visited[p->adjvex]) {
						visited[p->adjvex] = true;//���Ϊ���ʹ�
						std::cout << lastNode << "->" << vertices[p->adjvex].vertex << " ";//����ñ�
						isPrint = true;
						q.EnQueue(p->adjvex);//����������
					}
					p = p->next;
				}
			}
			if (!isPrint) {//û��������ߣ���ֻ�������
				std::cout << vertices[i].vertex;
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}
void DGraph::DFS()//�����������
{
	int m;
	std::cout << "�����������" << std::endl;
	std::cout << "��ѡ����ĸ�����Ϊ��㣺";
	std::cin >> m;//ѡ�������ʼ�����
	m = findNode(m);
	for (int i = 0; i < vexnum; i++) {
		visited[i] = false;
	}
	int i;
	for (int j = 0; j < vexnum; j++) {
		i = (j + m) % vexnum;//��ѡ��Ķ��㿪ʼѭ��
		if (!visited[i]) {//�������û���ʹ��ĵ�
			std::cout << "�Խ��" << vertices[i].vertex << "Ϊ����������:";
			flag = false;
			isPrint = false;
			DFS(i);//����ݹ麯��������Ϊ��ǰ���ʵĵ㣩
			if (!isPrint) {//û��������ߣ���ֻ�������
				std::cout << vertices[i].vertex;
			}
			std::cout << std::endl;
		}

	}
	std::cout << std::endl;
}
void DGraph::DFS(int i)//�����������
{
	ArcNode* p;
	visited[i] = true;
	if (flag) {//��һ�����������
		std::cout << lastNode << "->" << vertices[i].vertex << " ";//��������еĵ�ı�
		isPrint = true;
	}
	else {
		flag = true;
	}
	p = vertices[i].firstedge;

	while (p != NULL) {//ѭ���ҵ����ʽ���δ�����ʹ��ڽӽ��
		if (!visited[p->adjvex]) {
			lastNode = vertices[p->headNode].vertex;
			DFS(p->adjvex);//�Ѹ��ڽӽ����Ϊ�ݹ麯���Ĳ������õݹ麯��
		}
		p = p->next;
	}
}

