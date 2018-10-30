// 职工信息文件.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
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
int main()
{
	FILE *fp;
	int i;
	printf("输入姓名、职工号、性别、年龄、住址、工资、健康状况、文化程度\n");
	for(i=0;i<10;i++)
	{ 
		scanf_s("%s%d%s%d%s%d%s%s",emp[i].name,10, &emp[i].num, emp[i].sex,6, &emp[i].age, emp[i].address,20, &emp[i].wage, emp[i].health,10, emp[i].education,10);//写入数据
	}
	if (( fopen_s(&fp,"employee", "w")) == NULL)
	{
		printf("只写打开错误");
			exit(0);
	}
	for (i = 0; i < 4; i++)
		if (fwrite(&emp[i], sizeof(struct original), 1, fp) != 1)
			printf("写入错误");
			fclose(fp);
    return 0;
}

