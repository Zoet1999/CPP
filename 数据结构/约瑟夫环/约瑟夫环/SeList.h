#pragma once
class SeList
{
	/**
	* size ��Ĵ�С
	* L_[30] �����˵�����
	* Index_[30] �����˵���� 
	*/
private:
	int size_;
	int L_[30];
	int Index_[30];
public:
	SeList();
	~SeList();
	void Init(int n);		//��ʼ��
	void Delete(int index);	//ɾ��	
	void show();			//��ʾ
	void Joseph();			//Լɪ����
};

