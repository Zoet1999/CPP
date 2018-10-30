#include "stdafx.h"
#include "Triangle.h"

int Triangle::TriangleNumber = 0;

//无参构造函数
Triangle::Triangle():xy1_(0,0),xy2_(0,0),xy3_(0,0),Tcolor_(255,255,255)
{
	TriangleNumber++;
}
//析构函数
Triangle::~Triangle()
{
	TriangleNumber--;
}
//有参构造函数
Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y, int z):xy1_(y1, x1), xy2_(x2, y2), xy3_(x3, y3), Tcolor_(x, y, z)
{
	TriangleNumber++;
}
//拷贝构造函数
Triangle::Triangle(Triangle &t): xy1_(t.getxy1().getx(), t.getxy1().gety()), xy2_(t.getxy2().getx(), t.getxy2().gety()), xy3_(t.getxy3().getx(), t.getxy3().gety()), Tcolor_(t.getTcolor().getColor() )
{
	TriangleNumber++;
}

//setter
void Triangle::setxy(int x1, int y1, int x2, int y2, int x3, int y3)
{
	xy1_ = Point(x1, y1);
	xy2_ = Point(x2, y2);
	xy3_ = Point(x3, y3);
}
void Triangle::setTcolor(int x, int y, int z)//修改颜色 
{
	Tcolor_.setColor(x, y, z);
}
void Triangle::setFlag(bool a)// 设置是否填充 
{
	Tcolor_.setFlag(a);
}

//getter
Point Triangle::getxy1()
{
	return xy1_;
}
Point Triangle::getxy2()
{
	return xy2_;
}
Point Triangle::getxy3()
{
	return xy3_;
}
Color Triangle::getTcolor()//返回颜色 
{
	return Tcolor_;
}
int Triangle::getTriangleNumber()//返回三角形的数量
{
	return TriangleNumber;
}

//other
void Triangle::draw()//画三角形
{
	int a[8];
	a[0] = xy1_.getx();
	a[1] = xy1_.gety();
	a[2] = xy2_.getx();
	a[3] = xy2_.gety();
	a[4] = xy3_.getx();
	a[5] = xy3_.gety();
	a[6] = xy1_.getx();
	a[7] = xy1_.gety();
	Tcolor_.setC();
	if (Tcolor_.getFlag() == true)
		fillpoly(4, a);
	else
		drawpoly(4, a);
}