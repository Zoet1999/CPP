#include "stdafx.h"
#include "graphics.h"
#include "Point.h"


int Point::PointNumber = 0;

Point::Point(int x, int y)//有参构造函数初始化xy 
{
	x_ = x;
	y_ = y;
	PointNumber++;//计数加一
}
Point::Point()//无参构造初始化xy为0 0 
{
	x_ = 0;
	y_ = 0;
	PointNumber++;//计数加一
}
Point::Point(Point &p)//拷贝构造函数
{
	x_ = p.getx();
	y_ = p.gety();
	PointNumber++;//计数加一
}
Point::~Point()//析构函数
{
	PointNumber--;//计数减一
	xyprintf(60, 270, "%d    ", PointNumber); //显示点数量
}
int Point::getx()//返回x 
{
	return x_;
}
int Point::gety()//返回y 
{
	return y_;
}
int Point::getPointNumber()//返回点的数量
{
	return PointNumber;
}
void Point::setxy(const int x, const int y)//修改xy 
{
	x_ = x;
	y_ = y;
}
