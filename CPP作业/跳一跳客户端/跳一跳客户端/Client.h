#pragma once
#include "stdafx.h"
#include<WINSOCK2.H>  
#include<STDIO.H>  
#include<iostream>  
#include<cstring>  
#include <string>
#include<WS2tcpip.h>
class Client
{
	SOCKET sclient;
public:
	Client();
	~Client();
	void Connect();
	void Sendm(std::string str);

	std::string rec();
};

