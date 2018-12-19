#include "pch.h"
#include "UDGraph.h"


UDGraph::UDGraph()//��ʼ�����㡣
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
		vertices[i].vertex=i+1;
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

UDGraph::~UDGraph()
{
}

bool UDGraph::insert(int v1, int v2)//�����
{
	ArcNode* p = new ArcNode;
	ArcNode* p1 = new ArcNode;
	ArcNode* p2 = new ArcNode;
	v1 = findNode(v1);
	v2 = findNode(v2);
	//���������Ƿ�Ϸ�
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
			std::cout << "�ñ��Ѵ��ڣ�����������"<<std::endl;
			return false;
		}
		p = p->next;
	}

	//�ѱ߲��뵽�ڽӱ���
	p1->adjvex = v2;
	p1->headNode = v1;
	p1->next = vertices[v1].firstedge;
	vertices[v1].firstedge = p1;
	p2->adjvex = v1;
	p2->headNode = v2;
	p2->next = vertices[v2].firstedge;
	vertices[v2].firstedge = p2;
	return true;
}
int UDGraph::findNode(int v)//Ѱ�Ҷ���
{
	for (int i = 0; i < vexnum; i++) {
		if (vertices[i].vertex == v) {
			return i;
		}
	}
	std::cout << "�ö��㲻����," ;
	return -1;
}
void UDGraph::showAL()//��ʾ�ڽӱ�
{
	ArcNode* p;
	std::cout << "�ڽӱ�Ϊ��" << std::endl;
	for (int i = 0; i < vexnum; i++) {
		std::cout << i<<":"<< vertices[i].vertex;
		p = vertices[i].firstedge;
		while (p != NULL) {
			std::cout << "->" << vertices[p->adjvex].vertex;
			p = p->next;
		}
		std::cout << std::endl;
	}
}
void UDGraph::BFS()//�����������
{
	int m;
	std::cout << "�����������" << std::endl;
	std::cout << "��ѡ����ĸ�����Ϊ��㣺";
	std::cin >> m;//ѡ�������ʼ�����
	m = findNode(m);
	for (int i = 0; i < vexnum; i++) {
		visited[i] = false;
	}
	q.IntiQueue();
	int v;
	ArcNode* p;
	int i;
	for (int j = 0; j < vexnum; j++) {
		i =( j + m)%vexnum;//��ѡ��Ķ��㿪ʼѭ��
		isPrint = false;
		if (!visited[i]) {//�������û���ʹ��ĵ�
			std::cout << "�Խ��" << vertices[i].vertex << "Ϊ����������:";
			visited[i] = true;//���Ϊ���ʹ�
			//std::cout << vertices[i].vertex << " ";
			q.EnQueue(i);//�Ѹõ�������
			while (!q.isEmpty()) {//�����в�Ϊ��ʱ
				q.DeQueue(v);//�Ѷ��׳���
				p = vertices[v].firstedge;//�õ����׵��ڽӱ�ĵ�һ���ڽӽ��
				lastNode = vertices[v].vertex;
				while (p != NULL) {//ѭ���ҵ����׽����ڽӱ��ÿ��δ�����ʹ����ڽӽ��
					if (!visited[p->adjvex]) {
						visited[p->adjvex] = true;//���Ϊ���ʹ�
						std::cout << lastNode <<"->"<< vertices[p->adjvex].vertex << " ";//����ñ�
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
void UDGraph::DFS()//�����������
{
	int m;
	std::cout << "�����������" << std::endl;
	std::cout << "��ѡ����ĸ�����Ϊ��㣺";
	std::cin >>m;//ѡ�������ʼ�����
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
			DFS(i); //����ݹ麯��������Ϊ��ǰ���ʵĵ㣩
			if (!isPrint) {//û��������ߣ���ֻ�������
				std::cout << vertices[i].vertex;
			}
			std::cout << std::endl;
		}
	
	}
	std::cout << std::endl;
}
void UDGraph::DFS(int i)//�����������
{
	ArcNode* p;
	visited[i] = true;
	if (flag) {
	std::cout << lastNode << "->" << vertices[i].vertex<<" ";//��������еĵ�ı�
	isPrint = true;
	}
	else {
		flag = true;
	}
	p = vertices[i].firstedge;
	
	while (p != NULL) {//ѭ���ҵ����ʽ���δ�����ʹ��ڽӽ��
		if (!visited[p->adjvex]) {
		lastNode = vertices[p->headNode].vertex;
		DFS(p->adjvex); //�Ѹ��ڽӽ����Ϊ�ݹ麯���Ĳ������õݹ麯��
		}
		p = p->next;
	}
}

void UDGraph::DFSStack()//ջʵ�������������
{
	s.CreateStack();
	int m;
	std::cout << "�������������ջʵ�֣�"<<std::endl;
	std::cout << "��ѡ����ĸ�����Ϊ��㣺";
	std::cin >> m;//ѡ�������ʼ�����
	m = findNode(m);
	for (int i = 0; i < vexnum; i++) {
		visited[i] = false;
	}
	int i;
	for (int j = 0; j < vexnum; j++) {//��ѡ��Ķ��㿪ʼѭ��
		i = (j + m) % vexnum;
		if (!visited[i]){//�������û���ʹ��ĵ�
			std::cout << "�Խ��" << vertices[i].vertex << "Ϊ����������:";
			flag = false;
			isPrint = false;
			DFSStack(i);
			if (!isPrint) {//û��������ߣ���ֻ�������
				std::cout << vertices[i].vertex;
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

void UDGraph::DFSStack(int i)//ջʵ�������������
{
	Stack temp;
	int head;
	int out;
	s.push(i); //�Ѹõ���뵽ջ��
	ArcNode* p;
	visited[i] = true;
	p = vertices[i].firstedge;
	if (!p) {
		return;
	}
	while (!s.isEmpty())//���ջ��Ϊ��
	{
		out = s.top();// ����ջ��Ԫ��
		head = out;
		p = vertices[out].firstedge;

		while (p) {
			while (visited[p->adjvex] ) {//����ջ��Ԫ�صĵ�һ����Ч�ڽӽ��
				p = p->next;
				if (!p) {
					break;
				}
			}
			if (!p) {
				s.pop();
				break;
			}
			out = p->adjvex;
			std::cout << vertices[head].vertex << "->" << vertices[out].vertex << " ";//�������ڽӽ��ı�
			isPrint = true;
			visited[out] = true;
			s.push(out);// ������ڽӽ����뵽ջ��
			head = out;
			p = vertices[p->adjvex].firstedge; //Ȼ��ָ������ڽӽ����ڽӽ��
		}
	}
}