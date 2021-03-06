// Unit 07.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Person.h"
int main()
{
	int num1 = 1,num2;
	double dnum1 = 1.5,dnum2=2.5;
	int a[3] = { 1,2,3 };
	char m[] = {'a','a','a','\0'};
	Person p(m);
	std::fstream f("inout.dat", std::ios::out | std::ios::binary);
	f.write(reinterpret_cast<char *>(&num1), sizeof(num1));
	f.write(reinterpret_cast<char *>(&dnum1), sizeof(dnum1));
	f.write(reinterpret_cast<char *>(a), sizeof(a));
	f.write(reinterpret_cast<char *>(&p), sizeof(Person));
	f.seekg(sizeof(int),std::ios::beg);
	f.write(reinterpret_cast<char *>(&dnum2), sizeof(dnum2));
	f.close();
	f.open("inout.dat", std::ios::in | std::ios::binary);
	f.seekp(sizeof(int)+ sizeof(double)+sizeof(int));
	f.read(reinterpret_cast<char *>(&num2), sizeof(num2));
	std::cout << num2 << std::endl;
	f.close();
    return 0;
}

