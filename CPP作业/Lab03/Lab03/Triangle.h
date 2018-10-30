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
	Color Tcolor_;//��ɫ 
	static int TriangleNumber;//��¼�����ε�����
public:
	Triangle();
	Triangle(int x1, int y1, int x2, int y2, int x3,int y3,int x, int y, int z);
	Triangle(Triangle &t);
	~Triangle();

	//setter
	void setFlag(bool a);// �����Ƿ���� 
	void setxy(int x1, int y1, int x2, int y2, int x3, int y3);
	void setTcolor(int x, int y, int z);//�޸���ɫ 

	//getter
	Point getxy1();
	Point getxy2();
	Point getxy3();
	Color getTcolor();//������ɫ 
	static int getTriangleNumber();//���������ε�����

	//other
	void draw();//��������
	
};

