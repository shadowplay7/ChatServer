#include "Server.h"


	int main()
	{
		system("pause");
		Server MyServer(1111); //Create server on port 100
		for (int i = 0; i < 100; i++) //Up to 100 times...
		{
			MyServer.ListenForNewConnection(); //Accept new connection (if someones trying to connect)
		}
		system("pause");
		return 0;
	

	//SOCKET mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //main listening socket, if fail return err

	//if (mainSocket == INVALID_SOCKET)
	//{
	//	printf("Err creating socket: %ld\n", WSAGetLastError());
	//	WSACleanup();
	//	return 1;
	//}

	//if (bind(mainSocket, (SOCKADDR *)&service, sizeof(service)) == SOCKET_ERROR) //binding address to socket, if fail closesocket
	//{
	//	printf("bind() failed.\n");
	//	closesocket(mainSocket);
	//	return 1;
	//}

	//if (listen(mainSocket, SOMAXCONN) ==SOCKET_ERROR)	//mainSocket into listener state - maxconnections
	//	printf("Err list on sock.\n");
	//	
	//SOCKET acceptSocket = SOCKET_ERROR; //socket for new client connection
	//printf("Wait for a client to connect..\n");

	//for (int i = 0; i < 100; i++)
	//{
	//	acceptSocket = accept(mainSocket, NULL, NULL);
	//		if (acceptSocket == 0)
	//		{
	//			std::cout << "Failed to accept clients connection." << std::endl;
	//		}
	//		else
	//		{
	//			std::cout << "Client Connected!" << std::endl;
	//			Connections[i] = acceptSocket;
	//			connectionCounter++;
	//			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(i), NULL, NULL);
	//			std::string WD = "Witajcie!";
	//			SendString(i, WD);

				/*Packet chatmessagepacket = P_ChatMessage;
				send(Connections[i], (char*)&chatmessagepacket, sizeof(int), NULL);
				int WDLenght = WD.size();
				send(acceptSocket, (char*)&WDLenght, sizeof(int), NULL);
				send(acceptSocket, WD.c_str(), WDLenght, NULL);*/
		//	}
	//}

//	while (acceptSocket == SOCKET_ERROR)
//	{
//		acceptSocket = accept(mainSocket, NULL, NULL);
//	}
//
//	printf("Client connected.\n");
//	mainSocket = acceptSocket;
//
//	int bytesSent;
//	int bytesRecv = SOCKET_ERROR;
//	char sendbuf[32] = "Server says hello!";
//	char recvbuf[32] = "";
//
//	bytesRecv = recv(mainSocket, recvbuf, 32, 0);
//	//printf("Bytes received: %ld\n", bytesRecv);
//	printf("%s\n", recvbuf);
//
//	bytesSent = send(mainSocket, sendbuf, strlen(sendbuf), 0);
//	//printf("Bytes sent: %ld\n", bytesSent);
//
     system("pause");
}