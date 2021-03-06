/**************************************************************************************************************
**文件:Roguelike回合制RPG.cpp
**编写者:颜加泉
**编写日期:2017年1月1号
**简要描述:简单的回合制RPG
**编译环境：VS2017
**************************************************************************************************************/
#include "stdafx.h"
#include <windows.h>
#include <time.h>
#include <conio.h>
/***********宏定义区******************/
#define MONSTER 6//定义怪物种类数
#define frame_height 20 //定义地图大小
#define frame_width 40
#define UP 'w' //定义操作键
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
int finish;//判断战斗是否结束
int gameover = 0;//判断游戏是否结束
int map[frame_height][frame_width] = { { 0, } , };  //记录地图信息
//0:空地 1：障碍  3：BOSS 4：怪物类1 5：怪物类2 6：怪物类3 7：宝箱1 8：宝箱2 9：宝箱3 
/***********结构定义区****************/
struct hero {
	int x;//横坐标
	int y;//纵坐标
	int HP;//生命
	int MP;//魔力
	int EXP;//经验
	int LEVEL;//等级
	int attack;//攻击力
}player;//记录玩家角色的数据
struct monster {
	int HP;//生命
	int attack;//攻击力
	int exp;//被击杀后，英雄得到的经验
	char name[20];
}mon[MONSTER];
/*************函数声明区**************/
void gotoxy(int x, int y);					//移动光标
void inti_map();							//绘制地图
void draw(int x, int y, int len, int direction);	//画地图障碍
void draw_(int x, int y, int flag, int kind);		//画地图事件
void blank(int x, int y, int len, int direction);	//删除地图事件
void blank_(int x, int y, int len, int direction);	//清除文字信息
void inti_hero();							//初始化英雄数值
void inti_monster();						//初始化怪物数值
void move();								//移动
void chest(int a);							//宝箱事件
void fight(int a);							//战斗事件
void level_up();							//判断升级函数
void updata(int m);						//更新状态信息
void pla_death(int m);						//判断英雄死亡函数
void mon_death(int m);					//判断怪物死亡函数
void at1(int m);							//技能1
void at2(int m);							//技能2
void at3(int m);							//技能3
void login();								//绘制显示登入界面
/************主函数定义区***************/
int main()
{
	login();
	inti_map();	
	inti_hero();
	inti_monster();
	while (gameover == 0)
	{
		gotoxy(20, 1);
		printf("英雄：LV.%-4dEXP:%-5d\n HP:%-6dMP:%-6dattack：%-6d", player.LEVEL, player.EXP, player.HP, player.MP, player.attack);//显示英雄状态
		move();
	}
	gotoxy(33, 1);
	system("pause");
	return 0;
}
/************函数定义区***************/
void login()
{
	draw(0, 0, frame_width, 4);//画出框框
	draw(0, 0, frame_height, 2);
	draw(frame_height - 1, frame_width - 1, frame_width, 3);
	draw(frame_height - 1, frame_width - 1, frame_height, 1);
	gotoxy(10,17);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
		FOREGROUND_BLUE);
	printf("恶魔城");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
		FOREGROUND_BLUE);
	gotoxy(17,20);
	printf("Game Maker 颜加泉");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	/*************规则说明*************/
	gotoxy(5, 40);  printf("规则说明");
	gotoxy(6, 40);  printf("本游戏为roguelike回合制RPG");
	gotoxy(7, 40); printf("roguelike游戏的特色在于他的随机性");
	gotoxy(8, 40);  printf("一共有三层，每层的怪物逐渐变强");
	gotoxy(9, 40);  printf("每个怪物与宝箱都是随机的");
	gotoxy(10, 40); printf("EXP达到10*LEVEL是会升级，使英雄数值上升");
	gotoxy(11, 40); printf("请使用w s a d进行移动(小写！！！)");
	gotoxy(12, 40); printf("打到最后的BOSS即为胜利");
	gotoxy(13, 40); printf("P:Player玩家\tB:BOSS\tC:宝箱\tM：怪物");
	gotoxy(20, 1);
	system("pause");
	system("cls");
}

void inti_hero()
{
	/***初始化英雄数据***/
	player.x = 16;
	player.y = 1;
	gotoxy(player.x, player.y);
	printf("P");
	player.HP = 100;
	player.MP = 60;
	player.EXP = 0;
	player.LEVEL = 1;
	player.attack = 30;
}
void inti_monster()
{
	/***初始化怪物数据***/
	int hp[MONSTER] = { 20,50,100,500,1000,10000 };
	int attack[MONSTER] = { 10,20,50,200,500,2000 };
	int ex[MONSTER] = { 5,10,20,50,100,0 };
	char name[MONSTER][20] = { "骷髅战士·Lv.1","石像鬼·Lv.2","憎恶·Lv3","冰霜巨龙·Lv4","死亡骑士·Lv5","巫妖王·BOSS" };
	int i;
	for (i = 0; i < MONSTER; i++)
	{
		mon[i].HP = hp[i];
		mon[i].attack = attack[i];
		mon[i].exp = ex[i];
		strcpy_s(mon[i].name, name[i]);
	}
}
void move()//移动操作
{
	char ch;
	int nx, ny;//记录新的xy
	int flag = 0;
	while (flag == 0) {
		if (_kbhit())
		{
			ch = _getch();//输入移动指令
			if (ch == UP || ch == DOWN || ch == LEFT || ch == RIGHT)//判断输入是否有效
				break;
		}
	}
	/***********移动英雄**********/
	gotoxy(player.x, player.y);
	printf(" ");
	switch (ch)//判断方向
	{
	case UP:	nx = player.x - 1; ny = player.y; break;
	case DOWN:	nx = player.x + 1; ny = player.y; break;
	case LEFT:	nx = player.x; ny = player.y - 1; break;
	case RIGHT:	nx = player.x; ny = player.y + 1; break;
	default:break;
	}
	switch (map[nx][ny])//判断落点事件
	{
	case 0:
		player.x = nx; player.y = ny;
		gotoxy(player.x, player.y);
		printf("P");
		break;
	case 3:
		player.x = nx; player.y = ny;
		gotoxy(player.x, player.y);
		printf("P");
		fight(0); break;//BOSS
	case 4:player.x = nx; player.y = ny;
		gotoxy(player.x, player.y);
		printf("P");
		fight(1); break;//第一层怪物
	case 5:player.x = nx; player.y = ny;
		gotoxy(player.x, player.y);
		printf("P");
		fight(2); break;//第二层怪物
	case 6:player.x = nx; player.y = ny;
		gotoxy(player.x, player.y);
		printf("P");
		fight(3); break;//第三层怪物
	case 7:player.x = nx; player.y = ny;
		gotoxy(player.x, player.y);
		printf("P");
		chest(0); break;//第一层宝箱
	case 8:player.x = nx; player.y = ny;
		gotoxy(player.x, player.y);
		printf("P");
		chest(1); break;//第二层宝箱
	case 9:player.x = nx; player.y = ny;
		gotoxy(player.x, player.y);
		printf("P");
		chest(2); break;//第三层宝箱
	default:	gotoxy(player.x, player.y);
		printf("P");
		break;
	}
}
void chest(int a)//用a来选择三类宝箱
{
	int m, n;
	srand((unsigned)time(NULL));
	m = rand() % 4;
	n = 1 + rand() % 50;
	switch (m)
	{
	case 0:player.HP += ((1 + a)*n + 50*a);//三类HP增加为 0~50，50~150，150~300
		blank_(23, 0, 30, 4);
		gotoxy(23, 1);
		printf("你的HP增加了：%d", ((1 + a)*n + 50 * a)); break;
	case 1:player.MP += ((1 + a)*n + 50 * a);//三类MP增加为 0~50，50~150，150~300
		blank_(23, 0, 30, 4);
		gotoxy(23, 1);
		printf("你的MP增加了：%d", ((1 + a)*n + 50 * a)); break;
	case 2:player.attack += ((1 + a)*n + 50 * a);//三类attack增加为 0~50，50~150，150~300
		blank_(23, 0, 30, 4);
		gotoxy(23, 1);
		printf("你的attack增加了：%d", ((1 + a)*n + 50 * a)); break;
	case 3:player.EXP += ((1 + a)*n + 50 * a);//三类EXP增加为 0~50，50~150，150~300
		blank_(23, 0, 30, 4);
		gotoxy(23, 1);
		printf("你的EXP增加了：%d", ((1 + a)*n + 50 * a)); level_up();
		break;
	default:printf("宝箱bug");
		break;
	}
	map[player.x][player.y] = 0;//清除位置信息
}
void level_up()//经验值达到 LEVLE*10时升级
{
	while(player.EXP >= player.LEVEL * 10)
	{
		player.EXP = player.EXP - player.LEVEL * 10;
		player.LEVEL++;
		player.HP += 10 * player.LEVEL;
		player.MP += 10 * player.LEVEL;
		player.attack += 5 * player.LEVEL;
		gotoxy(28, 1);
		printf("恭喜你升级了！！");//通知升级
		system("pause");
		blank_(28, 0, 40, 4);//清除提示
	}}
void fight(int a)//用a来记录怪物的类型 0:BOSS 1:一层怪物 2.二层怪物 3.三层怪物
{
	/*****************判断怪物类别****************/
	int m;
	srand((unsigned)time(NULL));//每层怪物等级随机，但会随着层数增加而变强
	switch (a)
	{
	case 0:m = 5; break;//BOSS对应第5级别的怪物
	case 1:m = rand() % 3; break;//第一层，会出现第0，1，2级别的怪物
	case 2:m = 2 + rand() % 2; break;//第二层，会出现第2,3级别的怪物
	case 3:m = 3 + rand() % 2; break;//第二层，会出现第3,4级别的怪物
	default:printf("判断怪物类别时bug"); break;
	}
	/*****************显示战斗信息****************/
	blank(23, 1, 30, 4);
	gotoxy(23, 1);
	printf("你遇到了%s", mon[m].name);
	gotoxy(20, 40);
	printf("%s：\tHP:%-6dattack：%-6d", mon[m].name, mon[m].HP, mon[m].attack);//显示怪物信息
																			 /*****************进入战斗****************/
	finish = 0;
	int	i = 0, j;
	int n, d;
	while (finish == 0)
	{
		d = 0;
		gotoxy(25, 1);
		printf("1.攻击（0MP）\t2.火焰斩（%d MP）\t3.回复术（%d MP）", 10 + (int)(0.3*player.attack), 20 + (int)(0.5*player.attack));
		printf("请选择要进行的攻击：");
		scanf_s("%d", &n);
		switch (n)
		{
		case 1:at1(m); break;
		case 2:at2(m); break;
		case 3:at3(m); break;
		default:printf("输入错误"); d = 1; rewind(stdin); system("pause");
			break;
		}
		if (d == 0) {
			i++;
			gotoxy(26, 40);
			printf("第%d回合结束", i);
			system("pause");
		}
		for (j = 25; j <= 30; j++)
			blank_(j, 0, 100, 4);//清除每回合战斗信息显示部分
		updata(m);//更新数据
	}
	level_up();
	inti_monster();//回复怪物数据
	blank_(20, 40, 40, 4);
	blank_(23, 0, 40, 4);
}
void at1(int m)
{
	int a, b;
	double k, l;
	srand((unsigned)time(NULL));
	a = 1 + (rand() + 5) % 10;
	k = 0.5 + (float)a / 10.0;//令英雄攻击在0.5~1.5倍之间波动
	srand((unsigned)time(NULL));
	b = 1 + rand() % 10;
	l = 0.5 + (float)b / 10.0;//令怪物攻击在0.5~1.5倍之间波动
	mon[m].HP -= (int)(player.attack*k);//怪物扣血
	gotoxy(26, 1);
	printf("怪物受到了%d的伤害\n", (int)(player.attack*k));
	mon_death(m);//判断怪物是否死亡
	player.HP -= (int)(mon[m].attack*l);//英雄扣血
	gotoxy(27, 1);
	printf("英雄受到了%d的伤害\n", (int)(mon[m].attack*l));
	pla_death(m);//判断英雄是否死亡
}
void at2(int m)
{
	int a, b;
	double k, l;
	srand((unsigned)time(NULL));
	a = 1 + (rand() + 5) % 30;
	k = 3 + (float)a / 10.0;//令英雄攻击在3~6倍之间波动
	srand((unsigned)time(NULL));
	b = 1 + rand() % 10;
	l = 0.5 + (float)b / 10.0;//令怪物攻击在0.5~1.5倍之间波动
	if (player.MP >= (10 + (int)(0.3*player.attack)))//判断MP是否足够
	{
		player.MP -= (10 + (int)(0.3*player.attack));//扣除MP
		mon[m].HP -= (int)(player.attack*k);//怪物扣血
		gotoxy(26, 1);
		printf("怪物受到了%d的伤害\n", (int)(player.attack*k));
		mon_death(m);//判断怪物是否死亡
	}
	else
	{
		gotoxy(26, 1);
		printf("MP不足，没有造成伤害\n");
	}
	player.HP -= (int)(mon[m].attack*l);//英雄扣血
	gotoxy(27, 1);
	printf("英雄受到了%d的伤害\n", (int)(mon[m].attack*l));
	pla_death(m);//判断英雄是否死亡
}
void at3(int m)
{
	int a, b;
	double k, l;
	srand((unsigned)time(NULL));
	a = 1 + (rand() + 5) % 10;
	k = 0.5 + (float)a / 10.0;//令英雄回复在0.5~1.5倍之间波动
	srand((unsigned)time(NULL));
	b = 1 + rand() % 10;
	l = 0.5 + (float)b / 10.0;//令怪物攻击在0.5~1.5倍之间波动
	if (player.MP >= (20 + (int)(0.5*player.attack)))//判断MP是否足够
	{
		player.MP -= (20 + (int)(0.5*player.attack));//扣除MP
		player.HP += (int)(player.attack*k);//回血
		gotoxy(26, 1);
		printf("英雄回复了%d的血量\n", (int)(player.attack*k));
	}
	else
	{
		gotoxy(26, 1);
		printf("MP不足，没有回复血量\n");
	}
	player.HP -= (int)(mon[m].attack*l);//英雄扣血
	gotoxy(27, 1);
	printf("英雄受到了%d的伤害\n", (int)(mon[m].attack*l));
	pla_death(m);//判断英雄是否死亡
}
void mon_death(int m)
{
	int j;
	if (m == 5)
	{
		if (mon[m].HP <= 0)
		{
			gotoxy(23, 41);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_BLUE);
			printf("你打败了BOSS，游戏胜利！！！");//如果BOSS死亡宣布游戏胜利
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			for (j = 25; j <= 30; j++)
				blank_(j, 0, 100, 4);//清除战斗信息显示部分
			finish = 1;//结束战斗
			gameover = 1;//结束停止移动，退出游戏
			updata(m);//更新数据
		}
	}
	if (mon[m].HP <= 0)
	{
		map[player.x][player.y] = 0;//清除位置信息
		gotoxy(30, 1);
		printf("怪物死亡！！获得%dEXP！！", mon[m].exp);//宣布战斗胜利，获得经验
		finish = 1;//结束战斗
		player.EXP += mon[m].exp;
		updata(m);//更新数据
	}
}
void pla_death(int m)
{
	int j;
	if (player.HP <= 0)
	{
		gotoxy(24, 41);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_RED);
		printf("你被打败了，游戏失败，哈哈哈哈哈哈哈哈哈哈哈呵哈哈哈哈哈哈额");//如果英雄死亡，宣布游戏失败
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		for (j = 25; j <= 30; j++)
			blank_(j, 0, 100, 4);//清除战斗信息显示部分
		finish = 1;//结束战斗
		gameover = 1;//结束停止移动，退出游戏
	}
	updata(m);//更新数据
}

void updata(int m)
{
	blank_(20, 0, 80, 4);//清除原来数据
	blank_(21, 0, 80, 4);
	gotoxy(20, 1);
	printf("英雄：LV.%-4dEXP:%-5d\n HP:%-6dMP:%-6dattack：%-6d", player.LEVEL, player.EXP, player.HP, player.MP, player.attack);//显示英雄状态
	gotoxy(20, 40);
	printf("%s：\tHP:%-6dattack：%-6d", mon[m].name, mon[m].HP, mon[m].attack);//显示怪物信息
}
void inti_map()//画地图
{/************画出地图的四边**************/
	draw(0, 0, frame_width, 4);//画出地图
	draw(0, 0, frame_height, 2);
	draw(frame_height - 1, frame_width - 1, frame_width, 3);
	draw(frame_height - 1, frame_width - 1, frame_height, 1);
	/*************画出地图的细节*************/
	draw(6, 3, 36, 4);
	draw(13, 1, 36, 4);
	int i;
	for (i = 3; i < 39; i = i + 3)
	{
		draw(1, i, 2, 2);
	}
	for (i = 3; i < 39; i = i + 3)
	{
		draw(5, i, 2, 1);
	}
	for (i = 3; i < 39; i = i + 3)
	{
		draw(7, i, 2, 2);
	}
	for (i = 3; i < 39; i = i + 3)
	{
		draw(12, i, 2, 1);
	}
	for (i = 3; i < 39; i = i + 3)
	{
		draw(14, i, 2, 2);
	}
	for (i = 3; i < 39; i = i + 3)
	{
		draw(18, i, 2, 1);
	}

	for (i = 2; i < 39; i = i + 3)
	{
		draw(1, i, 2, 2);
	}
	for (i = 2; i < 39; i = i + 3)
	{
		draw(5, i, 2, 1);
	}
	for (i = 2; i < 39; i = i + 3)
	{
		draw(7, i, 2, 2);
	}
	for (i = 2; i < 39; i = i + 3)
	{
		draw(12, i, 2, 1);
	}
	for (i = 2; i < 39; i = i + 3)
	{
		draw(14, i, 2, 2);
	}
	for (i = 2; i < 39; i = i + 3)
	{
		draw(18, i, 2, 1);
	}
	/*************画出地图上的怪物与宝箱*************/
	for (i = 4; i < 37; i = i + 3)
	{
		draw_(1, i, 0, 3);
		draw_(2, i, 1, 3);
		draw_(4, i, 1, 3);
		draw_(5, i, 0, 3);
		draw_(7, i, 0, 2);
		draw_(8, i, 1, 2);
		draw_(11, i, 1, 2);
		draw_(12, i, 0, 2);
		draw_(14, i, 0, 1);
		draw_(15, i, 1, 1);
		draw_(17, i, 1, 1);
		draw_(18, i, 0, 1);
	}
	draw_(16, 37, 1, 2);
	draw_(3, 1, 1, 3);
	draw_(3, 37, 2, 0);//设立BOSS

					   /*************规则说明*************/
	gotoxy(5, 40);  printf("规则说明");
	gotoxy(6, 40);  printf("本游戏为roguelike回合制RPG");
	gotoxy(7, 40);  printf("一共有三层，每层的怪物逐渐变强");
	gotoxy(8, 40);  printf("每个怪物与宝箱都是随机的");
	gotoxy(9, 40);  printf("EXP达到10*LEVEL是会升级，使英雄数值上升");
	gotoxy(10, 40); printf("请使用w s a d进行移动(小写！！！)");
	gotoxy(11, 40); printf("打到最后的BOSS即为胜利");
	gotoxy(12, 40); printf("P:Player玩家\tB:BOSS\tC:宝箱\tM：怪物");
}					
void draw_(int x, int y, int flag, int kind)//标出宝箱与怪物 
{											//flag 0：宝箱 1：怪物 2:BOSS
	gotoxy(x, y);
	if (flag == 0)
	{
		printf("C");
		map[x][y] = kind + 6;
	}
	else if (flag == 1)
	{
		printf("M");
		map[x][y] = kind + 3;
	}
	else {
		printf("B");
		map[x][y] = 3;
	}
}
void draw(int x, int y, int len, int direction)//传入坐标，长度，方向进行画地图
{															//direction 1:上，2；下，3：左，4：右
	int i;
	gotoxy(x, y);
	for (i = 0; i<len; i++)
	{
		map[x][y] = 1;//在map标记为1，代表有障碍物

		switch (direction)
		{
		case 1:printf("|"); x--; break;
		case 2:printf("|"); x++; break;
		case 3:printf("-"); y--; break;
		case 4:printf("-"); y++; break;
		default:
			break;
		}
		gotoxy(x, y);
	}
}
void blank(int x, int y, int len, int direction)//传入坐标，长度，方向进行地图擦除
{															//direction 1:上，2；下，3：左，4：右
	int i;
	gotoxy(x, y);
	for (i = 0; i<len; i++)
	{
		map[x][y] = 0;//在map标记为0，代表无障碍物
		printf(" ");
		switch (direction)
		{
		case 1:x--; break;
		case 2:x++; break;
		case 3:y--; break;
		case 4:y++; break;
		default:printf("清除bug");
			break;
		}
		gotoxy(x, y);
	}
}
void blank_(int x, int y, int len, int direction)//传入坐标，长度，方向进行文本擦除
{															//direction 1:上，2；下，3：左，4：右
	int i;
	gotoxy(x, y);
	for (i = 0; i<len; i++)
	{
		printf(" ");
		switch (direction)
		{
		case 1:x--; break;
		case 2:x++; break;
		case 3:y--; break;
		case 4:y++; break;
		default:printf("清除bug");
			break;
		}
		gotoxy(x, y);
	}
}
void gotoxy(int x, int y)//移动光标
{
	HANDLE hout;
	COORD cor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cor.X = y;
	cor.Y = x;
	SetConsoleCursorPosition(hout, cor);
}