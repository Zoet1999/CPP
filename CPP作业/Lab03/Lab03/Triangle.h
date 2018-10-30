#pragma once
#include "Shape.h"
#include "Circle.h"
#include "Color.h"
class Triangle :
	public Shape
{
	Point xy1_;
	Point xy2_;
	Point xy3_;
	Color Tcolor_;//颜色 
	static int TriangleNumber;//记录三角形的数量
public:
	Triangle();
	Triangle(int x1, int y1, int x2, int y2, int x3,int y3,int x, int y, int z);
	Triangle(Triangle &t);
	~Triangle();

	//setter
	void setFlag(bool a);// 设置是否填充 
	void setxy(int x1, int y1, int x2, int y2, int x3, int y3);
	void setTcolor(int x, int y, int z);//修改颜色 

	//getter
	Point getxy1();
	Point getxy2();
	Point getxy3();
	Color getTcolor();//返回颜色 
	static int getTriangleNumber();//返回三角形的数量

	//other
	void draw();//画三角形
	
};

