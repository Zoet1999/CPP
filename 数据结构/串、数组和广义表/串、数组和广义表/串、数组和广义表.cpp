// 串、数组和广义表.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>

//KMP算法
int Index_KMP(std::string S,std::string T,int pos);
void get_next(std::string T, int next[]);
void get_nextval(std::string T, int next[]);

int main()
{
    return 0;
}

int Index_KMP(std::string S, std::string T, int pos)
{
	int nextval[100];
	get_nextval(T, nextval);
	int i = pos;
	int j = 1;
	while (i <= S.length() && j < T.length())
	{
		if (j = 0 || S[i] == T[j]) { i++, j++; }
		else j = nextval[j];
	}
	if (j > T.length())return i - T.length();
	else return 0;

}
void get_next(std::string T, int next[])
{
	int i = 1;
	next[1] = 0;
	int j = 0;
	while (i < T.length())
	{
		if (0 == j || T[i] == T[j])
		{
			++i; ++j;
			next[i] = j;
		}
		else j = next[j];
	}
}
void get_nextval(std::string T, int nextval[])
{
	int i = 1;
	nextval[1] = 0;
	int j = 0;
	while (i < T.length)
	{
		if (0 == j || T[i] == T[j])
		{
			++i; ++j;
			if (T[i] != T[j])
				nextval[i] = j;
			else nextval[i] = nextval[j];
		}
		else j = nextval[j];
	}
}