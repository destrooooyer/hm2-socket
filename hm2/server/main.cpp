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
	//创建套接字
	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest = MAKEWORD(1, 1);
	WSAStartup(myVersionRequest, &wsaData);

	serSocket = socket(AF_INET, SOCK_STREAM, 0);//创建了可识别套接字
													   //需要绑定的参数
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip地址
	addr.sin_port = htons(6666);//绑定端口

	bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));//绑定完成
	listen(serSocket, 5);//其中第二个参数代表能够接收的最多的连接数

	//////////////////////////////////////////////////////////////////////////
	//开始进行监听
	//////////////////////////////////////////////////////////////////////////
	std::thread T_connect(connect_client);
	T_connect.join();

// 	SOCKADDR_IN clientsocket;
// 	int len = sizeof(SOCKADDR);
// 	while (1)
// 	{
// 		SOCKET serConn = accept(serSocket, (SOCKADDR*)&clientsocket, &len);//如果这里不是accept而是conection的话。。就会不断的监听
// 		//connect(serConn, (SOCKADDR*)&clientsocket, sizeof(SOCKADDR));
// 		char sendBuf[100];
// 
// 		sprintf(sendBuf, "welcome %s to bejing", inet_ntoa(clientsocket.sin_addr));//找对对应的IP并且将这行字打印到那里
// 		send(serConn, sendBuf, strlen(sendBuf) + 1, 0);
// 		char receiveBuf[100] = { 0 };//接收
// 		recv(serConn, receiveBuf, 101, 0);
// 		if (strlen(receiveBuf) != 0)
// 			printf("%s\n", receiveBuf);
// 		closesocket(serConn);//关闭
// 		//WSACleanup();//释放资源的操作
// 	}
}