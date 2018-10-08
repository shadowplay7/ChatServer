#include "Server.h"

Server::Server(int PORT, bool BroadcastPublically)
{
	WSADATA wsaData;

	int resut = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (resut != NO_ERROR)
		printf("Init error.\n");

	
	if (BroadcastPublically)
		service.sin_addr.s_addr = htonl(INADDR_ANY);
	else
		service.sin_addr.s_addr = inet_addr("127.0.0.1"); //locally
	service.sin_port = htons(PORT); //port
	service.sin_family = AF_INET;		// IPv4

	mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //main listening socket, if fail return err

	if (mainSocket == INVALID_SOCKET)
	{
		printf("Err creating socket: %ld\n", WSAGetLastError());
		WSACleanup();
	}

	if (bind(mainSocket, (SOCKADDR *)&service, sizeof(service)) == SOCKET_ERROR) //binding address to socket, if fail closesocket
	{
		printf("bind() failed.\n");
		closesocket(mainSocket);
	}

	if (listen(mainSocket, SOMAXCONN) ==SOCKET_ERROR)	//mainSocket into listener state - maxconnections
		printf("Err list on sock.\n");
	
	serverptr = this;
}

bool Server::ListenForNewConnection()
{
	SOCKET newConnection = accept(mainSocket, (SOCKADDR*)&service, &servicelen); //Accept a new connection
	if (newConnection == 0) //If accepting the client connection failed
	{
		std::cout << "Failed to accept the client's connection." << std::endl;
		return false;
	}
	else //If client connection properly accepted
	{
		std::cout << "Client Connected! ID:" << connectionCounter << std::endl;
		Connections[connectionCounter] = newConnection; //Set socket in array to be the newest connection before creating the thread to handle this client's socket.
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(connectionCounter), NULL, NULL); //Create Thread to handle this client. The index in the socket array for this thread is the value (i).
		std::string WD = "MOTD: Welcome! This is the message of the day!.";
		SendString(connectionCounter, WD);
		connectionCounter += 1; //Incremenent total # of clients that have connected
		return true;
	}
}

bool Server::ProcessPacket(int ID, Packet _packettype)
{
	switch (_packettype)
	{
	case P_ChatMessage: //Packet Type: chat message
	{
		std::string Message; //string to store our message we received
		if (!GetString(ID, Message)) //Get the chat message and store it in variable: Message
			return false; //If we do not properly get the chat message, return false
						  //Next we need to send the message out to each user
		for (int i = 0; i < connectionCounter; i++)
		{
			if (i == ID) //If connection is the user who sent the message...
				continue;//Skip to the next user since there is no purpose in sending the message back to the user who sent it.
			if (!SendString(i, Message)) //Send message to connection at index i, if message fails to be sent...
			{
				std::cout << "Failed to send message from client ID: " << ID << " to client ID: " << i << std::endl;
			}
		}
		std::cout << "Processed chat message packet from user ID: " << ID << std::endl;
		break;
	}

	default: //If packet type is not accounted for
	{
		std::cout << "Unrecognized packet: " << _packettype << std::endl; //Display that packet was not found
		break;
	}
	}
	return true;
}

void Server::ClientHandlerThread(int ID) //ID = the index in the SOCKET Connections array
{
	Packet PacketType;
	while (true)
	{
		if (!serverptr->GetPacketType(ID, PacketType)) //Get packet type
			break; //If there is an issue getting the packet type, exit this loop
		if (!serverptr->ProcessPacket(ID, PacketType)) //Process packet (packet type)
			break; //If there is an issue processing the packet, exit this loop
	}
	std::cout << "Lost connection to client ID: " << ID << std::endl;
	closesocket(serverptr->Connections[ID]);
}