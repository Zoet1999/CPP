#include "stdafx.h"
#include "Shape_.h"
#include "graphics.h"
int Shape::ShapeNumber = 0;

Shape::Shape()
{
	ShapeNumber++;
}

Shape::~Shape()
{
	ShapeNumber--;
	//xyprintf(60, 310, "%d    ", ShapeNumber);
}

int Shape::getShapeNumber()
{
	return ShapeNumber;
}
