#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include "classes.h"
using namespace std;
char buf[30];
char str[30];

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu menu;
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	sockaddr_in destAddr;
	if (WSAStartup(wVersionRequested, &wsaData))
	{
		cout << "Error starting up" << endl;
		return WSAGetLastError();
	}
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	destAddr.sin_family = AF_INET;
	destAddr.sin_port = htons(1280);
	destAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (connect(s, (sockaddr*)&destAddr, sizeof(destAddr))!=0)
	{
		cout << "Connection error";
		return WSAGetLastError();
	}
	while (true)
	{
		switch (menu.CreateMenu("Вход*Регистрация*Выход*"))
		{
		case 1: Login(s); break;
		case 2: Register(s); break;
		case 3: Disconnect(s); break;
		}
	}
	closesocket(s);
	WSACleanup();
}