#pragma once
//定义一个绘图控制类，用于初始化绘图环境、终止绘图模式、设置绘图窗口大小等
class DrawControl
{
public:
	void inti(int w, int h);//初始化当前视图 
	DrawControl();//无参构造函数  
	DrawControl(int w, int h);//有参构造函数 初始化当前视图 
	void close();//关闭图形环境。 
	void set(int left, int top, int right, int bottom, int clip);//修改设置绘画环境。
};
