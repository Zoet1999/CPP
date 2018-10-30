#include "stdafx.h"
#include "Client.h"
#include<WINSOCK2.H>  
#include<STDIO.H>  
#include<iostream>  
#include<cstring>  
#include <string>
#include<WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib") 
Client::Client()
{
	
}
void Client::Connect()
{

	
	//初始化WSA windows自带的socket
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{

		printf("error!");
	}
	//创建客户端套接字
	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //客户端套接字
	if (sclient == INVALID_SOCKET)
	{
		printf("invalid socket");

	}
		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(5099);
		inet_pton(AF_INET, "10.202.20.104", (void*)&serAddr.sin_addr.S_un.S_addr);
		if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) //与指定IP地址和端口的服务端连接
		{
			printf("connect error");
			closesocket(sclient);
		}
	
}
void Client::Sendm(std::string str)
{
	const char * sendData=str.c_str();
	send(sclient, sendData, strlen(sendData), 0);
}

std::string Client::rec()
{
	char recData[255];
	int ret = recv(sclient, recData, 255, 0);
	if (ret > 0) {
		recData[ret] = 0x00;
		return recData;
	}
	else
		return "";
}

Client::~Client()
{
	closesocket(sclient);
	WSACleanup();
}
