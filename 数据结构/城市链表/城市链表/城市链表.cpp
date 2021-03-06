// 城市链表.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
/*
1）城市链表
[问题描述]
将若干城市的信息，存入一个带头结点的单链表。结点中的城市信息包括：城市名，城
市的位置坐标。要求能够利用城市名和位置坐标进行有关查找、插入、删除、更新等操作。
[基本要求]
（1） 给定一个城市名，返回其位置坐标；
（2） 给定一个位置坐标P和一个距离D，返回所有与P的距离小于等于D的城市。
[测试数据]
由学生依据软件工程的测试技术自己确定。注意测试边界数据。
*/


#include "pch.h"
#include <iostream>
#include "CityLinkList.h"
#include "CitySeList.h"

void StartSe();
void addSe(CitySeList& cities);
void updateSe(CitySeList& cities);
void searchSe(CitySeList& cities);
void DeleteSe(CitySeList& cities);
void nearbySe(CitySeList& cities);

void Start();
void add(CityLinkList cities);
void update(CityLinkList cities);
void search(CityLinkList cities);
void Delete(CityLinkList cities);
void nearby(CityLinkList cities);
int main()
{
	int a;
	std::cout << "请选择模式：1，链式结构  2，顺序结构" << std::endl;
	std::cin >> a;
	system("cls");
	if (a == 1)
		Start();
	else
		StartSe();

}

void Start()
{
	int act;								//保存主菜单选择
	bool flag = true;						//保存是否退出
	CityLinkList cities = CityLinkList();	//城市链表表头的对象

	while (flag) {
		system("cls");
		std::cout << "------------------------------------------------------------" << std::endl;
		std::cout << "请选择要进行的操作：" << std::endl;
		std::cout << "1 添加新城市   2 查找城市信息       3 删除城市 " << std::endl;
		std::cout << "4 更新城市信息 5 搜索范围内的城市   6 查看所有城市   7退出" << std::endl;
		std::cout << "------------------------------------------------------------" << std::endl;
		std::cin >> act;
		switch (act) {
		case 1:
			add(cities);//添加
			break;
		case 2:
			search(cities);//查找
			break;
		case 3:
			Delete(cities);//删除
			break;
		case 4:
			update(cities);//更新
			break;
		case 5:
			nearby(cities);//范围查找
			break;
		case 6:
			cities.show();//显示所有城市
			break;
		case 7:
			std::cout << "退出成功" << std::endl;
			flag = false;
			cities.DeleteList();
			break;
		default:
			std::cout << "无效输入" << std::endl;
			std::cin.clear();
			std::cin.ignore();
			break;
		}
		system("pause");
	}
}

void add(CityLinkList cities)
{
	std::cout << "请输入要添加的城市个数：";
	int n;								//要添加城市的个数
	std::cin >> n;
	double x, y;						//要添加城市的坐标
	char name[50];						//要添加城市的名字
	for (int i=0; i < n; i++) {			//循环n次
		std::cout << "请输入第" << i + 1 << "个城市的名字：" << std::endl;
		//std::cin >> name;
		getchar();
		std::cin.getline(name,1000);
		std::cout << "请输入第" << i + 1 << "个城市的坐标xy：" << std::endl;
		std::cin >> x>>y;
		cities.CityInsert(std::string(name), x, y);  //调用CityInsert（）插入城市
	}

}

void search(CityLinkList cities)
{
	LinkList L;
	int i;  //查找模式选择 1 通过城市名字查找    2 通过城市坐标查找
	std::cout << "请选择查找模式\n1 通过城市名字查找\n2 通过城市坐标查找" << std::endl;
	std::cin >> i;
	switch (i) {
	case 1:
		char name[50]; //保存要查找的城市名字
		std::cout << "请输入城市名字" << std::endl;
		std::cin >> name;
		L=cities.Search(std::string(name));  //调用Search（）通过名字查找，把找到的结点的前驱结点返回给L
		if (L->next)
		{
			std::cout << "城市名字：" << L->next->city.CityName.c_str() << "   城市坐标：("
				<< L->next->city.CityPosition[0] << "," << L->next->city.CityPosition[1] << ")" << std::endl;
		}
		else
			std::cout << "找不到匹配的城市信息" << std::endl;
		break;

	case 2:
		double x, y;//保存要查找的城市坐标
		std::cout << "请输入城市坐标" << std::endl;
		std::cin >> x >> y;
		L=cities.Search(x, y);				//调用Search（）通过坐标查找，把找到的结点的前驱结点返回给L
		if (L->next)
		{
			std::cout << "城市名字：" << L->next->city.CityName.c_str() << "   城市坐标：(" 
				<< L->next->city.CityPosition[0] << "," << L->next->city.CityPosition[1] << ")" << std::endl;
		}
		else
			std::cout << "找不到匹配的城市信息" << std::endl;
		break;
	}
	
}

void Delete(CityLinkList cities) {
	std::cout << "请输入要删除的城市名字" << std::endl;
	char name[50];  //保存要删除的城市名字
	std::cin >> name;
	cities.CityDelete(name); 
}

void update(CityLinkList cities)
{
	LinkList L;
	int i;   //更新模式选择 1 通过城市名字更新    2 通过城市坐标更新
	std::cout << "请选择更新模式\n1 通过名字查找更新\n2 通过坐标查找更新" << std::endl;
	std::cin >> i;
	double x_, y_; //保存更新后的坐标
	char cname[50];//保存更新后的名字
	switch (i) {
	case 1:
		char name[50];//保存要查找的城市名字
		std::cout << "请输入城市名字" << std::endl;
		std::cin >> name;
		L=cities.Search(std::string(name));//调用Search（）通过名字查找，把找到的结点的前驱结点返回给L
		if (L->next)
		{
			std::cout << "成功找到     城市名字：" << L->next->city.CityName.c_str() << "   城市坐标：(" 
				<< L->next->city.CityPosition[0] << "," << L->next->city.CityPosition[1] << ")" << std::endl;
			std::cout << "请输入更改后的城市名字，坐标：" << std::endl;
			std::cin >> cname >> x_ >> y_;
			cities.ChangeCity(name,cname,x_,y_);//调用ChangeCity(）更新
			std::cout << "成功改为     城市名字：" << L->next->city.CityName.c_str() << "   城市坐标：(" 
				<< L->next->city.CityPosition[0] << "," << L->next->city.CityPosition[1] << ")" << std::endl;
		}
		else
			std::cout << "找不到匹配的城市信息" << std::endl;
		break;
	case 2:
		double x, y;//保存要查找的城市坐标
		std::cout << "请输入城市坐标" << std::endl;
		std::cin >> x >> y;
		L=cities.Search(x, y);//调用Search（）通过坐标查找，把找到的结点的前驱结点返回给L
		if (L->next)
		{
			std::cout << "成功找到     城市名字：" << L->next->city.CityName.c_str() << "   城市坐标：(" 
				<< L->next->city.CityPosition[0] << "," << L->next->city.CityPosition[1] << ")" << std::endl;
			std::cout << "请输入更改后的城市名字，坐标：" << std::endl;
			std::cin >> cname >> x_ >> y_;
			cities.ChangeCity(x,y, cname, x_, y_);//调用ChangeCity(）更新
			std::cout << "成功改为     城市名字：" << L->next->city.CityName.c_str() << "   城市坐标：("
				<< L->next->city.CityPosition[0] << "," << L->next->city.CityPosition[1] << ")" << std::endl;
		}
		else
			std::cout << "找不到匹配的城市信息" << std::endl;
		break;
	}
	
}

void nearby(CityLinkList cities) {
	char name[50]; //保存中心城市名字
	double D;		//保存搜索范围
	std::cout << "请输入中心城市名字" << std::endl;
	std::cin >> name;
	std::cout << "请输入搜索范围:" << std::endl;
	std::cin >> D;
	if (D < 0) {
		printf("范围不能为负数\n");
	}
	else {
		std::vector<City> nearCity = cities.SearchNearest(name, D);
		printf("----------------------------------------------------\n");
		for (City it : nearCity)
			std::cout << "城市名字：" << it.CityName.c_str() << "   城市坐标：(" 
			<< it.CityPosition[0] << "," << it.CityPosition[1] << ")" << std::endl;
	}
}

void StartSe()
{
	int act;							//保存主菜单选择
	bool flag = true;					//保存是否退出
	CitySeList cities = CitySeList();	//城市链表表头的对象

	while (flag) {
		system("cls");
		std::cout << "------------------------------------------------------------" << std::endl;
		std::cout << "请选择要进行的操作：" << std::endl;
		std::cout << "1 添加新城市   2 查找城市信息       3 删除城市 " << std::endl;
		std::cout << "4 更新城市信息 5 搜索范围内的城市   6 查看所有城市   7退出" << std::endl;
		std::cout << "------------------------------------------------------------" << std::endl;
		std::cin >> act;
		switch (act) {
		case 1:
			addSe(cities);//添加
			break;
		case 2:
			searchSe(cities);//查找
			break;
		case 3:
			DeleteSe(cities);//删除
			break;
		case 4:
			updateSe(cities);//更新
			break;
		case 5:
			nearbySe(cities);//范围查找
			break;
		case 6:
			cities.show();//显示所有城市
			break;
		case 7:
			std::cout << "退出成功" << std::endl;
			flag = false;
			break;
		default:
			std::cout << "无效输入" << std::endl;
			std::cin.clear();
			std::cin.ignore();
			break;
		}
		system("pause");
	}
}

void addSe(CitySeList& cities)
{
	std::cout << "请输入要添加的城市个数：";
	int n;					//要添加城市的个数
	std::cin >> n;
	double x, y;			//要添加城市的坐标
	char name[50];			//要添加城市的名字
	for (int i = 0; i < n; i++) {
		std::cout << "请输入第" << i + 1 << "个城市的名字：" << std::endl;
		getchar();
		std::cin.getline(name, 1000);
		std::cout << "请输入第" << i + 1 << "个城市的坐标xy：" << std::endl;
		std::cin >> x >> y;
		cities.CityInsert(std::string(name), x, y); //调用CityInsert（）插入城市
	}
}

void searchSe(CitySeList& cities)
{
	CitySe c;
	int i;		 //查找模式选择 1 通过城市名字查找    2 通过城市坐标查找
	std::cout << "请选择查找模式\n1 通过城市名字查找\n2 通过城市坐标查找" << std::endl;
	std::cin >> i;
	switch (i) {
	case 1:
		char name[50];//保存要查找的城市名字
		std::cout << "请输入城市名字" << std::endl;
		std::cin >> name;
		c = cities.Search(std::string(name));//调用Search（）通过名字查找，把找到y元素返回给c
		if (c.CityName!=cities.getL_Flag().CityName)
		{
			std::cout << "城市名字：" << c.CityName.c_str() << "   城市坐标：(" << c.CityPosition[0] << "," << c.CityPosition[1] << ")" << std::endl;
		}
		else
			std::cout << "找不到匹配的城市信息" << std::endl;
		break;

	case 2:
		double x, y;//保存要查找的城市坐标
		std::cout << "请输入城市坐标" << std::endl;
		std::cin >> x >> y;
		c = cities.Search(x, y);//调用Search（）通过坐标查找，把找到的把找到y元素返回给c
		if (c.CityName != cities.getL_Flag().CityName)
		{
			std::cout << "城市名字：" << c.CityName.c_str() << "   城市坐标：(" << c.CityPosition[0] << "," << c.CityPosition[1] << ")" << std::endl;
		}
		else
			std::cout << "找不到匹配的城市信息" << std::endl;
		break;
	}

}

void DeleteSe(CitySeList& cities) {
	std::cout << "请输入要删除的城市名字" << std::endl;
	char name[50]; //保存要删除的城市名字
	std::cin >> name;
	cities.CityDelete(name);//调用CityDelete（）删除城市
}

void updateSe(CitySeList& cities)
{
	CitySe c;
	int i;  //更新模式选择 1 通过城市名字更新    2 通过城市坐标更新
	std::cout << "请选择更新模式\n1 通过名字查找更新\n2 通过坐标查找更新" << std::endl;
	std::cin >> i;
	double x_, y_;	//保存更新后的坐标
	char cname[50];	//保存更新后的名字
	switch (i) {
	case 1:
		char name[50];//保存要查找的城市名字
		std::cout << "请输入城市名字" << std::endl;
		std::cin >> name;
		c = cities.Search(std::string(name));//调用Search（）通过名字查找，把找到y元素返回给c
		if (c.CityName != cities.getL_Flag().CityName) {
			std::cout << "成功找到     城市名字：" << c.CityName.c_str() << "   城市坐标：(" 
				<< c.CityPosition[0] << "," << c.CityPosition[1] << ")" << std::endl;
			std::cout << "请输入更改后的城市名字，坐标：" << std::endl;
			std::cin >> cname >> x_ >> y_;
			cities.ChangeCity(name, cname, x_, y_);//调用ChangeCity(）更新
		}
		else
			std::cout << "找不到匹配的城市信息" << std::endl;
		break;
	case 2:
		double x, y;//保存要查找的城市坐标
		std::cout << "请输入城市坐标" << std::endl;
		std::cin >> x >> y;
		c = cities.Search(x, y);//调用Search（）通过坐标查找，把找到y元素返回给c
		if (c.CityName != cities.getL_Flag().CityName){
			std::cout << "成功找到     城市名字：" << c.CityName.c_str() << "   城市坐标：(" 
				<< c.CityPosition[0] << "," << c.CityPosition[1] << ")" << std::endl;
			std::cout << "请输入更改后的城市名字，坐标：" << std::endl;
			std::cin >> cname >> x_ >> y_;
			cities.ChangeCity(x, y, cname, x_, y_);//调用ChangeCity(）更新
		}
		else
			std::cout << "找不到匹配的城市信息" << std::endl;
		break;
	}

}

void nearbySe(CitySeList& cities) {
	char name[50]; //保存中心城市名字
	double D;	  //保存搜索范围
	std::cout << "请输入中心城市名字" << std::endl;
	std::cin >> name;
	std::cout << "请输入搜索范围:" << std::endl;
	std::cin >> D;
	if (D < 0) {
		printf("范围不能为负数\n");
	}
	else {
	std::vector<CitySe> nearCity = cities.SearchNearest(name, D);
	printf("----------------------------------------------------\n");
	for (CitySe it : nearCity)
		std::cout << "城市名字：" << it.CityName.c_str() << "   城市坐标：(" 
		<< it.CityPosition[0] << "," << it.CityPosition[1] << ")" << std::endl;

	}
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
