#include "stdafx.h"
#include "Circle_.h"
#include "graphics.h"
#include "Point_.h"
#include "Color_.h"
#include <stdexcept>

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
Circle::Circle(Circle &c) : Cxy_(c.getxy().getx(), c.getxy().gety()), r_(c.getr()), Ccolor_(c.getCcolor()[1], c.getCcolor()[2], c.getCcolor()[3])
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
		circle(getxy()[0], getxy()[1], getr());//��������Բ 
	else
		fillellipse(getxy()[0], getxy()[1], getr(), getr());//����ʵ��Բ 
}

//���������
bool Circle::operator <(const Circle &r)
{
	if (r_ < r.r_)
		return true;
	else
		return false;
}
bool Circle::operator >(const Circle &r)
{
	if (r_ >r.r_)
		return true;
	else
		return false;
}
bool Circle::operator <=(const Circle &r)
{
	if (r_ <= r.r_)
		return true;
	else
		return false;
}
bool Circle::operator >=(const Circle &r)
{
	if (r_ >= r.r_)
		return true;
	else
		return false;
}
bool Circle::operator ==(const Circle &r)
{
	if (r_ == r.r_&&Cxy_==r.Cxy_&&Ccolor_==r.Ccolor_)
		return true;
	else
		return false;
}
Circle& Circle::operator =(const Circle &r)
{
	r_ = r.r_;
	Cxy_ = r.Cxy_;
	Ccolor_ = r.Ccolor_;
	return *this;
}
int Circle::operator [](int index) const
{
	if (0 == index || 1 == index)
		return Cxy_[index];
	else
		throw std::out_of_range("index must be 0 or 1");
	return 0;
}