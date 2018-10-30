#pragma once
#include "Shape.h"
#include "graphics.h"
#include "Point.h"
#include "Color.h"

class Rectanglee :
	public Shape
{
private:
	Point xy1_;//上坐标 
	Point xy2_;//下坐标 
	Color Rcolor_;//颜色 
	static int RectangleNumber;//记录矩形的数量
public:
	Rectanglee();// 无参构造默认初始化矩形的上坐标、下坐标、颜色 
	Rectanglee(int x1, int y1, int x2, int y2, int x, int y, int z);// 初始化矩形的上坐标、下坐标、颜色 
	Rectanglee(Rectanglee &r);
	~Rectanglee();
	void setxy1(int x, int y);//修改上坐标 
	void setxy2(int x, int y);//修改下坐标 
	void setRcolor(int x, int y, int z);//修改颜色 
	Point getxy1();//返回上坐标 
	Point getxy2();//返回下坐标 
	Color getRcolor();//返回颜色 
	static int getRectangleNumber();//返回矩形的数量
	void draw();//画矩形 
	void setFlag(bool a);// 设置是否填充 
};
