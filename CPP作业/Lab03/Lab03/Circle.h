#pragma once
#include "Shape.h"
#include "graphics.h"
#include "Point.h"
#include "Color.h"
#include "Shape.h"
//����һ��Բ������ʾԲ�Σ�����������Ա�������ֱ��ʾԲ�����ꡢ�뾶����ɫ�� 
class Circle :
	public Shape
{
private:
	int r_;//�뾶 
	Point Cxy_;//Բ�� 
	Color Ccolor_;//��ɫ 
	static int CircleNumber;//��¼Բ������
public:
	//ctor and dtor
	Circle();// �޲ι���Ĭ�ϳ�ʼ��Բ�����ꡢ�뾶����ɫ 
	Circle(int x, int y, int r, int cx, int cy, int cz);//��ʼ��Բ�����ꡢ�뾶����ɫ 
	Circle(Circle &c);//�������캯��
	~Circle();//��������

	//setter
	void setxy(int x, int y);// �޸����� 
	void setr(int r);// �޸İ뾶 
	void setCcolor(int x, int y, int z);// �޸���ɫ 
	void setFlag(bool a);//�����Ƿ���� 

	//getter
	Point getxy();//�������� 
	int getr();// ���ذ뾶 
	Color getCcolor();//������ɫ 
	static int getCircleNumber();//����Բ������

	 //other
	void draw();//����Բ
};

