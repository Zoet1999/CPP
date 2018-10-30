
#include "stdafx.h"
#include "Color.h"
#include "graphics.h"

int Color::ColorNumber = 0;

//无参构造函数
Color::Color()
{
	co_ = RGB(255, 255, 255);//初始化默认颜色为白色 
	flag_ = false;
	ColorNumber++;
}
//有参构造函数
Color::Color(int x, int y, int z)//初始化颜色 
{
	co_ = RGB(x, y, z);
	flag_ = false;
	ColorNumber++;
}
//有参构造函数
Color::Color(int a)
{
	co_ = a;
	flag_ = false;
	ColorNumber++;
}
//拷贝构造函数
Color::Color(Color &c)
{
	co_ = c.getColor();
	flag_ = c.getFlag();
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
