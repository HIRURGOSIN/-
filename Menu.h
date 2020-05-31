#pragma once
#include <WinSock2.h>
#include <string>
#include <vector>
#include <iostream>
#include <conio.h>
using namespace std;
class Menu
{
public:
	Menu() {}
	~Menu() {}
	int CreateMenu(string menubullets);
	int CreateMenu(string menubullets, string custommsg);
	void Jump();
private:
	int highlighter = 1;
	vector<string> MenuBullet;
};