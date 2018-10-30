#include "pch.h"
#include "CitySeList.h"


CitySeList::CitySeList()
{
	/*���캯��*/
	size_ = 0;
	L_[MAXSIZE - 1].CityName = "��Ч����";
	L_[MAXSIZE - 1].CityPosition[0] = 0;
	L_[MAXSIZE - 1].CityPosition[1] = 0;
	L_[MAXSIZE - 1].index = MAXSIZE - 1;
}
CitySeList::~CitySeList()
{
}
CitySe CitySeList::getL_Flag() {
	return L_[MAXSIZE - 1];
}

void CitySeList::CityInsert(std::string CityName, double x, double y)		//�������
{

	/**
	* �����������
	* @param CityName string  Ҫ������е�����
	* @param x double  Ҫ������е�x����
	* @param y double  Ҫ������е�y����
	*/
	CitySe c = Search(CityName);
	if (c.CityName != L_[MAXSIZE - 1].CityName) {
		std::cout << "�ó����Ѵ���" << std::endl;
	}
	else {
		L_[size_].CityName = CityName;
		L_[size_].CityPosition[0] = x;
		L_[size_].CityPosition[1] = y;
		L_[size_].index = size_;
		size_++;

	}
}

void CitySeList::CityDelete(std::string CityName)					
{	/**
	* ɾ����������
	* @param CityName string  Ҫɾ�����е�����
	*/
	CitySe c=Search(CityName);
	if (c.CityName != L_[MAXSIZE - 1].CityName) {
		for (int i = c.index; i < size_-1; i++) {
			L_[i] = L_[i + 1];
			L_[i].index--;
		}
		size_--;
	}
	else {
		std::cout << "�Ҳ����ó���" << std::endl;
	}
		
}
CitySe CitySeList::Search(double x, double y)								
{
	/**
	* ͨ��������Һ���
	* @param x double Ҫ���ҵĳ���x����
	* @param y double Ҫ���ҵĳ���y����
	* @return LinkList �ҵ��Ľ���ǰ�����
	*/
	for (int i=0; i < size_; i++) {
		if (L_[i].CityPosition[0] == x&&L_[i].CityPosition[1]==y) {
			return L_[i];
		}
	}
	return L_[MAXSIZE - 1];

}
CitySe CitySeList::Search(std::string CityName)						
{
	/**
	* ͨ�����ֲ��Һ���
	* @param CityName string Ҫ���ҵĳ�������
	* @return LinkList �ҵ��Ľ���ǰ�����
	*/
	for (int i=0; i < size_; i++) {
		if (L_[i].CityName == CityName) {
			return L_[i];
		}
	}
	return L_[MAXSIZE - 1];
}
void CitySeList::ChangeCity(std::string Name_, std::string CityName, double x, double y)	
{
	/**
	* ͨ�����ָ��º���
	* @param Name_ string Ҫ���µĳ�������
	* @param CityName string  ���º�ĳ��е�����
	* @param x double  ���º�ĳ��е�x����
	* @param y double  ���º�ĳ��е�y����
	*/
	CitySe c = Search(Name_);
	if (c.CityName != L_[MAXSIZE - 1].CityName) {
		L_[c.index].CityName = CityName;
		L_[c.index].CityPosition[0] = x;
		L_[c.index].CityPosition[1] = y;
		std::cout << "�ɹ���Ϊ     �������֣�" << L_[c.index].CityName.c_str() << "   �������꣺("
			<< L_[c.index].CityPosition[0] << "," << L_[c.index].CityPosition[1] << ")" << std::endl;
	}
	else {
		std::cout << "�Ҳ����ó���" << std::endl;
	}
}
void CitySeList::ChangeCity(double x_, double y_, std::string CityName, double x, double y)
{
	/**
	* ͨ�����ָ��º���
	* @param x_ double  ��Ҫ���³��е�x����
	* @param y_ double  ��Ҫ���³��е�y����
	* @param CityName string  ���º�ĳ��е�����
	* @param x double  ���º�ĳ��е�x����
	* @param y double  ���º�ĳ��е�y����
	*/
	CitySe c = Search(x_,y_);
	if (c.CityName != L_[MAXSIZE - 1].CityName) {
		L_[c.index].CityName = CityName;
		L_[c.index].CityPosition[0] = x;
		L_[c.index].CityPosition[1] = y;
		std::cout << "�ɹ���Ϊ     �������֣�" << L_[c.index].CityName.c_str() << "   �������꣺("
			<< L_[c.index].CityPosition[0] << "," << L_[c.index].CityPosition[1] << ")" << std::endl;
	}
	else {
		std::cout << "�Ҳ����ó���" << std::endl;
	}
}
void CitySeList::show()
{
	/**
	* ��ʾ���г��к���
	*/
	for (int i = 0; i < size_; i++) {
		std::cout << "�������֣�" << L_[i].CityName.c_str() << "   �������꣺(" << L_[i].CityPosition[0] << "," << L_[i].CityPosition[1] << ")" << std::endl;
	}
}
std::vector<CitySe> CitySeList::SearchNearest(std::string CityName, double D)//���ط�Χ�ڵĳ���
{

	/**
	* �ڷ�Χ���������к���
	* @param CityName string ��Ϊ�������ĳ��е�����
	* @param D double ������Χ
	* @return std::vector<City>  �ڷ�Χ�ڵĳ��м���
	*/
	std::vector<CitySe> res;
	CitySe c = Search(CityName);
	if (c.CityName!=L_[MAXSIZE-1].CityName ) {
		double x = c.CityPosition[0];
		double y = c.CityPosition[1];
		double x_;
		double y_;
		double n;
		for(int i=0;i<size_;i++)
		{
			x_ = L_[i].CityPosition[0];
			y_ = L_[i].CityPosition[1];
			n= (x - x_)*(x - x_) + (y - y_)*(y - y_);
			if (D*D >= n && i!=c.index)
				res.push_back(L_[i]);
		}
		if (res.size() == 0)
		{
			std::cout << "�ڷ�Χ��û���ҵ���������" << std::endl;
		}
	}
	else {
		std::cout << "�Ҳ���ƥ��ĳ�����Ϣ" << std::endl;
	}
	return res;
}