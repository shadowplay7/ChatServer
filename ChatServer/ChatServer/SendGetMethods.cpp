#include "Server.h"

bool Server::SendInt(int index, int _int)
{
	int RetnCheck = send(Connections[index], (char*)&_int, sizeof(int), NULL); //send int: _int
	if (RetnCheck == SOCKET_ERROR)
		return false; //false cnnection isse
	return true;	//int ok sent
}

bool Server::GetInt(int index, int & _int)
{
	int RetnCheck = recv(Connections[index], (char*)&_int, sizeof(int), NULL); //recv int: _int
	if (RetnCheck == SOCKET_ERROR)
		return false; //false cnnection isse
	return true;	//int ok sent
}

bool Server::SendPacketType(int index, Packet _packettype)
{
	int RetnCheck = send(Connections[index], (char*)&_packettype, sizeof(Packet), NULL); //send int: _int
	if (RetnCheck == SOCKET_ERROR)
		return false; //false cnnection isse
	return true;	//int ok sent
}

bool Server::GetPacketType(int index, Packet & _packettype)
{
	int RetnCheck = recv(Connections[index], (char*)&_packettype, sizeof(Packet), NULL); //recv int: _int
	if (RetnCheck == SOCKET_ERROR)
		return false; //false cnnection isse
	return true;	//int ok sent
}

bool Server::SendString(int index, std::string & _string)
{
	if (!SendPacketType(index, P_ChatMessage))
		return false;
	int bufferlenght = _string.size();
	if (!SendInt(index, bufferlenght))
		return false;
	int RetnCheck = send(Connections[index], _string.c_str(), bufferlenght, NULL);
	if (RetnCheck == SOCKET_ERROR)
		return false;
	return true;
}

bool Server::GetString(int index, std::string & _string)
{
	int bufferlenght; //msg length
	if (!GetInt(index, bufferlenght))
		return false;
	char * buffer = new char[bufferlenght + 1];
	buffer[bufferlenght] = '\0';
	int RetnCheck = recv(Connections[index], buffer, bufferlenght, NULL);
	_string = buffer;
	delete[] buffer;
	if (RetnCheck == SOCKET_ERROR)
		return false;
	return true;
}