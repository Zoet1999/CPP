#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

struct City {
	/**
	* ������Ϣ�ṹ��
	* �洢�˳��е���Ϣ
	* CityName  ��������
	* CityPosition[0] x����
	* CityPosition[1] y����
	*/
	std::string CityName;
	double CityPosition[2];//0Ϊx��1Ϊy
};
typedef struct LNode
{
	/**
	* ������
	* city �洢������Ϣ
	* next ���ָ�룬ָ����һ�����
	*/
	City city;
	LNode * next;
}LNode, *LinkList;


class CityLinkList
{
private:
	LinkList LHead;
public:
	CityLinkList();
	~CityLinkList();
	void InitList();											                	//��ʼ��������
	void DeleteList();											                	//�������
	void CityInsert(std::string CityName, double x, double y);	                	//�������
	void CityDelete(std::string CityName);						                	//ɾ������
	LinkList Search(double x, double y);						                	//ͨ���������
	LinkList Search(std::string CityName);						                	//ͨ�����ֲ���
	void ChangeCity(std::string Name_,std::string CityName, double x, double y);	//ͨ�����ֲ��Ҹ���
	void ChangeCity(double x_, double y_,std::string CityName, double x, double y);//ͨ��������Ҹ���
	void show();
	std::vector<City> SearchNearest(std::string CityName, double D);//���ط�Χ�ڵĳ���
};

