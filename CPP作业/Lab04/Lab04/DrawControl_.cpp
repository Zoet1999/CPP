#include "stdafx.h"
#include "DrawControl_.h"
#include "graphics.h"
DrawControl::DrawControl()
{
	inti(1, 1);//无参构造默认初始化为 1*1 
}
DrawControl::DrawControl(int w, int h)
{
	inti(w, h);//初始化绘图环境
}
void DrawControl::inti(int w, int h)
{
	initgraph(w, h);//初始化绘图环境 
}
void DrawControl::close()
{
	closegraph();//关闭绘图环境 
}
void DrawControl::set(int left,
	int top,
	int right,
	int bottom,
	int clip = 1)//修改设置绘图环境 
{
	setviewport(left, top, right, bottom, clip);
}
