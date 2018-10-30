#pragma once
#include "Shape.h"
#include "graphics.h"
#include "Point.h"
#include "Color.h"

class Rectanglee :
	public Shape
{
private:
	Point xy1_;//������ 
	Point xy2_;//������ 
	Color Rcolor_;//��ɫ 
	static int RectangleNumber;//��¼���ε�����
public:
	Rectanglee();// �޲ι���Ĭ�ϳ�ʼ�����ε������ꡢ�����ꡢ��ɫ 
	Rectanglee(int x1, int y1, int x2, int y2, int x, int y, int z);// ��ʼ�����ε������ꡢ�����ꡢ��ɫ 
	Rectanglee(Rectanglee &r);
	~Rectanglee();
	void setxy1(int x, int y);//�޸������� 
	void setxy2(int x, int y);//�޸������� 
	void setRcolor(int x, int y, int z);//�޸���ɫ 
	Point getxy1();//���������� 
	Point getxy2();//���������� 
	Color getRcolor();//������ɫ 
	static int getRectangleNumber();//���ؾ��ε�����
	void draw();//������ 
	void setFlag(bool a);// �����Ƿ���� 
};
