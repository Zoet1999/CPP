#pragma once
// 定义一个颜色类来表示所绘图形的颜色，包括两个成员变量，分别表示颜色和是否填充。
class Color
{
private:
	int co_;	//记录颜色 
	bool flag_;//是否填充 
	static int ColorNumber;//记录颜色数量
public:
	Color();// 无参构造函数 
	Color(int x, int y, int z);//初始化颜色
	Color(int a);
	Color(Color &c);//拷贝构造函数
	~Color();//析构函数
	bool getFlag();//返回是否填充 
	int getColor();//返回颜色 
	void setColor(int x, int y, int z);//修改颜色 
	void setFlag(bool a);//修改是否填充 
	void setC();//设置当前颜色为填充色与线条色 
	static int getColorNumber();//返回颜色数量
};

