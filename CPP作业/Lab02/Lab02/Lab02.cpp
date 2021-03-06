// Lab02.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "graphics.h"
#include <iostream>
#include "Point.h"
#include "Color.h"
#include "Circle.h"
#include "Rectangle.h"
#include "DrawControl.h"
int main()
{
	DrawControl a(1000, 1000);//初始化1000*1000的绘画环境 

	Circle *c = reinterpret_cast<Circle *>(new Circle(500, 200, 150, 255, 255, 255));//构建圆对象
	//画表
	outtextxy(10, 10, "建立一个圆后 ");
	outtextxy(10, 30, "点：   ");
	outtextxy(10, 50, "颜色： ");
	outtextxy(10, 70, "图形： ");
	outtextxy(10, 90, "圆：   ");
	outtextxy(10, 110, "矩形： ");
	xyprintf(60, 30, "%d    ", Point::getPointNumber());
	xyprintf(60, 50, "%d    ", Color::getColorNumber());
	xyprintf(60, 70, "%d    ", Shape::getShapeNumber());
	xyprintf(60, 90, "%d    ", Circle::getCircleNumber());
	xyprintf(60, 110, "%d    ", Rectanglee::getRectangleNumber());
	Rectanglee *r = reinterpret_cast<Rectanglee *>(new Rectanglee(400, 400, 600, 600, 200, 200, 110));//构建矩形对象
	//画表
	outtextxy(10, 130, "再建立一个矩形后 ");
	outtextxy(10, 150, "点：   ");
	outtextxy(10, 170, "颜色： ");
	outtextxy(10, 190, "图形： ");
	outtextxy(10, 210, "圆：   ");
	outtextxy(10, 230, "矩形： ");
	xyprintf(60, 150, "%d    ", Point::getPointNumber());
	xyprintf(60, 170, "%d    ", Color::getColorNumber());
	xyprintf(60, 190, "%d    ", Shape::getShapeNumber());
	xyprintf(60, 210, "%d    ", Circle::getCircleNumber());
	xyprintf(60, 230, "%d    ", Rectanglee::getRectangleNumber());

	r->draw();//画矩形
	r->setFlag(true);//改参数
	r->setxy1(500, 500);
	r->draw();//画矩形

	c->draw();//画圆
	c->setFlag(true);//改参数
	c->setr(100);
	c->draw();//画圆

	//画表
	outtextxy(10, 250, "delete圆和矩形后 ");
	outtextxy(10, 270, "点：   ");
	outtextxy(10, 290, "颜色： ");
	outtextxy(10, 310, "图形： ");
	outtextxy(10, 330, "圆：   ");
	outtextxy(10, 350, "矩形： ");
	delete c;//释放圆对象
	delete r;//释放矩形对象
	ege::getch();
	a.close(); //关闭绘图环境
	return 0;
}

