#ifndef SERVER_H
#define SERVER_H

#include <WINSOCK2.H>
#include <string>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <deque>
#include <vector>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

/*using namespace std;*/

class client
{
public:
	client(SOCKET);
	client();
	~client();

	void connect();
	void init();
	void add_send_buf(std::string a, std::string b);
	void listen();
	void send_1();
	int check_id(char a[]);
	std::string name;

private:
	int listen_flag;
	SOCKADDR_IN clientsocket;
	SOCKET serConn;
	SOCKET serSocket;
	std::vector <std::pair<std::string, std::string> > send_buf;


};



#endif