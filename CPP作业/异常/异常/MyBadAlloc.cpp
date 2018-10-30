#include "stdafx.h"
#include "MyBadAlloc.h"


MyBadAlloc::MyBadAlloc()
{
}

MyBadAlloc::MyBadAlloc(std::string s)
{
	this->s = s;
}

MyBadAlloc::~MyBadAlloc()
{
}

void MyBadAlloc::setS(std::string s)
{
	this->s = s;
}
std::string MyBadAlloc::getS()
{
	return s;
}