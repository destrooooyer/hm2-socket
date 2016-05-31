#include "server.h"
#include <sstream>
#include <windows.h>
using namespace std;

extern deque <client> clients;
CRITICAL_SECTION cs;

client::client(SOCKET sock_in)
{
	this->serSocket = sock_in;
	this->listen_flag = 1;
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
	send(serConn, "已与server连接成功\n", strlen("已与server连接成功\n") + 1, 0);
	printf("与client连接成功\n");
}

void client::init()
{
	char receiveBuf[100] = { 0 };//接收
	recv(serConn, receiveBuf, 101, 0);
	name = receiveBuf;
	cout << "client设置其ID为：" << name << endl;
	send(serConn, "设置ID成功\n", strlen("设置ID成功\n") + 1, 0);

	lvl = rand() % 100;
	sex = rand() % 2 == 0 ? "male" : "female";
	age = rand() % 100;

	string str_temp = "年龄： ";
	stringstream ss;
	ss << age;
	str_temp += ss.str() + "\t性别：" + sex + "\t等级：";
	ss.clear();
	ss << lvl;
	str_temp += ss.str();
	cout << "该client的信息为：\n\t" << str_temp << endl;



	// 	thread T_send(&client::send_1, this);
	// 	thread T_listen(&client::listen, this);
	// 	T_listen.join();
	// 	T_send.join();
}

void client::send_1()
{
	while (listen_flag)
	{
		//cout << send_buf.size();
		if (send_buf.size() != 0)
		{
			pair<string, string> temp = send_buf.back();
			//EnterCriticalSection(&cs);
			send_buf.pop_back();
			//LeaveCriticalSection(&cs);
			string str_out = "client[";
			str_out += temp.first;
			str_out += "]\t=>\tclient[";
			str_out += name;
			str_out += "]:\t";
			str_out += temp.second;
			str_out += "\n";
			cout << str_out;
			ofstream fout("log.txt", ios::app);
			fout << str_out;
			fout.close();

			str_out = "client[";
			str_out += temp.first;
			str_out += "]:\t";
			str_out += temp.second;
			send(serConn, str_out.c_str(), strlen(str_out.c_str()) + 1, 0);

			// 			send(serConn, temp.first.c_str(), strlen(temp.first.c_str()) + 1, 0);
			// 			send(serConn, temp.second.c_str(), strlen(temp.second.c_str()) + 1, 0);

		}
		Sleep(100);

	}
}

void client::listen()
{
	while (listen_flag)
	{
		char receiveBuf[100] = { 0 };//接收
		recv(serConn, receiveBuf, 101, 0);
		/*		cout << receiveBuf;*/
		//cout << receiveBuf;
		if (strcmp(receiveBuf, "send") == 0)
		{
			char receiveBuf2[100] = { 0 };//接收
			recv(serConn, receiveBuf2, 101, 0);
			int flag = -1;
			for (int i = 0; i < clients.size() - 1; i++)
			{
				//cout << receiveBuf2 << endl;
				if (clients[i].check_id(receiveBuf2))
				{
					flag = i;
					break;
				}
			}

			recv(serConn, receiveBuf2, 101, 0);
			if (flag != -1)
				clients[flag].add_send_buf(name, receiveBuf2);


		}
		else if (strcmp(receiveBuf, "show info") == 0)
		{
			char receiveBuf2[100] = { 0 };//接收
			recv(serConn, receiveBuf2, 101, 0);
			for (int i = 0; i < clients.size() - 1; i++)
			{
				//cout << receiveBuf2 << endl;
				if (clients[i].check_id(receiveBuf2))
				{
					string str_temp = "年龄： ";
					stringstream ss;
					ss << clients[i].age;
					str_temp += ss.str() + "\t性别：" + clients[i].sex + "\t等级：";
					ss.clear();
					ss << clients[i].lvl;
					str_temp += ss.str();

					send(serConn, str_temp.c_str(), strlen(str_temp.c_str()) + 1, 0);

					cout << "client[" << name << "] checked info of client[" << receiveBuf2 << "]" << endl;

					goto _break;
				}
			}

			send(serConn, "wrong id", strlen("wrong id") + 1, 0);
		_break:;
		}
		else if (strcmp(receiveBuf, "exit") == 0)
		{
			listen_flag = 0;
			cout << "client[" << name << "] exited" << endl;
		}
	}
}

int client::check_id(char id[])
{
	//cout << '[' << id << ']' << '[' << name << ']' << endl;
	if (strcmp(id, name.c_str()) == 0)
		return 1;
	return 0;
}

void client::add_send_buf(string name, string text)
{
	//EnterCriticalSection(&cs);
	send_buf.push_back(pair<string, string>(name, text));
	//cout << send_buf.size();
	//LeaveCriticalSection(&cs);
}