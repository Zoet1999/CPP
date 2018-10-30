#include "stdafx.h"
#include "Rectangle_.h"
#include "graphics.h"
#include "Point_.h"
#include "Color_.h"
#include <stdexcept>


int Rectanglee::RectangleNumber = 0;
// 无参构造默认初始化矩形的上坐标、下坐标、颜色 
Rectanglee::Rectanglee() :xy1_(0, 0), xy2_(0, 0), Rcolor_(255, 255, 255)
{
	RectangleNumber++;
}
// 初始化矩形的上坐标、下坐标、颜色 
Rectanglee::Rectanglee(int x1, int y1, int x2, int y2, int x, int y, int z) : xy1_(x1, y1), xy2_(x2, y2), Rcolor_(x, y, z)
{
	RectangleNumber++;
}
// 拷贝构造函数
Rectanglee::Rectanglee(Rectanglee &r) : xy1_(r.getxy1().getx(), r.getxy1().gety()), xy2_(r.getxy1().getx(), r.getxy2().gety()), Rcolor_(r.getRcolor()[1], r.getRcolor()[2], r.getRcolor()[3])
{
	RectangleNumber++;
}
// 析构函数
Rectanglee::~Rectanglee()
{
	RectangleNumber--;

	//xyprintf(60, 350, "%d    ", RectangleNumber);
}

//setter
void Rectanglee::setxy1(int x, int y) { xy1_ = Point(x, y); }//修改上坐标 
void Rectanglee::setxy2(int x, int y) { xy2_ = Point(x, y); }//修改下坐标 
void Rectanglee::setRcolor(int x, int y, int z) { Rcolor_.setColor(x, y, z); }//修改颜色 
void Rectanglee::setFlag(bool a)//设置是否填充 
{
	Rcolor_.setFlag(a);
}

//getter
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

//other
void Rectanglee::draw()
{
	Rcolor_.setC();//设置矩形的颜色为填充色与线条色 
	if (Rcolor_.getFlag() == true)
		bar(getxy1()[0], getxy1()[1], getxy2()[0], getxy2()[1]);//画实心矩形 
	else
		rectangle(getxy1()[0], getxy1()[1], getxy2()[0], getxy2()[1]);//画空心矩形 
}

//重载运算符
bool Rectanglee::operator <(const Rectanglee &r)
{
	int s1 = (xy1_[0] - xy2_[0])*(xy1_[1] - xy2_[1]);
	int s2 = (r.xy1_[0] - r.xy2_[0])*(r.xy1_[1] - r.xy2_[1]);
	if (s1<s2)
		return true;
	else
		return false;
}
bool Rectanglee::operator >(const Rectanglee &r)
{
	int s1 = (xy1_[0] - xy2_[0])*(xy1_[1] - xy2_[1]);
	int s2 = (r.xy1_[0] - r.xy2_[0])*(r.xy1_[1] - r.xy2_[1]);
	if (s1>s2)
		return true;
	else
		return false;
}
bool Rectanglee::operator <=(const Rectanglee &r)
{
	int s1 = (xy1_[0] - xy2_[0])*(xy1_[1] - xy2_[1]);
	int s2 = (r.xy1_[0] - r.xy2_[0])*(r.xy1_[1] - r.xy2_[1]);
	if (s1<=s2)
		return true;
	else
		return false;
}
bool Rectanglee::operator >=(const Rectanglee &r)
{
	int s1 = (xy1_[0] - xy2_[0])*(xy1_[1] - xy2_[1]);
	int s2 = (r.xy1_[0] - r.xy2_[0])*(r.xy1_[1] - r.xy2_[1]);
	if (s1>=s2)
		return true;
	else
		return false;
}
bool Rectanglee::operator ==(const Rectanglee &r)
{
	if (xy1_==r.xy1_&&xy2_==r.xy2_&&Rcolor_==r.Rcolor_)
		return true;
	else
		return false;
}
Rectanglee& Rectanglee::operator =(const Rectanglee &r)
{
	xy1_ = r.xy1_;
	xy2_ = r.xy2_;
	Rcolor_ = r.Rcolor_;
	return *this;
}
int Rectanglee::operator [](int index) const
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
	default:
		throw std::out_of_range("index must be 0 to 3");
		break;
	}
}