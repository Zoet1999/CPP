#include "stdafx.h"
#include "graphics.h"
#include "Point.h"


int Point::PointNumber = 0;

Point::Point(int x, int y)//�вι��캯����ʼ��xy 
{
	x_ = x;
	y_ = y;
	PointNumber++;//������һ
}
Point::Point()//�޲ι����ʼ��xyΪ0 0 
{
	x_ = 0;
	y_ = 0;
	PointNumber++;//������һ
}
Point::Point(Point &p)//�������캯��
{
	x_ = p.getx();
	y_ = p.gety();
	PointNumber++;//������һ
}
Point::~Point()//��������
{
	PointNumber--;//������һ
	xyprintf(60, 270, "%d    ", PointNumber); //��ʾ������
}
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
void Point::setxy(const int x, const int y)//�޸�xy 
{
	x_ = x;
	y_ = y;
}
