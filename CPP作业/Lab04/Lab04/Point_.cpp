#include "stdafx.h"
#include "graphics.h"
#include "Point_.h"
#include <stdexcept>

int Point::PointNumber = 0;

//�вι��캯��
Point::Point(int x, int y)//�вι��캯����ʼ��xy 
{
	x_ = x;
	y_ = y;
	PointNumber++;
}
//�޲ι��캯��
Point::Point()//�޲ι����ʼ��xyΪ0 0 
{
	x_ = 0;
	y_ = 0;
	PointNumber++;
}
Point::Point(Point &p)//�������캯��
{
	x_ = p.getx();
	y_ = p.gety();
	PointNumber++;
}
Point::~Point()//��������
{
	PointNumber--;
	//	xyprintf(60, 270, "%d    ", PointNumber);
}

//getter
int Point::getx()//����x 
{
	return x_;
}
int Point::gety()//����y 
{
	return y_;
}
int Point::getPointNumber()//���ص������
{
	return PointNumber;
}

//setter
void Point::setxy(const int x, const int y)//�޸�xy 
{
	x_ = x;
	y_ = y;
}

//���������
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

