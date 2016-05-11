#include <WINSOCK2.H>
#include <stdio.h>
#include <string>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

void main()
{
	int err;
	WORD versionRequired;
	WSADATA wsaData;
	versionRequired = MAKEWORD(1, 1);
	err = WSAStartup(versionRequired, &wsaData);//协议库的版本信息
	if (!err)
	{
		printf("客户端嵌套字已经打开!\n");
	}
	else
	{
		printf("客户端的嵌套字打开失败!\n");
		return;//结束
	}
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN clientsock_in;
	clientsock_in.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	clientsock_in.sin_family = AF_INET;
	clientsock_in.sin_port = htons(6666);
	//bind(clientSocket,(SOCKADDR*)&clientsock_in,strlen(SOCKADDR));//注意第三个参数
	//listen(clientSocket,5);
	connect(clientSocket, (SOCKADDR*)&clientsock_in, sizeof(SOCKADDR));//开始连接
// 	char receiveBuf[100] = {0};
// 	recv(clientSocket, receiveBuf, 101, 0);
// 	printf("%s\n", receiveBuf);

	//输入id
	cout << "请输入您的ID";
	char client_id[50] = {0};
	cin >> client_id;

	send(clientSocket, client_id, strlen(client_id) + 1, 0);
	closesocket(clientSocket);
	WSACleanup();
	system("pause");
}