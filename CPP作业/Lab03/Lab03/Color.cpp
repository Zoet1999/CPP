
#include "stdafx.h"
#include "Color.h"
#include "graphics.h"

int Color::ColorNumber = 0;

//�޲ι��캯��
Color::Color()
{
	co_ = RGB(255, 255, 255);//��ʼ��Ĭ����ɫΪ��ɫ 
	flag_ = false;
	ColorNumber++;
}
//�вι��캯��
Color::Color(int x, int y, int z)//��ʼ����ɫ 
{
	co_ = RGB(x, y, z);
	flag_ = false;
	ColorNumber++;
}
//�вι��캯��
Color::Color(int a)
{
	co_ = a;
	flag_ = false;
	ColorNumber++;
}
//�������캯��
Color::Color(Color &c)
{
	co_ = c.getColor();
	flag_ = c.getFlag();
	ColorNumber++;
}
//��������
Color::~Color()
{
	ColorNumber--;
	//xyprintf(60, 290, "%d    ", ColorNumber);
}

//setter
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

//getter
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
