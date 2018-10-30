#pragma once
class Shape
{
	static int ShapeNumber;//记录图像数量
public:
	Shape();
	~Shape();
	virtual void draw() = 0;//纯虚函数 

							//getter
	static int getShapeNumber();//返回图像数量
};

