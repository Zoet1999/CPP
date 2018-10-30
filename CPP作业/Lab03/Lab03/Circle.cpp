#include "stdafx.h"
#include "Circle.h"
#include "graphics.h"
#include "Point.h"
#include "Color.h"

int Circle::CircleNumber = 0;

//�޲ι��캯��
Circle::Circle() :Cxy_(0, 0), r_(1), Ccolor_(255, 255, 255) //Ĭ�ϳ�ʼ��Բ�����ꡢ�뾶����ɫ 
{
	CircleNumber++;
}
//�вι��캯��
Circle::Circle(int x, int y, int cr, int cx, int cy, int cz) : Cxy_(x, y), r_(cr), Ccolor_(cx, cy, cz) //��ʼ��Բ�����ꡢ�뾶����ɫ 
{
	CircleNumber++;
}
//�������캯��
Circle::Circle(Circle &c) : Cxy_(c.getxy().getx(), c.getxy().gety()), r_(c.getr()), Ccolor_(c.getCcolor().getColor())
{
	CircleNumber++;
}
//��������
Circle::~Circle()
{
	CircleNumber--;
	//xyprintf(60, 330, "%d    ", CircleNumber);
}

//setter
void Circle::setxy(int x, int y) {
	Cxy_ = Point(x, y);
}
void Circle::setr(int cr) { r_ = cr; }
void Circle::setCcolor(int x, int y, int z) { Ccolor_.setColor(x, y, z); }
void Circle::setFlag(bool a) //�����Ƿ���� 
{
	Ccolor_.setFlag(a);
}


//getter
Point Circle::getxy()// �޸����� 
{
	return Cxy_;
}
int Circle::getr()// �޸İ뾶 
{
	return r_;
}
Color Circle::getCcolor()// �޸���ɫ 
{
	return Ccolor_;
}
int Circle::getCircleNumber()//����Բ������
{
	return CircleNumber;
}

//other
void Circle::draw()
{
	Ccolor_.setC();//����Բ����ɫΪ���ɫ������ɫ 
	if (Ccolor_.getFlag() == false)
		circle(getxy().getx(), getxy().gety(), getr());//��������Բ 
	else
		fillellipse(getxy().getx(), getxy().gety(), getr(), getr());//����ʵ��Բ 
}
