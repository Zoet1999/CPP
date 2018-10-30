#pragma once
#include <string>
#include <iostream>
class MyComplex
{
	int real;
	int imaginary;
public:
	MyComplex();
	MyComplex(int r,int i);
	~MyComplex();
	std::string toString();
	MyComplex operator + (MyComplex n);
	MyComplex operator += (MyComplex n);
	int& operator [](int index);
	MyComplex operator ++();
	MyComplex operator ++(int flag);
	friend std::ostream& operator <<(std::ostream& os, MyComplex m);
	MyComplex operator =(MyComplex m);
};
