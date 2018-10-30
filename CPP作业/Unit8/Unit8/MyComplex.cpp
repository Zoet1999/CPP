#include "stdafx.h"
#include "MyComplex.h"
#include <stdexcept>

MyComplex::MyComplex()
{
	real = 0;
	imaginary = 0;
}

MyComplex::MyComplex(int r, int i)
{
	real = r;
	imaginary = i;
}

MyComplex::~MyComplex()
{
}

std::string MyComplex::toString()
{
	std::string a = std::to_string(real);
	std::string b = std::to_string(imaginary);
	std::string c;
	if(imaginary<0)
	{
		if (real == 0)
			c = b + "i";
		else
		 c = a + b + "i";
	}
	else if(imaginary>0) {
		if (real == 0)
			c = b + "i";
		else
	c = a + "+" + b + "i";
	}
	else {
		return a;
	}
	return c;
}

MyComplex MyComplex::operator + (MyComplex n)
{
	int a = this->real + n.real;
	int b = this->imaginary + n.imaginary;
	return MyComplex(a, b);
}
MyComplex MyComplex::operator += (MyComplex n)
{
	this->real+= n.real;
	this->imaginary +=  n.imaginary;
	return MyComplex(real, imaginary);
}

int& MyComplex::operator [](int index)
{
	if (index == 0)
	{
		return real;
	}
	else if (index == 1)
	{
		return imaginary;
	}
	else
	{
		throw std::out_of_range("index must be 0 or 1");
	}

}

MyComplex MyComplex::operator ++()
{
	this->real++;
	return *this;
}
MyComplex MyComplex::operator ++(int flag)
{
	MyComplex a = *this;
	this->real++;
	return a;
}
std::ostream& operator <<(std::ostream& os, MyComplex m)
{
	os <<m.toString();
	return os;
}

MyComplex MyComplex::operator =(MyComplex m)
{
	this->real = m.real;
	this->imaginary = m.imaginary;
	return *this;
}