#include "stdafx.h"
#include"Client.h"
using namespace std;
#pragma comment(lib, "ws2_32.lib")  

using namespace std;
#pragma comment(lib, "ws2_32.lib")  
int main()
{
	Client a;
	a.Connect();
	std::cout<<a.rec();
	//std::cout << a.rec();
	std::string str = "asdsad";
	a.Sendm(str);
	std::cout << a.rec();
	a.Sendm("gameSolo");
	std::cout << a.rec();
	a.Sendm("123");
	std::string m;
	std::cin >> m;
	return 0;
}