// 文件流.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	/*std::fstream f1;
	f1.open("number.txt",std::ios::out);
	for (int i = 0; i < 10; i++)
	{
		f1 << i;
		if (i != 9)
			f1 << ' ';
	}
	f1.close();
	
	char b[10];
	std::fstream f2;
	f2.open("number.txt", std::ios::in);
	int i=0;
	while(!f2.eof())
	{
		f2 >> b[i];
		i++;
	}
	for (auto i : b)
	{
		std::cout<< i;
		if (i != 9)
			std::cout << ' ';
	}
	f2.close();
	
	std::fstream f3("number.txt",std::ios::app);
	int m, n;
	std::cin >> m >> n;
	f3 << ' '<<m <<' '<< n;
	f3.close();
	
	int b[] = { 0,1,2,3,4,5,6,7,8,9 };
	std::fstream f4("number.dat", std::ios::out | std::ios::binary);
	f4.write(reinterpret_cast<char *>(&b[0]),sizeof(b));
	int a[10];
	f4.close();
	f4.open("number.dat", std::ios::in | std::ios::binary);
	f4.read(reinterpret_cast<char *>(a),  sizeof(a));
	for (int i = 0; i < 10; i++)
	{
		std::cout << a[i]<<std::endl;
	}
	f4.close();

	std::fstream f5("number.dat",std::ios::in|std::ios::binary);
	int k[10];
	f5.read(reinterpret_cast<char *>(k), sizeof(k));
	f5.close();
	f5.open("number.dat",  std::ios::out | std::ios::binary);
	f5.write(reinterpret_cast<char *>(&k), sizeof(k));
	f5.seekp(16,std::ios::beg);
	int m = 100;
	int n[11];
	f5.write(reinterpret_cast<char *>(&m), sizeof(m));
	f5.seekp(20, std::ios::beg);
	f5.write(reinterpret_cast<char *>(&k[4]), 6*sizeof(k[0]));
	f5.close();
	f5.open("number.dat", std::ios::in | std::ios::binary);
	
	f5.read(reinterpret_cast<char *>(n), sizeof(n));
	int i = 0;
	while(i<11)
	{
		std::cout << n[i]<<std::endl;
		i++;
	}
	f5.close();

    return 0;*/
	int num1 = 1;
	int num2[1] = { 0 };
	double dnum1 = 1.5, dnum2;
	int a[3] = { 1,2,3 }, b[3];
	
	std::fstream f("inout.dat", std::ios::in | std::ios::binary);
	f.write(reinterpret_cast<char *>(&num1), sizeof(num1));
	f.close();
	f.open("inout.dat", std::ios::out | std::ios::binary);
	f.read(reinterpret_cast<char *>(num2), sizeof(num2));
	std::cout << num2[0] << std::endl;
	f.close();
	return 0;
}

