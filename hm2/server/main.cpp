#include "server.h"

SOCKET serSocket;
client clients[5];

void connect_client()
{
	for (int i = 0; i < 5; i++)
	{
		client temp(serSocket);
		temp.connect();
		clients[i] = temp;
		clients[i].init();
	}
}

void main()
{
	//�����׽���
	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest = MAKEWORD(1, 1);
	int err;
	err = WSAStartup(myVersionRequest, &wsaData);
	if (!err)
	{
		printf("�Ѵ��׽���\n");
	}
	else
	{
		//��һ�����׽���
		printf("Ƕ����δ��!");
		return;
	}
	serSocket = socket(AF_INET, SOCK_STREAM, 0);//�����˿�ʶ���׽���
													   //��Ҫ�󶨵Ĳ���
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip��ַ
	addr.sin_port = htons(6666);//�󶨶˿�

	bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));//�����
	listen(serSocket, 5);//���еڶ������������ܹ����յ�����������

	//////////////////////////////////////////////////////////////////////////
	//��ʼ���м���
	//////////////////////////////////////////////////////////////////////////
	std::thread T_connect(connect_client);
	T_connect.join();
// 	SOCKADDR_IN clientsocket;
// 	int len = sizeof(SOCKADDR);
// 	while (1)
// 	{
// 		SOCKET serConn = accept(serSocket, (SOCKADDR*)&clientsocket, &len);//������ﲻ��accept����conection�Ļ������ͻ᲻�ϵļ���
// 		//connect(serConn, (SOCKADDR*)&clientsocket, sizeof(SOCKADDR));
// 		char sendBuf[100];
// 
// 		sprintf(sendBuf, "welcome %s to bejing", inet_ntoa(clientsocket.sin_addr));//�ҶԶ�Ӧ��IP���ҽ������ִ�ӡ������
// 		send(serConn, sendBuf, strlen(sendBuf) + 1, 0);
// 		char receiveBuf[100] = { 0 };//����
// 		recv(serConn, receiveBuf, 101, 0);
// 		if (strlen(receiveBuf) != 0)
// 			printf("%s\n", receiveBuf);
// 		closesocket(serConn);//�ر�
// 		//WSACleanup();//�ͷ���Դ�Ĳ���
// 	}
}