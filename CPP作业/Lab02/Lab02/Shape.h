#pragma once
class Shape
{
	static int ShapeNumber;//��¼ͼ������
public:
	Shape();
	~Shape();
	virtual void draw() = 0;//���麯�� 
	static int getShapeNumber();//����ͼ������
};

