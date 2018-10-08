#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <process.h>

#include <WinSock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

enum Packet
{
	P_ChatMessage
};

class Server
{
public:
	Server(int PORT, bool BroadcastPublically = false);
	bool ListenForNewConnection();
private:
	bool SendInt(int index, int _int);
	bool GetInt(int index, int & _int);

	bool SendPacketType(int index, Packet _packettype);
	bool GetPacketType(int index, Packet & _packettype);

	bool SendString(int index, std::string & _string);
	bool GetString(int index, std::string & _string);

	bool ProcessPacket(int index, Packet _packettype);

	static void ClientHandlerThread(int index);
private:
	SOCKET Connections[100];
	int connectionCounter = 0;
	sockaddr_in service; //addr for bind listening socket to
	int servicelen = sizeof(service);
						 //memset(&service, 0, sizeof(service)); //sets to 0
	SOCKET mainSocket;
};

static Server * serverptr;