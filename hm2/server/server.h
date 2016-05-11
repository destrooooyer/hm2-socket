#ifndef SERVER_H
#define SERVER_H

#include <WINSOCK2.H>
#include <string>
#include <stdio.h>
#include <iostream>
#include <thread>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

/*using namespace std;*/

class client
{
public:
	client(SOCKET serSocket);
	client();
	~client();

	void connect();
	void init();

private:
	std::string name;
	SOCKADDR_IN clientsocket;
	SOCKET serConn;
	SOCKET serSocket;
};



#endif