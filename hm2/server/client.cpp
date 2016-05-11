#include "server.h"
using namespace std;

client::client(SOCKET sock_in)
{
	this->serSocket = sock_in;
}

client::client()
{
}

client::~client()
{
}

void client::connect()
{
	int len = sizeof(SOCKADDR);
	serConn = accept(serSocket, (SOCKADDR*)&clientsocket, &len);
}

void client::init()
{
	char receiveBuf[100] = { 0 };//接收
	recv(serConn, receiveBuf, 101, 0);
	this->name = receiveBuf;
	cout<<"已连接用户：" << this->name<<endl;

}