#pragma once
#include <map>
#include <stdio.h>
#include <WinSock2.h>
#include <thread>

struct match
{
	int a=-1;
	char na[100] = "";
	int b=-1;
	char nb[100] = "";
};

class player
{
	char name[100];
	int score;
	int PKscore;
	static std::map<int,match> m;
public:
	player();
	~player();
	void login(SOCKET sockConn);
	void gameSolo(SOCKET sockConn);
	void gamePK(SOCKET sockConn);
	void rank(SOCKET sockConn);
};

