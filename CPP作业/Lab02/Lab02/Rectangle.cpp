#include "stdafx.h"
#include "Rectangle.h"
#include "graphics.h"
#include "Point.h"
#include "Color.h"



int Rectanglee::RectangleNumber = 0;
Rectanglee::Rectanglee() :xy1_(0, 0), xy2_(0, 0), Rcolor_(255, 255, 255)  // 无参构造默认初始化矩形的上坐标、下坐标、颜色 
{
	RectangleNumber++;//计数加一
}
Rectanglee::Rectanglee(int x1, int y1, int x2, int y2, int x, int y, int z) : xy1_(x1, y1), xy2_(x2, y2), Rcolor_(x, y, z) // 初始化矩形的上坐标、下坐标、颜色 
{
	RectangleNumber++;//计数加一
}
Rectanglee::Rectanglee(Rectanglee &r) : xy1_(r.getxy1().getx(), r.getxy1().gety()), xy2_(r.getxy1().getx(), r.getxy2().gety()), Rcolor_(r.getRcolor().getColor())
{
	RectangleNumber++;//计数加一
}
Rectanglee::~Rectanglee()
{
	RectangleNumber--;//计数减一

	xyprintf(60, 350, "%d    ", RectangleNumber);//显示矩形数量
}
void Rectanglee::setxy1(int x, int y) { xy1_ = Point(x, y); }//修改上坐标 
void Rectanglee::setxy2(int x, int y) { xy2_ = Point(x, y); }//修改下坐标 
void Rectanglee::setRcolor(int x, int y, int z) { Rcolor_.setColor(x, y, z); }//修改颜色 
Point Rectanglee::getxy1()//返回上坐标 
{
	return xy1_;
}
Point Rectanglee::getxy2()//返回下坐标 
{
	return xy2_;
}
Color Rectanglee::getRcolor()//返回颜色 
{
	return Rcolor_;
}
int Rectanglee::getRectangleNumber()//返回矩形的数量
{
	return RectangleNumber;
}
void Rectanglee::setFlag(bool a)//设置是否填充 
{
	Rcolor_.setFlag(a);
}
void Rectanglee::draw()
{
	Rcolor_.setC();//设置矩形的颜色为填充色与线条色 
	if (Rcolor_.getFlag() == true)
		bar(getxy1().getx(), getxy1().gety(), getxy2().getx(), getxy2().gety());//画实心矩形 
	else
		rectangle(getxy1().getx(), getxy1().gety(), getxy2().getx(), getxy2().gety());//画空心矩形 

}