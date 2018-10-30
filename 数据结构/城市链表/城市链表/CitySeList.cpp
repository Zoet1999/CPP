#include "pch.h"
#include "CitySeList.h"


CitySeList::CitySeList()
{
	/*构造函数*/
	size_ = 0;
	L_[MAXSIZE - 1].CityName = "无效城市";
	L_[MAXSIZE - 1].CityPosition[0] = 0;
	L_[MAXSIZE - 1].CityPosition[1] = 0;
	L_[MAXSIZE - 1].index = MAXSIZE - 1;
}
CitySeList::~CitySeList()
{
}
CitySe CitySeList::getL_Flag() {
	return L_[MAXSIZE - 1];
}

void CitySeList::CityInsert(std::string CityName, double x, double y)		//插入操作
{

	/**
	* 插入操作函数
	* @param CityName string  要插入城市的名字
	* @param x double  要插入城市的x坐标
	* @param y double  要插入城市的y坐标
	*/
	CitySe c = Search(CityName);
	if (c.CityName != L_[MAXSIZE - 1].CityName) {
		std::cout << "该城市已存在" << std::endl;
	}
	else {
		L_[size_].CityName = CityName;
		L_[size_].CityPosition[0] = x;
		L_[size_].CityPosition[1] = y;
		L_[size_].index = size_;
		size_++;

	}
}

void CitySeList::CityDelete(std::string CityName)					
{	/**
	* 删除操作函数
	* @param CityName string  要删除城市的名字
	*/
	CitySe c=Search(CityName);
	if (c.CityName != L_[MAXSIZE - 1].CityName) {
		for (int i = c.index; i < size_-1; i++) {
			L_[i] = L_[i + 1];
			L_[i].index--;
		}
		size_--;
	}
	else {
		std::cout << "找不到该城市" << std::endl;
	}
		
}
CitySe CitySeList::Search(double x, double y)								
{
	/**
	* 通过坐标查找函数
	* @param x double 要查找的城市x坐标
	* @param y double 要查找的城市y坐标
	* @return LinkList 找到的结点的前驱结点
	*/
	for (int i=0; i < size_; i++) {
		if (L_[i].CityPosition[0] == x&&L_[i].CityPosition[1]==y) {
			return L_[i];
		}
	}
	return L_[MAXSIZE - 1];

}
CitySe CitySeList::Search(std::string CityName)						
{
	/**
	* 通过名字查找函数
	* @param CityName string 要查找的城市名字
	* @return LinkList 找到的结点的前驱结点
	*/
	for (int i=0; i < size_; i++) {
		if (L_[i].CityName == CityName) {
			return L_[i];
		}
	}
	return L_[MAXSIZE - 1];
}
void CitySeList::ChangeCity(std::string Name_, std::string CityName, double x, double y)	
{
	/**
	* 通过名字更新函数
	* @param Name_ string 要更新的城市名字
	* @param CityName string  更新后的城市的名字
	* @param x double  更新后的城市的x坐标
	* @param y double  更新后的城市的y坐标
	*/
	CitySe c = Search(Name_);
	if (c.CityName != L_[MAXSIZE - 1].CityName) {
		L_[c.index].CityName = CityName;
		L_[c.index].CityPosition[0] = x;
		L_[c.index].CityPosition[1] = y;
		std::cout << "成功改为     城市名字：" << L_[c.index].CityName.c_str() << "   城市坐标：("
			<< L_[c.index].CityPosition[0] << "," << L_[c.index].CityPosition[1] << ")" << std::endl;
	}
	else {
		std::cout << "找不到该城市" << std::endl;
	}
}
void CitySeList::ChangeCity(double x_, double y_, std::string CityName, double x, double y)
{
	/**
	* 通过名字更新函数
	* @param x_ double  需要更新城市的x坐标
	* @param y_ double  需要更新城市的y坐标
	* @param CityName string  更新后的城市的名字
	* @param x double  更新后的城市的x坐标
	* @param y double  更新后的城市的y坐标
	*/
	CitySe c = Search(x_,y_);
	if (c.CityName != L_[MAXSIZE - 1].CityName) {
		L_[c.index].CityName = CityName;
		L_[c.index].CityPosition[0] = x;
		L_[c.index].CityPosition[1] = y;
		std::cout << "成功改为     城市名字：" << L_[c.index].CityName.c_str() << "   城市坐标：("
			<< L_[c.index].CityPosition[0] << "," << L_[c.index].CityPosition[1] << ")" << std::endl;
	}
	else {
		std::cout << "找不到该城市" << std::endl;
	}
}
void CitySeList::show()
{
	/**
	* 显示所有城市函数
	*/
	for (int i = 0; i < size_; i++) {
		std::cout << "城市名字：" << L_[i].CityName.c_str() << "   城市坐标：(" << L_[i].CityPosition[0] << "," << L_[i].CityPosition[1] << ")" << std::endl;
	}
}
std::vector<CitySe> CitySeList::SearchNearest(std::string CityName, double D)//返回范围内的城市
{

	/**
	* 在范围内搜索城市函数
	* @param CityName string 作为搜索中心城市的名字
	* @param D double 搜索范围
	* @return std::vector<City>  在范围内的城市集合
	*/
	std::vector<CitySe> res;
	CitySe c = Search(CityName);
	if (c.CityName!=L_[MAXSIZE-1].CityName ) {
		double x = c.CityPosition[0];
		double y = c.CityPosition[1];
		double x_;
		double y_;
		double n;
		for(int i=0;i<size_;i++)
		{
			x_ = L_[i].CityPosition[0];
			y_ = L_[i].CityPosition[1];
			n= (x - x_)*(x - x_) + (y - y_)*(y - y_);
			if (D*D >= n && i!=c.index)
				res.push_back(L_[i]);
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