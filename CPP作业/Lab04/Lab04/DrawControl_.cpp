#include "stdafx.h"
#include "DrawControl_.h"
#include "graphics.h"
DrawControl::DrawControl()
{
	inti(1, 1);//�޲ι���Ĭ�ϳ�ʼ��Ϊ 1*1 
}
DrawControl::DrawControl(int w, int h)
{
	inti(w, h);//��ʼ����ͼ����
}
void DrawControl::inti(int w, int h)
{
	initgraph(w, h);//��ʼ����ͼ���� 
}
void DrawControl::close()
{
	closegraph();//�رջ�ͼ���� 
}
void DrawControl::set(int left,
	int top,
	int right,
	int bottom,
	int clip = 1)//�޸����û�ͼ���� 
{
	setviewport(left, top, right, bottom, clip);
}
