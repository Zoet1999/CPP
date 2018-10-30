#include "stdafx.h"
#include "Rectangle.h"
#include "graphics.h"
#include "Point.h"
#include "Color.h"



int Rectanglee::RectangleNumber = 0;
// �޲ι���Ĭ�ϳ�ʼ�����ε������ꡢ�����ꡢ��ɫ 
Rectanglee::Rectanglee() :xy1_(0, 0), xy2_(0, 0), Rcolor_(255, 255, 255)  
{
	RectangleNumber++;
}
// ��ʼ�����ε������ꡢ�����ꡢ��ɫ 
Rectanglee::Rectanglee(int x1, int y1, int x2, int y2, int x, int y, int z) : xy1_(x1, y1), xy2_(x2, y2), Rcolor_(x, y, z) 
{
	RectangleNumber++;
}
// �������캯��
Rectanglee::Rectanglee(Rectanglee &r) : xy1_(r.getxy1().getx(), r.getxy1().gety()), xy2_(r.getxy1().getx(), r.getxy2().gety()), Rcolor_(r.getRcolor().getColor())
{
	RectangleNumber++;
}
// ��������
Rectanglee::~Rectanglee()
{
	RectangleNumber--;

	//xyprintf(60, 350, "%d    ", RectangleNumber);
}

//setter
void Rectanglee::setxy1(int x, int y) { xy1_ = Point(x, y); }//�޸������� 
void Rectanglee::setxy2(int x, int y) { xy2_ = Point(x, y); }//�޸������� 
void Rectanglee::setRcolor(int x, int y, int z) { Rcolor_.setColor(x, y, z); }//�޸���ɫ 
void Rectanglee::setFlag(bool a)//�����Ƿ���� 
{
	Rcolor_.setFlag(a);
}

//getter
Point Rectanglee::getxy1()//���������� 
{
	return xy1_;
}
Point Rectanglee::getxy2()//���������� 
{
	return xy2_;
}
Color Rectanglee::getRcolor()//������ɫ 
{
	return Rcolor_;
}
int Rectanglee::getRectangleNumber()//���ؾ��ε�����
{
	return RectangleNumber;
}

//other
void Rectanglee::draw()
{
	Rcolor_.setC();//���þ��ε���ɫΪ���ɫ������ɫ 
	if (Rcolor_.getFlag() == true)
		bar(getxy1().getx(), getxy1().gety(), getxy2().getx(), getxy2().gety());//��ʵ�ľ��� 
	else
		rectangle(getxy1().getx(), getxy1().gety(), getxy2().getx(), getxy2().gety());//�����ľ��� 
}