#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXSIZE 101

struct CitySe {
	/**
		* 城市信息结构体
		* 存储了城市的信息
		* CityName  城市名字
		* CityPosition[0] x坐标
		* CityPosition[1] y坐标
		* index 该数据在顺序表中的下标
		*/
	std::string CityName;
	double CityPosition[2];//0为x，1为y
	int index;
};


class CitySeList
{
	int size_;
	CitySe L_[MAXSIZE];
public:
	CitySeList();
	~CitySeList();
	CitySe getL_Flag();																		//返回L[size-1]的值
	void CityInsert(std::string CityName, double x, double y);								//插入操作
	void CityDelete(std::string CityName);													//删除操作
	CitySe Search(double x, double y);														//通过坐标查找
	CitySe Search(std::string CityName);														//通过名字查找
	void ChangeCity(std::string Name_, std::string CityName, double x, double y);		//通过名字查找更新
	void ChangeCity(double x_, double y_, std::string CityName, double x, double y);//通过坐标查找更新
	void show();
	std::vector<CitySe> SearchNearest(std::string CityName, double D);						//返回范围内的城市
};

