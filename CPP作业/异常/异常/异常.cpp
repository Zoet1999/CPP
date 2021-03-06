// 异常.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <new>
#include "MyBadAlloc.h"

int f1();
int f2();

int main()
{
		try { f1(); }
	
	catch (MyBadAlloc& m)
	{
		std::cout << m.getS() << std::endl;
	}

	try { f2(); }
	catch (std::bad_alloc)
	{
		std::cout << "bad_alloc" << std::endl;
	}
	    return 0;
}

int f1()
{
	while(int *a = new int[10000000]){
		throw MyBadAlloc("MyBadAlloc");
	}
	throw 100;
}
int f2()
{
	while (1) {
		int *a = new int[10000000];
	}
	throw 100;
}
