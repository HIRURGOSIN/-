#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <WinSock2.h>
#include "Integer.h"
#include "Menu.h"
#include "Account.h"
#include "Table.h"
#define SIZE 100

using namespace std;



void passscan(char password[]);
void passscan(char password[], string custommsg);

void sendString(SOCKET& s, string str);
string recvString(SOCKET& s);

int recvInt(SOCKET& s);
void sendInt(SOCKET& s, int a);
void sendInt(SOCKET& s, Integer a);

void adminMenu(SOCKET& s);
void userMenu(SOCKET& s);
void expertMenu(SOCKET& s);

void accountsMenu(SOCKET& s);
void accountsList(SOCKET& s);
void accountsAdd(SOCKET& s);
void accountsRem(SOCKET& s);
void accountsPassch(SOCKET& s);
void accountsKeygen(SOCKET& s);

void expertFill(SOCKET& s);
void expertShow(SOCKET& s);

void Login(SOCKET &s);
void Register(SOCKET& s);
void Disconnect(SOCKET &s);

void workersMenu(SOCKET& s);
void workersList(SOCKET& s);
void workersAdd(SOCKET& s);
void workersEdit(SOCKET& s);
void workersSort(SOCKET& s);
void workersSearch(SOCKET& s);
void workersRem(SOCKET& s);
void workersEstimate(SOCKET& s);
void workersRating(SOCKET& s);

static Account account;