// Unit8.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include "MyComplex.h"


int main()
{
	MyComplex m(3, 2);
	MyComplex n;
	n = m + n + m;
	std::cout << n<<std::endl;
    return 0;
}

