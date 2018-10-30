#pragma once
class SeList
{
	/**
	* size 表的大小
	* L_[30] 保存人的密码
	* Index_[30] 保存人的序号 
	*/
private:
	int size_;
	int L_[30];
	int Index_[30];
public:
	SeList();
	~SeList();
	void Init(int n);		//初始化
	void Delete(int index);	//删除	
	void show();			//显示
	void Joseph();			//约瑟夫函数
};

