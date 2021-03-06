#include "stdafx.h"
#include <stdio.h>
#include <WinSock2.h>
#include <thread>
#include "player.h"

#pragma comment(lib, "ws2_32.lib")


void start(SOCKET sockConn)
{
	player a;
	a.login(sockConn);

}
int main(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	int port = 5099;

	char buf[] = "login succeed";


	//加载套接字失败时报错
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("加载套接字失败：%d\n", WSAGetLastError());
		return 1;
	}

	//创建套接字
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);


	/*
	//设置为非阻塞
	int per = 1;
	ioctlsocket(sockSrv, FIONBIO, (u_long FAR*) &per);
	*/

	// 初始化IP和端口信息

	SOCKADDR_IN addrSrv;

	addrSrv.sin_family = AF_INET;

	addrSrv.sin_port = htons(port);

	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	//bind 
	if (bind(sockSrv, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		printf("套接字绑定失败：%d......\n", WSAGetLastError());
		return 1;
	}

	if (listen(sockSrv, 10) == SOCKET_ERROR) {
		printf("套接字监听失败：%d......\n", WSAGetLastError());
		return 1;
	}
	// 客户端信息

	SOCKADDR_IN addrClient;

	int len = sizeof(SOCKADDR);
	// 开始监听

	printf("服务端启动,开始监听\n");

	while (1)

	{
		// 等待客户请求到来  
		SOCKET sockConn = accept(sockSrv, (SOCKADDR *)&addrClient, &len);

		// 发送登陆成功信息

		if (send(sockConn, buf, sizeof(buf), 0) == SOCKET_ERROR) {

			printf("发送数据失败......\n");

			break;

		}
		std::thread t(start, sockConn);
		t.detach();

	}
	// 关闭套接字

	closesocket(sockSrv);

	WSACleanup();

	system("pause");
	return 0;
}




