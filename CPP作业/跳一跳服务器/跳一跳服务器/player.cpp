#include "stdafx.h"
#include "player.h"
#include <cstring>
#include <WinSock2.h>
#include <thread>
#include <iostream>
#include <sstream>
#include <map>

std::map<int, match> player::m;
player::player()
{
	memset(name, 0, sizeof(name));
}


player::~player()
{
}


void player::rank(SOCKET sockConn)
{

}

void player::gameSolo(SOCKET sockConn)
{
	char recvBuf[100];
	memset(recvBuf, 0, sizeof(recvBuf));
	recv(sockConn, recvBuf, sizeof(recvBuf), 0);
	printf("%s", recvBuf);
	std::stringstream sstr(recvBuf);
	sstr >> score;
	//保存player::name和player::score到文件里
}
void player::gamePK(SOCKET sockConn)
{
	int password;
	char recvBuf[100];
	memset(recvBuf, 0, sizeof(recvBuf));
	recv(sockConn, recvBuf, sizeof(recvBuf), 0);
	printf("%s", recvBuf);
	std::stringstream sstr(recvBuf);
	sstr >> password;
	if (m[password].a == -1)
	{
		m[password].a = 0;
		strcpy_s(m[password].na ,name);

		while (m[password].b == -1)
		{
			//如果受到退出信号退出
		}
		char buf[] = "search succeed";
		send(sockConn, buf, sizeof(buf), 0);

		char recvBuf[100];
		memset(recvBuf, 0, sizeof(recvBuf));
		recv(sockConn, recvBuf, sizeof(recvBuf), 0);
		printf("%s", recvBuf);
		std::stringstream sstr(recvBuf);
		sstr >> PKscore;
		m[password].a = PKscore;
		while (m[password].b == 0)
		{
			//如果受到退出信号退出
		}
	}
	else {
		m[password].b = 0;
		strcpy_s(m[password].nb, name);
		char buf[] = "search succeed";
		send(sockConn, buf, sizeof(buf), 0);

		char recvBuf[100];
		memset(recvBuf, 0, sizeof(recvBuf));
		recv(sockConn, recvBuf, sizeof(recvBuf), 0);
		printf("%s", recvBuf);
		std::stringstream sstr(recvBuf);
		sstr >> PKscore;
		while (m[password].a == 0)
		{
			//如果受到退出信号退出
		}
	}
	


}

void player::login(SOCKET sockConn)
{
	player p;
	recv(sockConn, name, sizeof(name), 0);
	printf("%s", name);

	while (1) {
		char recvBuf[100];

		memset(recvBuf, 0, sizeof(recvBuf));

		// 接收数据

		recv(sockConn, recvBuf, sizeof(recvBuf), 0);
		printf("%s", recvBuf);
		if (!strcmp(recvBuf, "gameSolo"))
		{
			printf(" in%s", recvBuf);
			gameSolo(sockConn);
		}
		else if (!strcmp(recvBuf, "gamePK"))
		{
			printf(" in%s", recvBuf);
			gamePK(sockConn);
		}
		else if (!strcmp(recvBuf, "end"))
		{
			char buf[] = "downline succeed";
			send(sockConn, buf, sizeof(buf), 0);
			return;
		}
		else if (!strcmp(recvBuf, "rank"))
		{
			printf(" in%s", recvBuf);
			rank(sockConn);
		}
	}
}