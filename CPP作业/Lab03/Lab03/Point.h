
#pragma once
//定义一个点类来表示二维坐标，包括两个成员变量，分别表示横、纵坐标。 
class Point
{
private:
	static int PointNumber;//记录点的数量
	int x_;//点的坐标xy 
	int y_;
public:
	Point();//无参构造函数初始化默认xy为 0 0 
	Point(int x, int y);//有参构造函数初始化xy 
	Point(Point &p);//拷贝构造函数
	~Point();//析构函数

	//setter
	void setxy(const int x, const int y);//修改坐标 

	//getter
	int getx();//返回坐标x 
	int gety();//返回坐标y 
	static int getPointNumber();//返回点的数量
};

