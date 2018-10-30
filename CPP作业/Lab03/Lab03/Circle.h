#pragma once
#include "Shape.h"
#include "graphics.h"
#include "Point.h"
#include "Color.h"
#include "Shape.h"
//定义一个圆类来表示圆形，包括三个成员变量，分别表示圆心坐标、半径、颜色。 
class Circle :
	public Shape
{
private:
	int r_;//半径 
	Point Cxy_;//圆心 
	Color Ccolor_;//颜色 
	static int CircleNumber;//记录圆的数量
public:
	//ctor and dtor
	Circle();// 无参构造默认初始化圆的坐标、半径、颜色 
	Circle(int x, int y, int r, int cx, int cy, int cz);//初始化圆的坐标、半径、颜色 
	Circle(Circle &c);//拷贝构造函数
	~Circle();//析构函数

	//setter
	void setxy(int x, int y);// 修改坐标 
	void setr(int r);// 修改半径 
	void setCcolor(int x, int y, int z);// 修改颜色 
	void setFlag(bool a);//设置是否填充 

	//getter
	Point getxy();//返回坐标 
	int getr();// 返回半径 
	Color getCcolor();//返回颜色 
	static int getCircleNumber();//返回圆的数量

	 //other
	void draw();//画出圆
};

