#include "stdafx.h"
#include "Color.h"
#include "graphics.h"

int Color::ColorNumber = 0;

Color::Color()
{
	co_ = RGB(255, 255, 255);//��ʼ��Ĭ����ɫΪ��ɫ 
	flag_ = false;
	ColorNumber++; //������һ
}
Color::Color(int x, int y, int z)//��ʼ����ɫ 
{
	co_ = RGB(x, y, z);
	flag_ = false;
	ColorNumber++;//������һ
}
Color::Color(int a)
{
	co_ = a;
	flag_ = false;
	ColorNumber++;//������һ
}
Color::Color(Color &c)//�������캯��
{
	co_ = c.getColor();
	flag_ = c.getFlag();
	ColorNumber++;//������һ
}
Color::~Color()//��������
{
	ColorNumber--;//������һ
	xyprintf(60, 290, "%d    ", ColorNumber);//��ʾ��ɫ����
}

void Color::setColor(int x, int y, int z)//�޸���ɫ 
{
	co_ = RGB(x, y, z);
}
void Color::setC()
{
	setcolor(co_);//���õ�ǰ��ɫΪ����ɫ 
	setfillcolor(co_);//���õ�ǰ��ɫΪ���ɫ
}
void Color::setFlag(bool a)//�޸��Ƿ����
{
	flag_ = a;
}
bool Color::getFlag()//�����Ƿ����
{
	return flag_;
}
int Color::getColorNumber()//������ɫ����
{
	return ColorNumber;
}
int Color::getColor()//������ɫ 
{
	return co_;
}
