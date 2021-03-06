// Lab03.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include "graphics.h"
#include <iostream>
#include "Point.h"
#include "Color.h"
#include "Circle.h"
#include "Rectangle.h"
#include "DrawControl.h"
#include "Triangle.h"
#include <fstream>
#include <string>
#include <sstream>
int main1();//1.读文件模式（main1）
int main2();//2.写文件模式（main2）
int main()
{
	DrawControl a(1000, 1000);//初始化1000*1000的绘画环境 
	
	std::string choose ;

	std::istringstream ss;
	int n, flag=1;
	inputbox_getline("选择进行那种模式", "请选择模式：\n0.退出\n1.读文件模式（main1）\n2.写文件模式（main2）", const_cast<char*>(choose.c_str()), 50);
	ss.str(choose.c_str());
	ss >> n;
	ss.clear();//清空缓冲区  
	choose.clear();
	while (1) {//进行模式选择
		switch (n) {
		case 1:main1();//进入模式1
			inputbox_getline("选择进行那种模式", "请选择模式：\n0.退出\n1.读文件模式（main1）\n2.写文件模式（main2）", const_cast<char*>(choose.c_str()), 50);
			ss.str(choose.c_str());
			ss >> n;
			ss.clear();//清空缓冲区  
			choose.clear();
			break;
		case 2:
			main2();//进入模式2
			inputbox_getline("选择进行那种模式", "请选择模式：\n0.退出\n1.读文件模式（main1）\n2.写文件模式（main2）", const_cast<char*>(choose.c_str()), 50);
			ss.str(choose.c_str());
			ss >> n;
			ss.clear();//清空缓冲区  
			choose.clear();
			break;
		case 0:
			flag = 0;
			break;
		default://如果输入错误重新输入
			inputbox_getline("选择进行那种模式", "选择出现错误，请重新选择;\n0.退出\n1.读文件模式（main1）\n2.写文件模式（main2）", const_cast<char*>(choose.c_str()), 50);
			ss.str(choose.c_str());
			ss >> n;
			ss.clear();//清空缓冲区  
			choose.clear();
			break;
		}
		if (0 == flag)//n==0时退出
			break;
		cleardevice();//每次模式退出时清屏
	}
	ege::getch();
	a.close(); //关闭绘图环境
	return 0;
}
int main1() 
{
	int kind = 0;//图形
	int x1=0, x2=0, x3=0;//坐标
	int y1=0, y2=0, y3=0;
	int ra=0;//半径
	char line[105] = { 0 };
	std::string co;
	bool flag=0;
	std::fstream f1;
	f1.open("f1.txt", std::ios::in);//打开文件
	Circle c;
	Rectanglee r;
	Triangle t;
	std::stringstream word(line);
		while (!f1.eof())//读到文件末尾
		{
			f1 >> kind;
			switch (kind) {
			case 1:
				f1.getline(line, 100);
				f1.getline(line, 100);

				word >> x1;
				word >> y1;
				word >> ra;
				try{if (!ra)//如果半径没读入则报错，改为默认数据继续执行
				{
					throw ra;	
				}}
				catch(int &ra)
				{
					ra = 100;
					outtextxy(800, 50, "半径缺少，默认为100");
				}
				f1 >> co >> flag;
				c.setxy(x1, y1);
				c.setr(ra);
				try{
				if (co == "white")
					c.setCcolor(255, 255, 255);
				else if (co == "black")
					c.setCcolor(0, 0, 0);
				else if (co == "yellow")
					c.setCcolor(0, 0, 255);
				else if (co == "red")
					c.setCcolor(220, 20, 60);
				else if (co == "blue")
					c.setCcolor(0, 0, 255);
				else if (co == "green")
					c.setCcolor(0, 255, 0);
				else {
					throw c;//如果颜色错误，报错，并设为默认颜色
				}
				}
				catch (Circle &c)
				{
					c.setCcolor(255, 255, 255);
					outtextxy(800, 10, "颜色异常，默认为白色");
				}
				co.clear();
				c.setFlag(flag);
				c.draw();
				break;
			case 2:
				f1 >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> co >> flag;
				t.setxy(x1, y1, x2, y2, x3, y3);
				try{
				if (co == "white")
					t.setTcolor(255, 255, 255);
				else if (co == "black")
					t.setTcolor(0, 0, 0);
				else if (co == "yellow")
					t.setTcolor(0, 0, 255);
				else if (co == "red")
					t.setTcolor(220, 20, 60);
				else if (co == "blue")
					t.setTcolor(0, 0, 255);
				else if (co == "green")
					t.setTcolor(0, 255, 0);
				else {
					throw t;//如果颜色错误，报错，并设为默认颜色
				}
				}
				catch (Triangle &t)
				{
					t.setTcolor(255, 255, 255);
					outtextxy(800, 10, "颜色异常，默认为白色");
				}
				co.clear();
				t.setFlag(flag);
				t.draw();
				break;
			case 3:
				f1 >> x1 >> y1 >> x2 >> y2 >> co >> flag;
				r.setxy1(x1, y1);
				r.setxy2(x2, y2);
				try{
				if (co == "white")
					r.setRcolor(255, 255, 255);
				else if (co == "black")
					r.setRcolor(0, 0, 0);
				else if (co == "yellow")
					r.setRcolor(0, 0, 255);
				else if (co == "red")
					r.setRcolor(220, 20, 60);
				else if (co == "blue")
					r.setRcolor(0, 0, 255);
				else if (co == "green")
					r.setRcolor(0, 255, 0);
				else {
					throw r;//如果颜色错误，报错，并设为默认颜色
				}
				}
				catch(Rectanglee &r)
				{
					r.setRcolor(255, 255, 255);
					outtextxy(800, 10, "颜色异常，默认为白色");
				}
				co.clear();
				r.setFlag(flag);
				r.draw();
				break;
			default:
				outtextxy(800, 30, "图形异常，默认为矩形");
				f1 >> x1 >> y1 >> x2 >> y2 >> co >> flag;
				r.setxy1(x1, y1);
				r.setxy2(x2, y2);
				try{
				if (co == "white")
					r.setRcolor(255, 255, 255);
				else if (co == "black")
					r.setRcolor(0, 0, 0);
				else if (co == "yellow")
					r.setRcolor(0, 0, 255);
				else if (co == "red")
					r.setRcolor(220, 20, 60);
				else if (co == "blue")
					r.setRcolor(0, 0, 255);
				else if (co == "green")
					r.setRcolor(0, 255, 0);
				else {
					throw r;//如果颜色错误，报错，并设为默认颜色
				}
				}
				catch (Rectanglee &r)
				{
					r.setRcolor(255, 255, 255);
					outtextxy(800, 10, "颜色异常，默认为白色");
				}
				co.clear();
				r.setFlag(flag);
				r.draw();//画图
				break;
			}
		}
		
	f1.close();
	return 0;
}
int main2()
{
	std::fstream f2;
	f2.open("f2.txt", std::ios::out);//打开文件
	int kind = 0;//图形
	int x1 = 0, x2 = 0, x3 = 0;//坐标
	int y1 = 0, y2 = 0, y3 = 0;
	int ra = 0;//半径
	std::string co;//颜色
	int flag = 0;//是否填充
	Circle c;
	Rectanglee r;
	Triangle t;

	std::string dataput;
	std::istringstream sss;

	//用inputbox_getline获得一串字符串，然后压入字符串流，再输入到对应的变量中，字符串和流用过后要清空
	inputbox_getline("选择图形", "请选择图形的类型：\n0、退出\n1、圆形\n2、三角形\n3、矩形\n ", const_cast<char*>(dataput.c_str()), 50);
	sss.str(dataput.c_str());
	sss >> kind;
	sss.clear();//清空缓冲区  
	dataput.clear();

	while (kind!=0)//kind==0时退出
	{
		f2 << kind << std::endl;//输出到文件
	
		switch (kind) {
		case 1://圆
			inputbox_getline("坐标xy、半径：", "请输入圆的坐标xy（0~1000）、半径：", const_cast<char*>(dataput.c_str()), 100);
			sss.str(dataput.c_str());
			sss >> x1 >> y1 >> ra;
			sss.clear();//清空缓冲区  
			dataput.clear();
			inputbox_getline("颜色", "请输入圆的颜色：\nwhite、black、yellow、red、blue、green", const_cast<char*>(dataput.c_str()), 50);
			co.assign(dataput.c_str());
			dataput.clear();
			inputbox_getline("是否填充", "请输入圆的是否填充：\n（填充：1	不填充：0）", const_cast<char*>(dataput.c_str()), 50);
			sss.str(dataput.c_str());
			sss >> flag;
			sss.clear();//清空缓冲区  
			dataput.clear();
			f2 << x1 << ' ' << y1 << ' ' << ra << std::endl << co << ' ' << flag << std::endl;//

			c.setxy(x1, y1);
			c.setr(ra);
			if (co == "white")
				c.setCcolor(255, 255, 255);
			else if (co == "black")
				c.setCcolor(0, 0, 0);
			else if (co == "yellow")
				c.setCcolor(0, 255, 255);
			else if (co == "red")
				c.setCcolor(0, 0, 255);
			else if (co == "blue")
				c.setCcolor(255, 255, 0);
			else if (co == "green")
				c.setCcolor(0, 255, 0);
			else {
				//error
			}
			co.clear();
			c.setFlag(flag);
			c.draw();
			break;
		case 2://三角形
			char s[100];
			//inputbox_getline("三点坐标xy", "请输入三角形的三点坐标xy（0~1000）", const_cast<char*>(dataput.c_str()), 200);
			//sss.str(dataput.c_str());
			//这里如果用string，一旦数值变大，就会奔溃，所以改用char数组
			inputbox_getline("三点坐标xy", "请输入三角形的三点坐标xy（0~1000）", s, 200);
			sss.str(s);
			sss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
			sss.clear();//清空缓冲区  
			dataput.clear();
			inputbox_getline("颜色", "请输入三角形的颜色：\nwhite、black、yellow、red、blue、green", const_cast<char*>(dataput.c_str()), 50);
			co.assign(dataput.c_str());
			dataput.clear();
			inputbox_getline("是否填充", "请输入三角形的是否填充：\n（填充：1	不填充：0）", const_cast<char*>(dataput.c_str()), 50);
			sss.str(dataput.c_str());
			sss >> flag;
			sss.clear();//清空缓冲区  
			dataput.clear();
			f2 << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << x3 << ' ' << y3 << std::endl << co << ' ' << flag << std::endl;

			t.setxy(x1, y1, x2, y2, x3, y3);
			if (co == "white")
				t.setTcolor(255, 255, 255);
			else if (co == "black")
				t.setTcolor(0, 0, 0);
			else if (co == "yellow")
				t.setTcolor(0, 255, 255);
			else if (co == "red")
				t.setTcolor(0, 0, 255);
			else if (co == "blue")
				t.setTcolor(255, 255, 0);
			else if (co == "green")
				t.setTcolor(0, 255, 0);
			else {
				//error
			}
			co.clear();
			t.setFlag(flag);
			t.draw();
			break;
		case 3://矩形
			inputbox_getline("两点坐标xy（0~1000）", "请输入矩形的两点坐标xy（0~1000）", const_cast<char*>(dataput.c_str()), 50);
			sss.str(dataput.c_str());
			sss >> x1 >> y1 >> x2 >> y2;
			sss.clear();//清空缓冲区  
			dataput.clear();
			inputbox_getline("颜色", "请输入矩形的颜色：\nwhite、black、yellow、red、blue、green", const_cast<char*>(dataput.c_str()), 50);
			co.assign(dataput.c_str());
			dataput.clear();
			inputbox_getline("是否填充", "请输入矩形的是否填充：\n（填充：1	不填充：0）", const_cast<char*>(dataput.c_str()), 50);
			sss.str(dataput.c_str());
			sss >> flag;
			sss.clear();//清空缓冲区  
			dataput.clear();
			f2 << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << std::endl << co << ' ' << flag << std::endl;

			r.setxy1(x1, y1);
			r.setxy2(x2, y2);
			if (co == "white")
				r.setRcolor(255, 255, 255);
			else if (co == "black")
				r.setRcolor(0, 0, 0);
			else if (co == "yellow")
				r.setRcolor(0, 255, 255);
			else if (co == "red")
				r.setRcolor(0, 0, 255);
			else if (co == "blue")
				r.setRcolor(255, 255, 0);
			else if (co == "green")
				r.setRcolor(0, 255, 0);
			else {
				//error
			}
			co.clear();
			r.setFlag(flag);
			r.draw();
			break;
		}
		ege::getch();//暂停以保证图形不被交互框挡到
		inputbox_getline("选择图形", "请选择图形的类型：\n0、退出\n1、圆形\n2、三角形\n3、矩形\n ", const_cast<char*>(dataput.c_str()), 50);
		if ("" == dataput)//因为getch（）不吸收回车，所以可能会把下一个输入跳过，所以如果dataput没值，需要重新显示输入框
		{
			inputbox_getline("选择图形", "请选择图形的类型：\n0、退出\n1、圆形\n2、三角形\n3、矩形\n ", const_cast<char*>(dataput.c_str()), 50);
		}
		sss.str(dataput.c_str());
		sss >> kind;
		sss.clear();//清空缓冲区  
		dataput.clear();	
	}
	f2.close();//关闭文件
	return 0;
}