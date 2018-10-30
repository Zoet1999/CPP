#pragma once
// ����һ����ɫ������ʾ����ͼ�ε���ɫ������������Ա�������ֱ��ʾ��ɫ���Ƿ���䡣
class Color
{
private:
	int co_;		//��¼��ɫ 
	int x_;
	int y_;
	int z_;
	bool flag_;		//�Ƿ���� 
	static int ColorNumber;//��¼��ɫ����
public:
	Color();// �޲ι��캯�� 
	Color(int x, int y, int z);//��ʼ����ɫ
	//Color(int a);
	Color(Color &c);//�������캯��
	~Color();//��������

	 //getter
	bool getFlag();//�����Ƿ���� 
	int getColor();//������ɫ 
	static int getColorNumber();//������ɫ����

	//setter
	void setColor(int x, int y, int z);//�޸���ɫ 
	void setFlag(bool a);//�޸��Ƿ���� 
	void setC();//���õ�ǰ��ɫΪ���ɫ������ɫ 

	//���������
	Color& operator =(const Color& c);
	bool operator ==(const Color& c);
	bool operator !=(const Color& c);
	int operator[](int index) const;
};

