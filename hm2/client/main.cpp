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
	err = WSAStartup(versionRequired, &wsaData);//Э���İ汾��Ϣ
	if (!err)
	{
		printf("�ͻ���Ƕ�����Ѿ���!\n");
	}
	else
	{
		printf("�ͻ��˵�Ƕ���ִ�ʧ��!\n");
		return;//����
	}
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN clientsock_in;
	clientsock_in.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	clientsock_in.sin_family = AF_INET;
	clientsock_in.sin_port = htons(6666);
	//bind(clientSocket,(SOCKADDR*)&clientsock_in,strlen(SOCKADDR));//ע�����������
	//listen(clientSocket,5);
	connect(clientSocket, (SOCKADDR*)&clientsock_in, sizeof(SOCKADDR));//��ʼ����
// 	char receiveBuf[100] = {0};
// 	recv(clientSocket, receiveBuf, 101, 0);
// 	printf("%s\n", receiveBuf);

	//����id
	cout << "����������ID";
	char client_id[50] = {0};
	cin >> client_id;

	send(clientSocket, client_id, strlen(client_id) + 1, 0);
	closesocket(clientSocket);
	WSACleanup();
	system("pause");
}