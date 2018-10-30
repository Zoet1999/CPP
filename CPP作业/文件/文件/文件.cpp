// 职工信息文件.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
struct original {
	char name[10];
	int num;
	char  sex[6];
	int age;
	char address[20];
	int wage;
	char health[10];
	char education[10];
}emp[10];
struct now {
	char name[10];
	int wage;
}empl[10],em[10];
int main()
{
	FILE *fp;
	int i;
	fopen_s(&fp, "employee", "r");
	for (i = 0; i<10; i++)
	{
		if (fread(&emp[i], sizeof(struct original), 1, fp) != 1)//读取原文件的内容
			printf("读取错误");
	}
	for (i = 0; i < 10; i++)
	{
		strcpy_s(empl[i].name, emp[i].name);//将原文件的结构数组的内容需要的部分付给新的结构数组
		empl[i].wage = emp[i].wage;
	}
	fclose(fp);
	fopen_s(&fp, "simple", "w");
	for (i = 0; i < 10; i++)
		if (fwrite(&empl[i], sizeof(struct now), 1, fp) != 1)//把新的结构数组写入新的文件中
			printf("写入错误");
	fclose(fp);
	fopen_s(&fp, "simple", "r");
	for (i = 0; i<10; i++)
	{
		if (fread(&em[i], sizeof(struct now), 1, fp) != 1)
			printf("读取错误");
	}
	printf("新文件的内容为：\n");
	for (i = 0; i < 10; i++)
	{
		printf("%s,%d\n", em[i].name, em[i].wage);//输出显示新文件的内容
	}
	return 0;
}

