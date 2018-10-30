#include "stdafx.h"
#include "Circle.h"
#include "graphics.h"
#include "Point.h"
#include "Color.h"

int Circle::CircleNumber = 0;

//无参构造函数
Circle::Circle() :Cxy_(0, 0), r_(1), Ccolor_(255, 255, 255) //默认初始化圆的坐标、半径、颜色 
{
	CircleNumber++;
}
//有参构造函数
Circle::Circle(int x, int y, int cr, int cx, int cy, int cz) : Cxy_(x, y), r_(cr), Ccolor_(cx, cy, cz) //初始化圆的坐标、半径、颜色 
{
	CircleNumber++;
}
//拷贝构造函数
Circle::Circle(Circle &c) : Cxy_(c.getxy().getx(), c.getxy().gety()), r_(c.getr()), Ccolor_(c.getCcolor().getColor())
{
	CircleNumber++;
}
//析构函数
Circle::~Circle()
{
	CircleNumber--;
	//xyprintf(60, 330, "%d    ", CircleNumber);
}

//setter
void Circle::setxy(int x, int y) {
	Cxy_ = Point(x, y);
}
void Circle::setr(int cr) { r_ = cr; }
void Circle::setCcolor(int x, int y, int z) { Ccolor_.setColor(x, y, z); }
void Circle::setFlag(bool a) //设置是否填充 
{
	Ccolor_.setFlag(a);
}


//getter
Point Circle::getxy()// 修改坐标 
{
	return Cxy_;
}
int Circle::getr()// 修改半径 
{
	return r_;
}
Color Circle::getCcolor()// 修改颜色 
{
	return Ccolor_;
}
int Circle::getCircleNumber()//返回圆的数量
{
	return CircleNumber;
}

//other
void Circle::draw()
{
	Ccolor_.setC();//设置圆的颜色为填充色与线条色 
	if (Ccolor_.getFlag() == false)
		circle(getxy().getx(), getxy().gety(), getr());//画出空心圆 
	else
		fillellipse(getxy().getx(), getxy().gety(), getr(), getr());//画出实心圆 
}
