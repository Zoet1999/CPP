#pragma once
#include <new>
#include <string>
class MyBadAlloc:public std::bad_alloc
{
public:
	MyBadAlloc();	
	MyBadAlloc(std::string s);
	~MyBadAlloc();
	void setS(std::string s);
	std::string getS();
private:
	std::string s;

};

