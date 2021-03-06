// Lab04.cpp: 定义控制台应用程序的入口点。
//
#include <iostream>
#include "stdafx.h"
#include "Point_.h"
#include "Circle_.h"
#include "Triangle_.h"
#include "DrawControl_.h"
#include "graphics.h"
#include "Color_.h"
#include "Rectangle_.h"
#include <stdexcept>

int main()
{
	
	DrawControl d(1000, 1000);
	Circle c1(100,100,50,66,55,144);

	//用构造函数初始化三个图像
	c1.setFlag(true);
	Rectanglee r1(500,500,700,600,0,200,100);
	r1.setFlag(true);
	Triangle t1(300, 200, 400, 200, 100, 400, 200,100, 250);
	t1.setFlag(true);

	//用重载运算符“=”创建三个图像并赋值
	Circle c2;
	c2 = c1;
	c2.draw();
	Rectanglee r2;
	r2 = r1;
	r2.draw();
	Triangle t2;
	t2= t1;
	t2.draw();

	//用构造函数初始化三个图像
	Circle c3(100, 100, 100, 66, 55, 144);
	c3.setFlag(true);
	Rectanglee r3(500, 500, 600, 600, 0, 200, 100);
	r3.setFlag(true);
	Triangle t3(300, 200, 300, 200, 100, 300, 200, 100, 250);
	t3.setFlag(true);



	setcolor(RGB(255, 255, 255));//设置当前颜色为线条色 
	setfillcolor(RGB(255, 255, 255));//设置当前颜色为填充色

	//输出重载运算符“<”“>”“<=”“>=”“==”的值
	xyprintf(300, 50, "(c1 == c2):%d , (c2 <= c3):%d, (c1 >= c2):%d, (c2 > c3):%d, (c1 < c2):%d", (c1 == c2), (c2 <= c3), (c1 >= c2), (c2 > c3), (c1 < c2));//圆比较半径
	xyprintf(300, 70, "(r1 == r2):%d , (r2 <= r3):%d, (r1 >= r2):%d, (r2 > r3):%d, (r1 < r2):%d", (r1 == r2), (r2 <= r3), (r1 >= r2), (r2 > r3), (r1 < r2));//矩形比较面积
	xyprintf(300, 90, "(t1 == t2):%d , (t2 <= t3):%d, (t1 >= t2):%d, (t2 > t3):%d, (t1 < t2):%d", (t1 == t2), (t2 <= t3), (t1 >= t2), (t2 > t3), (t1 < t2));//三角形比较周长

	//输出重载运算符"[ ]"输出的值
	xyprintf(300, 110, "[0]:%d [1]:%d", c1[0],c1[1]);
	xyprintf(300, 130, "[0]:%d [1]:%d [2]:%d [3]:%d", r1[0], r1[1], r1[2] ,r1[3]);
	xyprintf(300, 150, "[0]:%d [1]:%d [2]:%d [3]:%d [4]:%d [5]:%d", t1[0], t1[1], t1[2], t1[3],t1[4],t1[5]);

	ege::getch();
	d.close();
    return 0;
}

