
#pragma once
//����һ����������ʾ��ά���꣬����������Ա�������ֱ��ʾ�ᡢ�����ꡣ 
class Point
{
private:
	static int PointNumber;//��¼�������
	int x_;//�������xy 
	int y_;
public:
	Point();//�޲ι��캯����ʼ��Ĭ��xyΪ 0 0 
	Point(int x, int y);//�вι��캯����ʼ��xy 
	Point(Point &p);//�������캯��
	~Point();//��������

			 //setter
	void setxy(const int x, const int y);//�޸����� 

										 //getter
	int getx();//��������x 
	int gety();//��������y 
	static int getPointNumber();//���ص������

	//���������
	Point& operator +(Point& p);
	Point& operator =(const Point& p);
	bool operator ==(const Point& p);
	bool operator !=(const Point& p);
	int operator [](int index) const;
	Point& operator +=(const Point& p);
};

