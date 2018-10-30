#include "stdafx.h"
#include "Rectangle_.h"
#include "graphics.h"
#include "Point_.h"
#include "Color_.h"
#include <stdexcept>


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
Rectanglee::Rectanglee(Rectanglee &r) : xy1_(r.getxy1().getx(), r.getxy1().gety()), xy2_(r.getxy1().getx(), r.getxy2().gety()), Rcolor_(r.getRcolor()[1], r.getRcolor()[2], r.getRcolor()[3])
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
		bar(getxy1()[0], getxy1()[1], getxy2()[0], getxy2()[1]);//��ʵ�ľ��� 
	else
		rectangle(getxy1()[0], getxy1()[1], getxy2()[0], getxy2()[1]);//�����ľ��� 
}

//���������
bool Rectanglee::operator <(const Rectanglee &r)
{
	int s1 = (xy1_[0] - xy2_[0])*(xy1_[1] - xy2_[1]);
	int s2 = (r.xy1_[0] - r.xy2_[0])*(r.xy1_[1] - r.xy2_[1]);
	if (s1<s2)
		return true;
	else
		return false;
}
bool Rectanglee::operator >(const Rectanglee &r)
{
	int s1 = (xy1_[0] - xy2_[0])*(xy1_[1] - xy2_[1]);
	int s2 = (r.xy1_[0] - r.xy2_[0])*(r.xy1_[1] - r.xy2_[1]);
	if (s1>s2)
		return true;
	else
		return false;
}
bool Rectanglee::operator <=(const Rectanglee &r)
{
	int s1 = (xy1_[0] - xy2_[0])*(xy1_[1] - xy2_[1]);
	int s2 = (r.xy1_[0] - r.xy2_[0])*(r.xy1_[1] - r.xy2_[1]);
	if (s1<=s2)
		return true;
	else
		return false;
}
bool Rectanglee::operator >=(const Rectanglee &r)
{
	int s1 = (xy1_[0] - xy2_[0])*(xy1_[1] - xy2_[1]);
	int s2 = (r.xy1_[0] - r.xy2_[0])*(r.xy1_[1] - r.xy2_[1]);
	if (s1>=s2)
		return true;
	else
		return false;
}
bool Rectanglee::operator ==(const Rectanglee &r)
{
	if (xy1_==r.xy1_&&xy2_==r.xy2_&&Rcolor_==r.Rcolor_)
		return true;
	else
		return false;
}
Rectanglee& Rectanglee::operator =(const Rectanglee &r)
{
	xy1_ = r.xy1_;
	xy2_ = r.xy2_;
	Rcolor_ = r.Rcolor_;
	return *this;
}
int Rectanglee::operator [](int index) const
{
	switch (index)
	{
	case 0:
		return xy1_[0];
		break;
	case 1:
		return xy1_[1];
		break;
	case 2:
		return xy2_[0];
		break;
	case 3:
		return xy2_[1];
		break;
	default:
		throw std::out_of_range("index must be 0 to 3");
		break;
	}
}