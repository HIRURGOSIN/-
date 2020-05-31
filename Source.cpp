#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <WinSock2.h>
#include <process.h>
#include "classes.h"
using namespace std;
char srcX;

void ThreadFunc(void* client_socket)
{
	MainMenu(client_socket);
	cout << "Client succesfully disconnected" << endl;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	sockaddr_in localAddr;
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(1280);
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (WSAStartup(wVersionRequested, &wsaData))
	{
		cout << "Error starting up" << endl;
		return WSAGetLastError();
	}
	cout << "WSAStartup succesfull" << endl;
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		cout << "Error creating socket" << endl;
		return WSAGetLastError();
	}
	cout << "Socket created succesfully" << endl;
	if (bind(s, (struct sockaddr*)&localAddr, sizeof(localAddr)) == SOCKET_ERROR)
	{
		cout << "Error binding" << endl;
		return WSAGetLastError();
	}
	cout << "Binding complete" << endl;
	if (listen(s, 5) == SOCKET_ERROR)
	{
		cout << "Error listening" << endl;
		return WSAGetLastError();
	}
	cout << "Recieve ready" << endl;
	while (true)
	{
		SOCKET clientSocket;
		sockaddr_in clientAddr;
		int clientAddrSize = sizeof(clientAddr);
		clientSocket = accept(s, (sockaddr*)&clientAddr, &clientAddrSize);
		if (clientSocket == SOCKET_ERROR)
		{
			cout << "Connection corrupted" << endl;
			cout << WSAGetLastError();
		}
		else
		{
			cout << "Client connected" << endl;
			_beginthread(ThreadFunc, 0, (void*)clientSocket);
		}

	}
	WSACleanup();
	return 0;
}