#pragma once
#include "User.h"
#include "Account.h"
#include "Worker.h"
#include "Expert.h"
#include <WinSock2.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <random>

#define SIZE 100
using namespace std;

void sendString(void* client_socket, string str);
string recvString(void* client_socket);

void sendInt(void* client_socket, int a);
int recvInt(void* client_socket);

void sendFloat(void* client_socket, float a);

int login(void* client_socket, Account& account);
void reg(void* client_socket, Account& account);

void MainMenu(void *client_socket);


void adminMenu(void* client_socket, Account& account);
void userMenu(void* client_socket, Account& account);
void expertMenu(void* client_socket, Account& account);

void accountsMenu(void* client_socket, Account& account);
void accountsList(void* client_socket, Account& account);
void accountsAdd(void* client_socket, Account& account);
void accountsRem(void* client_socket, Account& account);
void accountsPassch(void* client_socket, Account& account);
void accountsKeygen(void* client_socket, Account& account);

void workersMenu(void* client_socket, Account& account);
void workersList(void* client_socket, Account& account);
void workersAdd(void* client_socket, Account& account);
void workersRem(void* client_socket, Account& account);
void workersEdit(void* client_socket, Account& account);
void workersSearch(void* client_socket, Account& account);
void workersSort(void* client_socket, Account& account);
void workersEstimate(void* client_socket, Account& account);
void workersRating(void* client_socket, Account& account);

int surnameCmp(class Worker& l, class Worker& r);
int nameCmp(class Worker& l, class Worker &r);
int patronymicCmp(class Worker& l, class Worker& r);
int commendsCmp(class Worker& l, class Worker& r);
int reportsCmp(class Worker& l, class Worker& r);
int hoursCmp(class Worker& l, class Worker& r);
int detailsCmp(class Worker& l, class Worker& r);
int markCmp(class Worker& l, class Worker& r);

static vector<Worker> worker;