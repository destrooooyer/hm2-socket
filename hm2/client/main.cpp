#include <WINSOCK2.H>
#include <stdio.h>
#include <thread>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

SOCKET clientSocket;
int run_flag = 1;

void _listen()
{
	while (run_flag)
	{
		char receiveBuf[100] = { 0 };
		recv(clientSocket, receiveBuf, 101, 0);
		printf("%s\n", receiveBuf);
	}
}


void main()
{
	WORD versionRequired;
	WSADATA wsaData;
	versionRequired = MAKEWORD(1, 1);
	WSAStartup(versionRequired, &wsaData);//协议库的版本信息

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN clientsock_in;
	clientsock_in.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	clientsock_in.sin_family = AF_INET;
	clientsock_in.sin_port = htons(6666);
	//bind(clientSocket,(SOCKADDR*)&clientsock_in,strlen(SOCKADDR));//注意第三个参数
	//listen(clientSocket,5);
	connect(clientSocket, (SOCKADDR*)&clientsock_in, sizeof(SOCKADDR));//开始连接
	char receiveBuf[100] = { 0 };
	recv(clientSocket, receiveBuf, 101, 0);
	cout << receiveBuf;

	//输入id
	cout << "请设置您的ID\n";
	char client_id[50] = { 0 };
	cin >> client_id;
	send(clientSocket, client_id, strlen(client_id) + 1, 0);

	recv(clientSocket, receiveBuf, 101, 0);
	cout << receiveBuf;
	cout << "请输入指令，输入help查看帮助\n";

	thread T(_listen);

	getchar();

	regex pt_send("send\\s+\\[(.*)\\]\\s+(.*)");
	regex pt_show_info("show\\s+info\\s+\\[(.*)\\]");
	while (1)
	{
		string str_in;
		getline(cin, str_in);

		match_results<string::const_iterator> rs;
		if (regex_match(str_in, rs, pt_send))
		{
			send(clientSocket, "send", strlen("send") + 1, 0);
			send(clientSocket, rs.str(1).c_str(), strlen(rs.str(1).c_str()) + 1, 0);
			send(clientSocket, rs.str(2).c_str(), strlen(rs.str(2).c_str()) + 1, 0);

		}
		else if (str_in == "exit")
		{
			send(clientSocket, "exit", strlen("exit") + 1, 0);
			run_flag = 0;
			T.join();
			closesocket(clientSocket);
			WSACleanup();
			return;
		}
		else if (str_in == "show log")
		{
			ifstream fin("log.txt");
			string str_in2;
			while (getline(fin, str_in2))
			{
				if (str_in2.find("[" + string(client_id) + "]") != -1)
					cout << str_in2 << endl;
			}
			fin.close();

		}
		else if (regex_match(str_in, rs, pt_show_info))
		{
			send(clientSocket, "show info", strlen("show info") + 1, 0);
			send(clientSocket, rs.str(1).c_str(), strlen(rs.str(1).c_str()) + 1, 0);
		}

		else
		{
			cout << "请输入正确的指令\n";
		}
	}


	closesocket(clientSocket);
	WSACleanup();
	system("pause");
}