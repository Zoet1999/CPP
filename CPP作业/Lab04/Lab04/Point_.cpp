#include "stdafx.h"
#include "graphics.h"
#include "Point_.h"
#include <stdexcept>

int Point::PointNumber = 0;

//有参构造函数
Point::Point(int x, int y)//有参构造函数初始化xy 
{
	x_ = x;
	y_ = y;
	PointNumber++;
}
//无参构造函数
Point::Point()//无参构造初始化xy为0 0 
{
	x_ = 0;
	y_ = 0;
	PointNumber++;
}
Point::Point(Point &p)//拷贝构造函数
{
	x_ = p.getx();
	y_ = p.gety();
	PointNumber++;
}
Point::~Point()//析构函数
{
	PointNumber--;
	//	xyprintf(60, 270, "%d    ", PointNumber);
}

//getter
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

//setter
void Point::setxy(const int x, const int y)//修改xy 
{
	x_ = x;
	y_ = y;
}

//运算符重载
Point& Point::operator +(Point& p)
{
	int x = (this->x_ + p.getx()) / 2.0;
	int y = (this->y_ + p.gety()) / 2.0;
	Point a(x, y);
	return a;
}

Point& Point::operator =(const Point& p)
{
	x_ = p.x_;
	y_ = p.y_;

	return *this;
}

bool Point::operator ==(const Point& p)
{
	if (x_ == p.x_&&y_ == p.y_)
	{
		return true;
	}
	else return false;
}

bool Point::operator !=(const Point& p)
{
	if (x_ == p.x_&&y_ == p.y_)
	{
		return false;
	}
	else return true;
}

int Point::operator [](int index) const
{
	if (0==index)
		return x_;
	else if (1==index)
		return y_;
	else { 
		throw std::out_of_range("index must be 0 or 1");
		return 0; }
}

Point& Point::operator+=(const Point& p)
{
	x_ += p.x_;
	y_ += p.y_;
	return *this;
}

