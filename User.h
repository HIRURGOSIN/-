#pragma once
#include <fstream>
#include <iostream>
using namespace std;
class User
{
private:
	string username;
	string password;
	string permissions;
public:
	void encode(int code);
	void decode(int code);
	void fprint(fstream& acc);
	void fscan(fstream& acc, int key);
	string passwordSend(string CurrPermissions);
	string usernameGet()
	{
		return username;
	}
	string passwordGet()
	{
		return password;
	}
	string permissionsGet()
	{
		return permissions;
	}
	void usernameSet(string Username)
	{
		username = Username;
	}
	void passwordSet(string Password)
	{
		password = Password;
	}
	void permissionsSet(string Permissions)
	{
		permissions = Permissions;
	}
	//friend bool operator==(User& lhs, User& rhs) { return lhs.username == rhs.username; }
	//void print(string CurrentPermissions, int counter);

};