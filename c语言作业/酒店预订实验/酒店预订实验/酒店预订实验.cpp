// 酒店预订实验.cpp: 定义控制台应用程序的入口点。
//该程序每次执行完命令后会自动清屏，保持界面整洁

/***********库定义区****************/
#include "stdafx.h"
#include <stdlib.h>
/***********结构定义区****************/
struct guest {
	char name[8];	//姓名
	int sum;		//人数
	char time[10];	//用餐时间
	int number;		//编号
	int flag;		//标记是否有效
};
/***********函数定义区****************/
	int insert(struct guest *p, int n, int max, int *num);
	int print(struct guest *p, int n, int max, int *num);
	int search(struct guest *p, int n, int max);
	int delete_(struct guest *p, int n, int max);
	int change(struct guest *p, int n, int max);
	int choose();
int main()
{
	int max,finish=1,cho,n=0,i,No=0;
	//max记录最大人数，n记录有效订单数，cho记录用户选择，
	int *num= &No;//用于记录编号轮序
	printf("请输入酒店最大订单数:");
	scanf_s("%d", &max);
	struct guest * destine = (struct guest *)malloc(max * sizeof(struct guest));//根据设定的最大订单数定义结构数组
	for (i = 0; i < max; i++)
	{
		destine[i].flag = 0;//把所有结构数组的flag置0
	}
	while (finish == 1) 
	{
		cho = choose();//输出选项
		switch (cho)
		{
		case 1:insert(destine, n, max, num);
			n++;
			break;//插入
		case 2:search(destine, n, max);
			break;//查询
		case 3:change(destine, n, max);
			break;//修改
		case 4:delete_(destine, n, max);
			n--;
			break;//删除
		case 5:print(destine, n, max, num);
			break;//显示
		case 6:finish = 0; printf("程序已关闭，感谢您的使用。\n");
			break;//退出
		default:printf("输入错误！！！\n");
			rewind(stdin);
			break;
		}
		if (finish == 1)
		{
			system("pause");
			system("cls");
			printf("请输入酒店最大订单数:%d\n",max);
		}
	}
    return 0;
}
int choose() {
	printf("1.插入\t");
	printf("2.查询\t");
	printf("3.修改\n");
	printf("4.删除\t");
	printf("5.显示\t");
	printf("6.退出\n");
	printf("请选择要进行的操作：");
	int n;
	scanf_s("%d", &n);
	return n;
}
int change(struct guest *p, int n,int max)
{
	if (n == 0) {
		printf("没有订单!!\n");//如果没有订单，不进行操作
		return 0;
	}
	printf("请输入要改变的订单编号：");
	int num,i;	
	scanf_s("%d", &num);//记录要改变的订单编号
	for (i = 0; i < max; i++)//寻找对应编号的订单
	{
		if (p[i].flag == 0);//检查该订单是否还有效
		else
			if (num == p[i].number)//找到对应编号的订单则退出循环
				break;
		if (i == max - 1)//没有找到订单则退出函数
		{
			printf("无此订单！\n");
			return 0;
		}
	}
		printf("找到订单为：\t编号：%-4d\t姓名：%s\t人数：%-2d\t用餐时间：%s\n",
			p[i].number, p[i].name, p[i].sum, p[i].time);//显示找到的订单
		printf("是否要修改？（1.yes  2.no）");//确认订单是否是想要的订单后，再选择是否修改
		int a;
		scanf_s("%d", &a);
		if(a==1)
		{
			printf("请输入修改的值:\n");
			printf("姓名：");
			scanf_s("%s",p[i].name,8);
			printf("人数：");
			scanf_s("%d", &p[i].sum);
			printf("用餐时间：");
			scanf_s("%s", p[i].time,10);
		}	//用新数据覆盖订单内容
		return 0;//结束函数

}
int delete_(struct guest *p, int n, int max)
{
	if (n == 0) {
		printf("没有订单!!\n");//如果没有订单，不进行操作
		return 0;
	}
	printf("请输入要删除的订单编号：");
	int num,i;
	scanf_s("%d", &num);//记录要删除的订单编号
	for (i = 0; i < max; i++)//寻找对应编号的订单
	{
		if (p[i].flag == 0);//检查该订单是否还有效
		else
			if (num == p[i].number)//找到对应编号的订单则退出循环
				break;
		if (i == max - 1)//没有找到订单则退出函数
		{
			printf("无此订单！\n");
			return 0;
		}
	}
		printf("找到订单为：\t编号：%-4d\t姓名：%s\t人数：%-2d\t用餐时间：%s\n",
			p[i].number, p[i].name, p[i].sum, p[i].time);//显示找到的订单
		printf("是否要删除？（1.yes  2.no）");//确认订单是否是想要的订单后，再选择是否删除
		int a;
		scanf_s("%d", &a);
		if (a == 1)
		{
			p[i].flag = 0;//使订单无效
		}
		return 0;
}
int insert(struct guest *p, int n, int max, int *num)
{
	int i,b;
	for (i = 0; i < max; i++) //找到一个无效的座位
	{
		if (p[i].flag == 0)
			break;
	}
	b = i;
	if (n < max) {
		printf("请输入新订单的信息\n");
		printf("姓名：");
		scanf_s("%s", p[b].name,8);
		printf("人数：");
		scanf_s("%d",& p[b].sum);
		printf("用餐时间:");
		scanf_s("%s", p[b].time,10);
		*num += 1;
		p[b].number = *num;//给编号
		printf("该订单编号为：%d\n",*num);//告知编号
		p[b].flag = 1;
	}	//写入订单信息
	else if (n >=max)
		printf("没有空余位置\n");
	return 0;
}

int print(struct guest *p, int n, int max, int *num)
{
	if(n == 0)
	{
		printf("无订单\n"); //如果没有订单，不进行操作
		return 0;
	}
	int i;
	printf("找到订单为\n");
	for (i = 0; i < max; i++) {
		if (p[i].flag == 1)
		{
			printf("编号：%-4d\t姓名：%s\t人数：%-2d\t用餐时间：%s\n",
				p[i].number, p[i].name, p[i].sum, p[i].time);//输出
		}
	}
	return 0;
}
int search(struct guest *p, int n, int max)
{
	if (n == 0) {
		printf("没有订单!!\n");//如果没有订单，不进行操作
		return 0;
	}
	printf("请输入要查询的订单编号：");
	int num,i;
	scanf_s("%d", &num);//记录要查询的订单编号
	for (i = 0; i < max; i++)//寻找对应编号的订单
	{
		if (p[i].flag == 0);//检查该订单是否还有效
		else
			if (num == p[i].number)//找到对应编号的订单则退出循环
				break;
		if (i == max - 1)//没有找到订单则退出函数
		{
			printf("无此订单！\n");
			return 0;
		}
	}
		printf("找到订单为：\t编号：%-4d\t姓名：%s\t人数：%-2d\t用餐时间：%s\n",
			p[i].number, p[i].name, p[i].sum, p[i].time);//显示找到的订单
return 0;
	
}
