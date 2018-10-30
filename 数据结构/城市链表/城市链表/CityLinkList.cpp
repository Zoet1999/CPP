#include "pch.h"
#include "CityLinkList.h"


CityLinkList::CityLinkList()
{
	InitList();
}


CityLinkList::~CityLinkList()
{
	
}

void CityLinkList::InitList()										
{
	/**
	* ��ʼ����������
	* ��ͷ�ڵ㴴���ռ䣬����ͷ����nextָ��ָ��NULL
	*/
	LHead = new LNode;
	LHead->next = NULL;
}
void CityLinkList::DeleteList()
{
	/**
	* ���ٵ�������
	*/
	LinkList L = LHead->next;
	while (L)
	{
		CityDelete(L->city.CityName);
		L = LHead->next;
	}
	delete LHead;
}
void CityLinkList::CityInsert(std::string CityName, double x, double y)		
{
	/**
	* �����������
	* @param CityName string  Ҫ������е�����
	* @param x double  Ҫ������е�x����
	* @param y double  Ҫ������е�y���� 
	*/
	LinkList L = Search(CityName);
	if (L->next) {
		std::cout << "�����Ѵ���" << std::endl;
	}
	else{
		LinkList N = new LNode;

		N->city.CityName = CityName;
		N->city.CityPosition[0] = x;
		N->city.CityPosition[1] = y;
		N->next = LHead->next;
		LHead->next = N;
	}
}
void CityLinkList::CityDelete(std::string CityName)						
{
	/**
	* ɾ����������
	* @param CityName string  Ҫɾ�����е�����
	*/

	LinkList L = Search(CityName);
	if (L->next)
	{
		LinkList M = L->next;
		L->next = L->next->next;
		delete M;
		std::cout << "ɾ�����гɹ�" << std::endl;
	}
	else {
		std::cout << "�Ҳ����ó���" << std::endl;
	}
}
LinkList CityLinkList::Search(double x, double y)						
{
	/**
	* ͨ��������Һ���
	* @param x double Ҫ���ҵĳ���x����
	* @param y double Ҫ���ҵĳ���y����
	* @return LinkList �ҵ��Ľ���ǰ�����
	*/
	LinkList L = LHead;
	while (L->next)
	{
		if (L->next->city.CityPosition[0] == x && L->next->city.CityPosition[1] == y)
			return L;
		L = L->next;
	}
	return L;
}
LinkList CityLinkList::Search(std::string CityName)					
{
	/**
	* ͨ�����ֲ��Һ���
	* @param CityName string Ҫ���ҵĳ�������
	* @return LinkList �ҵ��Ľ���ǰ�����
	*/
	LinkList L = LHead;
	while (L->next)
	{
		if (L->next->city.CityName==CityName)
			return L;
		L = L->next;
	}
	return L;
}
void CityLinkList::ChangeCity(std::string Name_, std::string CityName, double x, double y)	
{
	/**
	* ͨ�����ָ��º���
	* @param Name_ string Ҫ���µĳ�������
	* @param CityName string  ���º�ĳ��е�����
	* @param x double  ���º�ĳ��е�x����
	* @param y double  ���º�ĳ��е�y���� 
	*/
	LinkList L = Search(Name_);
	if (L->next)
	{
		L->next->city.CityName = CityName;
		L->next->city.CityPosition[0] = x;
		L->next->city.CityPosition[1] = y;
	}
	else
		std::cout << "�Ҳ���ƥ��ĳ�����Ϣ"<<std::endl;

}
void CityLinkList::ChangeCity(double x_, double y_, std::string CityName, double x, double y)
{
	/**
	* ͨ�����ָ��º���
	* @param x_ double  ��Ҫ���³��е�x����
	* @param y_ double  ��Ҫ���³��е�y����
	* @param CityName string  ���º�ĳ��е�����	
	* @param x double  ���º�ĳ��е�x����
	* @param y double  ���º�ĳ��е�y����
	*/
	LinkList L = Search(x_, y_);
	if (L->next)
	{
		L->next->city.CityName = CityName;
		L->next->city.CityPosition[0] = x;
		L->next->city.CityPosition[1] = y;
	}
	else
		std::cout << "�Ҳ���ƥ��ĳ�����Ϣ" << std::endl;
	
}
std::vector<City> CityLinkList::SearchNearest(std::string CityName, double D)
{
	/**
	* �ڷ�Χ���������к���
	* @param CityName string ��Ϊ�������ĳ��е�����	
	* @param D double ������Χ
	* @return std::vector<City>  �ڷ�Χ�ڵĳ��м���
	*/
	std::vector<City> res;
	LinkList N=Search(CityName);//���ڲ鿴���Ľ���Ƿ����
	LinkList L = LHead;			//���ڱ���������ҷ��������ĳ���
	if (N->next){
		double x = N->next->city.CityPosition[0];
		double y = N->next->city.CityPosition[1];
		double x_;
		double y_;
		double i;
		while (L->next)  //��ʼѭ���������ҷ��������ĳ���
		{
			x_ = L->next->city.CityPosition[0];
			y_ = L->next->city.CityPosition[1];
			i = (x - x_)*(x - x_) + (y - y_)*(y - y_);
			if (D*D >= i&&L->next->city.CityName!=N->next->city.CityName)
				res.push_back(L->next->city);
			L = L->next;
		}
		if (res.size() == 0)
		{
			std::cout << "�ڷ�Χ��û���ҵ���������" << std::endl;
		}
	}
	else {
		std::cout << "�Ҳ���ƥ��ĳ�����Ϣ" << std::endl;
	}
	return res;
}
void CityLinkList::show() {
	/**
	* ��ʾ���г��к���
	*/
	LinkList L = LHead->next;
	while (L)
	{
		std::cout << "�������֣�" << L->city.CityName.c_str() << "   �������꣺(" 
			<< L->city.CityPosition[0] << "," << L->city.CityPosition[1] << ")" << std::endl;
		L = L->next;
	}
}