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
	* 初始化单链表函数
	* 给头节点创建空间，并把头结点的next指针指向NULL
	*/
	LHead = new LNode;
	LHead->next = NULL;
}
void CityLinkList::DeleteList()
{
	/**
	* 销毁单链表函数
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
	* 插入操作函数
	* @param CityName string  要插入城市的名字
	* @param x double  要插入城市的x坐标
	* @param y double  要插入城市的y坐标 
	*/
	LinkList L = Search(CityName);
	if (L->next) {
		std::cout << "城市已存在" << std::endl;
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
	* 删除操作函数
	* @param CityName string  要删除城市的名字
	*/

	LinkList L = Search(CityName);
	if (L->next)
	{
		LinkList M = L->next;
		L->next = L->next->next;
		delete M;
		std::cout << "删除城市成功" << std::endl;
	}
	else {
		std::cout << "找不到该城市" << std::endl;
	}
}
LinkList CityLinkList::Search(double x, double y)						
{
	/**
	* 通过坐标查找函数
	* @param x double 要查找的城市x坐标
	* @param y double 要查找的城市y坐标
	* @return LinkList 找到的结点的前驱结点
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
	* 通过名字查找函数
	* @param CityName string 要查找的城市名字
	* @return LinkList 找到的结点的前驱结点
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
	* 通过名字更新函数
	* @param Name_ string 要更新的城市名字
	* @param CityName string  更新后的城市的名字
	* @param x double  更新后的城市的x坐标
	* @param y double  更新后的城市的y坐标 
	*/
	LinkList L = Search(Name_);
	if (L->next)
	{
		L->next->city.CityName = CityName;
		L->next->city.CityPosition[0] = x;
		L->next->city.CityPosition[1] = y;
	}
	else
		std::cout << "找不到匹配的城市信息"<<std::endl;

}
void CityLinkList::ChangeCity(double x_, double y_, std::string CityName, double x, double y)
{
	/**
	* 通过名字更新函数
	* @param x_ double  需要更新城市的x坐标
	* @param y_ double  需要更新城市的y坐标
	* @param CityName string  更新后的城市的名字	
	* @param x double  更新后的城市的x坐标
	* @param y double  更新后的城市的y坐标
	*/
	LinkList L = Search(x_, y_);
	if (L->next)
	{
		L->next->city.CityName = CityName;
		L->next->city.CityPosition[0] = x;
		L->next->city.CityPosition[1] = y;
	}
	else
		std::cout << "找不到匹配的城市信息" << std::endl;
	
}
std::vector<City> CityLinkList::SearchNearest(std::string CityName, double D)
{
	/**
	* 在范围内搜索城市函数
	* @param CityName string 作为搜索中心城市的名字	
	* @param D double 搜索范围
	* @return std::vector<City>  在范围内的城市集合
	*/
	std::vector<City> res;
	LinkList N=Search(CityName);//用于查看中心结点是否存在
	LinkList L = LHead;			//用于遍历链表查找符合条件的城市
	if (N->next){
		double x = N->next->city.CityPosition[0];
		double y = N->next->city.CityPosition[1];
		double x_;
		double y_;
		double i;
		while (L->next)  //开始循环遍历查找符合条件的城市
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
			std::cout << "在范围内没有找到其他城市" << std::endl;
		}
	}
	else {
		std::cout << "找不到匹配的城市信息" << std::endl;
	}
	return res;
}
void CityLinkList::show() {
	/**
	* 显示所有城市函数
	*/
	LinkList L = LHead->next;
	while (L)
	{
		std::cout << "城市名字：" << L->city.CityName.c_str() << "   城市坐标：(" 
			<< L->city.CityPosition[0] << "," << L->city.CityPosition[1] << ")" << std::endl;
		L = L->next;
	}
}