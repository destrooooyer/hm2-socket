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
	char receiveBuf[100] = { 0 };//����
	recv(serConn, receiveBuf, 101, 0);
	this->name = receiveBuf;
	cout<<"�������û���" << this->name<<endl;

}