#pragma once
#include <iostream>
#include <conio.h>
using namespace std;
class Account
{
public:
	Account() {}
	~Account() {}
	string getUsername()
	{
		return username;
	}
	string getPassword()
	{
		return password;
	}
	string getPermissions()
	{
		return permissions;
	}
	void setPassword(char* str);
	void setUsername();
	void setPermissions(char* str);
	void setPermissions(const char* str);
private:
	string username;
	string password;
	string permissions;
};