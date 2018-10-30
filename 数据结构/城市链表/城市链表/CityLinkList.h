#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

struct City {
	/**
	* 城市信息结构体
	* 存储了城市的信息
	* CityName  城市名字
	* CityPosition[0] x坐标
	* CityPosition[1] y坐标
	*/
	std::string CityName;
	double CityPosition[2];//0为x，1为y
};
typedef struct LNode
{
	/**
	* 链表结点
	* city 存储城市信息
	* next 后继指针，指向下一个结点
	*/
	City city;
	LNode * next;
}LNode, *LinkList;


class CityLinkList
{
private:
	LinkList LHead;
public:
	CityLinkList();
	~CityLinkList();
	void InitList();											                	//初始化单链表
	void DeleteList();											                	//清空链表
	void CityInsert(std::string CityName, double x, double y);	                	//插入操作
	void CityDelete(std::string CityName);						                	//删除操作
	LinkList Search(double x, double y);						                	//通过坐标查找
	LinkList Search(std::string CityName);						                	//通过名字查找
	void ChangeCity(std::string Name_,std::string CityName, double x, double y);	//通过名字查找更新
	void ChangeCity(double x_, double y_,std::string CityName, double x, double y);//通过坐标查找更新
	void show();
	std::vector<City> SearchNearest(std::string CityName, double D);//返回范围内的城市
};

