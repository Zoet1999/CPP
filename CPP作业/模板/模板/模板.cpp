// 模板.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
template <typename T>
class Array
{
private:
	T * a_;
	int len_;
public:
	Array(T* a, int len);
	
	T sum();

	int seek(T key);

	T* reverse();
	
	T* print();
};
template <typename T>
Array<T>::Array(T* a, int len)
{
	len_ = len;
	a_ = new(T);
	for (int i = 0; i < len_; i++)
	{
		a_[i] = a[i];
	}
}
template <typename T>
T Array<T>::sum()
{
	T s = 0;
	for (int i = 0; i < len_; i++)
	{
		s = a_[i];
	}
	return s;
}
template <typename T>
int Array<T>::seek(T key)
{
	for (int i = 0; i < len_; i++)
	{
		if (a_[i] == key)
			return i;
	}
	return - 1;
}
template <typename T>
T* Array<T>::reverse()
{
	for (int i = 0; i < len_ / 2; i++)
	{
		T t = a_[i];
		a_[i] = a_[len_ - 1 - i];
		a_[len_ - 1 - i] = t;
	}
	return a_;
}
template <typename T>
T* Array<T>::print()
{
	for (int i = 0; i < len_; i++)
	{
		std::cout << a_[i] << std::endl;
	}
	return a_;
}
int main()
{
	int a[3] = { 1,2,3 };
	double b[3] = { 1.1,2.2,3.3 };
	Array<int> c(a, 3);
	Array<double> d(b, 3);
	c.print();
	d.print();
	c.reverse();
	d.reverse();
	c.print();
	d.print();
	std::cout << c.sum() << std::endl;
	std::cout << d.sum() << std::endl;
	std::cout << c.seek(2) << std::endl;
	std::cout << d.seek(2.2) << std::endl;
	return 0;
}
