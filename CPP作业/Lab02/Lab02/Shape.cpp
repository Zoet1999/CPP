#include "stdafx.h"
#include "Shape.h"
#include "graphics.h"
int Shape::ShapeNumber = 0;

Shape::Shape()//����
{
	ShapeNumber++;//������һ
}


Shape::~Shape()//����
{
	ShapeNumber--;//������һ
	xyprintf(60, 310, "%d    ", ShapeNumber);//��ʾͼ������
}

int Shape::getShapeNumber()
{
	return ShapeNumber;
}


