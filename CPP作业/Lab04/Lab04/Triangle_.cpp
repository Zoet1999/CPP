#include "stdafx.h"
#include "Triangle_.h"
#include <stdexcept>
#include <cmath>

int Triangle::TriangleNumber = 0;

//无参构造函数
Triangle::Triangle() :xy1_(0, 0), xy2_(0, 0), xy3_(0, 0), Tcolor_(255, 255, 255)
{
	TriangleNumber++;
}
//析构函数
Triangle::~Triangle()
{
	TriangleNumber--;
}
//有参构造函数
Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y, int z) :xy1_(y1, x1), xy2_(x2, y2), xy3_(x3, y3), Tcolor_(x, y, z)
{
	TriangleNumber++;
}
//拷贝构造函数
Triangle::Triangle(Triangle &t) : xy1_(t.getxy1().getx(), t.getxy1().gety()), xy2_(t.getxy2().getx(), t.getxy2().gety()), xy3_(t.getxy3().getx(), t.getxy3().gety()), Tcolor_(t.getTcolor()[1], t.getTcolor()[2], t.getTcolor()[3])
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
	a[0] = xy1_[0];
	a[1] = xy1_[1];
	a[2] = xy2_[0];
	a[3] = xy2_[1];
	a[4] = xy3_[0];
	a[5] = xy3_[1];
	a[6] = xy1_[0];
	a[7] = xy1_[1];
	Tcolor_.setC();
	if (Tcolor_.getFlag() == true)
		fillpoly(4, a);
	else
		drawpoly(4, a);
}

//重载运算符
bool Triangle::operator <(const Triangle &r) {
	int c1 = sqrt((xy1_[0] - xy2_[0])*(xy1_[0] - xy2_[0]) + (xy1_[1] - xy2_[1])*(xy1_[1] - xy2_[1]))
		+ sqrt((xy3_[0] - xy2_[0])*(xy3_[0] - xy2_[0]) + (xy3_[1] - xy2_[1])*(xy3_[1] - xy2_[1]))
		+ sqrt((xy1_[0] - xy3_[0])*(xy1_[0] - xy3_[0]) + (xy1_[1] - xy3_[1])*(xy1_[1] - xy3_[1]));
	int c2 = sqrt((r.xy1_[0] - r.xy2_[0])*(r.xy1_[0] - r.xy2_[0]) + (r.xy1_[1] - r.xy2_[1])*(r.xy1_[1] - r.xy2_[1]))
		+ sqrt((r.xy3_[0] - r.xy2_[0])*(r.xy3_[0] - r.xy2_[0]) + (r.xy3_[1] - r.xy2_[1])*(r.xy3_[1] - r.xy2_[1]))
		+ sqrt((r.xy1_[0] - r.xy3_[0])*(r.xy1_[0] - r.xy3_[0]) + (r.xy1_[1] - r.xy3_[1])*(r.xy1_[1] - r.xy3_[1]));
		if (c1 < c2)
		return true;
	else
		return false;
}
bool Triangle::operator >(const Triangle &r) {
	int c1 = sqrt((xy1_[0] - xy2_[0])*(xy1_[0] - xy2_[0]) + (xy1_[1] - xy2_[1])*(xy1_[1] - xy2_[1]))
		+ sqrt((xy3_[0] - xy2_[0])*(xy3_[0] - xy2_[0]) + (xy3_[1] - xy2_[1])*(xy3_[1] - xy2_[1]))
		+ sqrt((xy1_[0] - xy3_[0])*(xy1_[0] - xy3_[0]) + (xy1_[1] - xy3_[1])*(xy1_[1] - xy3_[1]));
	int c2 = sqrt((r.xy1_[0] - r.xy2_[0])*(r.xy1_[0] - r.xy2_[0]) + (r.xy1_[1] - r.xy2_[1])*(r.xy1_[1] - r.xy2_[1]))
		+ sqrt((r.xy3_[0] - r.xy2_[0])*(r.xy3_[0] - r.xy2_[0]) + (r.xy3_[1] - r.xy2_[1])*(r.xy3_[1] - r.xy2_[1]))
		+ sqrt((r.xy1_[0] - r.xy3_[0])*(r.xy1_[0] - r.xy3_[0]) + (r.xy1_[1] - r.xy3_[1])*(r.xy1_[1] - r.xy3_[1]));
	if (c1 > c2)
		return true;
	else
		return false;
}
bool Triangle::operator <=(const Triangle &r) {
	int c1 = sqrt((xy1_[0] - xy2_[0])*(xy1_[0] - xy2_[0]) + (xy1_[1] - xy2_[1])*(xy1_[1] - xy2_[1]))
		+ sqrt((xy3_[0] - xy2_[0])*(xy3_[0] - xy2_[0]) + (xy3_[1] - xy2_[1])*(xy3_[1] - xy2_[1]))
		+ sqrt((xy1_[0] - xy3_[0])*(xy1_[0] - xy3_[0]) + (xy1_[1] - xy3_[1])*(xy1_[1] - xy3_[1]));
	int c2 = sqrt((r.xy1_[0] - r.xy2_[0])*(r.xy1_[0] - r.xy2_[0]) + (r.xy1_[1] - r.xy2_[1])*(r.xy1_[1] - r.xy2_[1]))
		+ sqrt((r.xy3_[0] - r.xy2_[0])*(r.xy3_[0] - r.xy2_[0]) + (r.xy3_[1] - r.xy2_[1])*(r.xy3_[1] - r.xy2_[1]))
		+ sqrt((r.xy1_[0] - r.xy3_[0])*(r.xy1_[0] - r.xy3_[0]) + (r.xy1_[1] - r.xy3_[1])*(r.xy1_[1] - r.xy3_[1]));
	if (c1 <= c2)
		return true;
	else
		return false;
}
bool Triangle::operator >=(const Triangle &r) {
	int c1 = sqrt((xy1_[0] - xy2_[0])*(xy1_[0] - xy2_[0]) + (xy1_[1] - xy2_[1])*(xy1_[1] - xy2_[1]))
		+ sqrt((xy3_[0] - xy2_[0])*(xy3_[0] - xy2_[0]) + (xy3_[1] - xy2_[1])*(xy3_[1] - xy2_[1]))
		+ sqrt((xy1_[0] - xy3_[0])*(xy1_[0] - xy3_[0]) + (xy1_[1] - xy3_[1])*(xy1_[1] - xy3_[1]));
	int c2 = sqrt((r.xy1_[0] - r.xy2_[0])*(r.xy1_[0] - r.xy2_[0]) + (r.xy1_[1] - r.xy2_[1])*(r.xy1_[1] - r.xy2_[1]))
		+ sqrt((r.xy3_[0] - r.xy2_[0])*(r.xy3_[0] - r.xy2_[0]) + (r.xy3_[1] - r.xy2_[1])*(r.xy3_[1] - r.xy2_[1]))
		+ sqrt((r.xy1_[0] - r.xy3_[0])*(r.xy1_[0] - r.xy3_[0]) + (r.xy1_[1] - r.xy3_[1])*(r.xy1_[1] - r.xy3_[1]));
	if (c1 >= c2)
		return true;
	else
		return false;
}
bool Triangle::operator ==(const Triangle &r) {
	if (xy1_ == r.xy1_&&xy2_ == r.xy2_&&xy3_ == r.xy3_&&Tcolor_ == r.Tcolor_)
		return true;
	else
		return false;
}
Triangle& Triangle::operator =(const Triangle &r)
{
	xy1_ = r.xy1_;
	xy2_ = r.xy2_;
	xy3_ = r.xy3_;
	Tcolor_ = r.Tcolor_;
	return *this;
}
int Triangle::operator [](int index) const
{
	switch (index)
	{
	case 0:
		return xy1_[0];
		break;
	case 1:
		return xy1_[1];
		break;
	case 2:
		return xy2_[0];
		break;
	case 3:
		return xy2_[1];
		break;
	case 4:
		return xy3_[0];
		break;
	case 5:
		return xy3_[1];
		break;
	default:
		throw std::out_of_range("index must be 0 to 5");
		break;
	}
}