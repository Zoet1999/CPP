
#include "stdafx.h"
#include "Color_.h"
#include "graphics.h"
#include <stdexcept>

int Color::ColorNumber = 0;

//无参构造函数
Color::Color()
{
	x_ = 255;
	y_ = 255;
	z_ = 255;
	co_ = RGB(255, 255, 255);//初始化默认颜色为白色 
	flag_ = false;
	ColorNumber++;
}
//有参构造函数
Color::Color(int x, int y, int z)//初始化颜色 
{
	x_ = x;
	y_ = y;
	z_ = z;
	co_ = RGB(x, y, z);
	flag_ = false;
	ColorNumber++;
}
//有参构造函数
/*Color::Color(int a)
{
	co_ = a;
	flag_ = false;
	ColorNumber++;
}*/
//拷贝构造函数
Color::Color(Color &c)
{
	x_ = c[1];
	y_ = c[2];
	z_ = c[3];
	co_ = c[0];
	flag_ = c.flag_;
	ColorNumber++;
}
//析构函数
Color::~Color()
{
	ColorNumber--;
	//xyprintf(60, 290, "%d    ", ColorNumber);
}

//setter
void Color::setColor(int x, int y, int z)//修改颜色 
{
	x_ = x;
	y_ = y;
	z_ = z;
	co_ = RGB(x, y, z);
}
void Color::setC()
{
	setcolor(co_);//设置当前颜色为线条色 
	setfillcolor(co_);//设置当前颜色为填充色
}
void Color::setFlag(bool a)//修改是否填充
{
	flag_ = a;
}

//getter
bool Color::getFlag()//返回是否填充
{
	return flag_;
}
int Color::getColorNumber()//返回颜色数量
{
	return ColorNumber;
}
int Color::getColor()//返回颜色 
{
	return co_;
}
//运算符重载
Color& Color::operator =(const Color& c)
{
	co_ = c[0];
	x_ = c[1];
	y_ = c[2];
	z_ = c[3];
	flag_ = c.flag_;
	return *this;
}
bool Color::operator ==(const Color& c)
{
	if (co_ == c.co_)
		return true;
	else
		return false;
}
bool Color::operator !=(const Color& c)
{
	if (co_ != c.co_)
		return true;
	else
		return false;
}
int Color::operator[](int index) const
{
	switch (index)
	{
	case 0:
		return co_;
		break;
	case 1:
		return x_;
		break;
	case 2:
		return y_;
		break;
	case 3:
		return z_;
		break;
	default:
		throw std::out_of_range("index must be 0 or 1");
		break;
	}
}