#pragma once
//����һ����ͼ�����࣬���ڳ�ʼ����ͼ��������ֹ��ͼģʽ�����û�ͼ���ڴ�С��
class DrawControl
{
public:
	void inti(int w, int h);//��ʼ����ǰ��ͼ 
	DrawControl();//�޲ι��캯��  
	DrawControl(int w, int h);//�вι��캯�� ��ʼ����ǰ��ͼ 
	void close();//�ر�ͼ�λ����� 
	void set(int left, int top, int right, int bottom, int clip);//�޸����û滭������
};
