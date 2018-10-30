#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXSIZE 101

struct CitySe {
	/**
		* ������Ϣ�ṹ��
		* �洢�˳��е���Ϣ
		* CityName  ��������
		* CityPosition[0] x����
		* CityPosition[1] y����
		* index ��������˳����е��±�
		*/
	std::string CityName;
	double CityPosition[2];//0Ϊx��1Ϊy
	int index;
};


class CitySeList
{
	int size_;
	CitySe L_[MAXSIZE];
public:
	CitySeList();
	~CitySeList();
	CitySe getL_Flag();																		//����L[size-1]��ֵ
	void CityInsert(std::string CityName, double x, double y);								//�������
	void CityDelete(std::string CityName);													//ɾ������
	CitySe Search(double x, double y);														//ͨ���������
	CitySe Search(std::string CityName);														//ͨ�����ֲ���
	void ChangeCity(std::string Name_, std::string CityName, double x, double y);		//ͨ�����ֲ��Ҹ���
	void ChangeCity(double x_, double y_, std::string CityName, double x, double y);//ͨ��������Ҹ���
	void show();
	std::vector<CitySe> SearchNearest(std::string CityName, double D);						//���ط�Χ�ڵĳ���
};

