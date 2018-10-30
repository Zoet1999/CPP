#include "stdafx.h"
#include "Shape.h"
#include "graphics.h"
int Shape::ShapeNumber = 0;

Shape::Shape()//构造
{
	ShapeNumber++;//计数加一
}


Shape::~Shape()//析构
{
	ShapeNumber--;//计数减一
	xyprintf(60, 310, "%d    ", ShapeNumber);//显示图形数量
}

int Shape::getShapeNumber()
{
	return ShapeNumber;
}


