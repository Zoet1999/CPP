
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
};

