#include "server.h"

SOCKET serSocket;
//client clients[5];
std::deque <client> clients;

void client_init_T(int i)
{
	clients[i].init();
}
void connect_client()
{
	std::vector <std::thread> T;
	for (int i = 0; i < 5; i++)
	{
		clients.push_back(client(serSocket));
		clients.back().connect();
		clients.back().init();
		T.push_back(std::thread(&client::listen, &(clients.back())));
		T.push_back(std::thread(&client::send_1, &(clients.back())));
		//T.push_back(std::thread(&client::init, clients.back()));
		//T.push_back(std::thread(client_init_T, i));

	}
	for (int i = 0; i < T.size(); i++)
		T[i].join();
}


void main()
{
	//�����׽���
	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest = MAKEWORD(1, 1);
	WSAStartup(myVersionRequest, &wsaData);

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