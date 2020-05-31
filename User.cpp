#include "User.h"
using namespace std;
void User::encode(int code)
{
	for (int i = 0; i < username.length(); i++)
	{
		username[i] += code;
	}
	for (int i = 0; i < password.length(); i++)
	{
		password[i] += code;
	}
}
void User::decode(int code)
{
	for (int i = 0; i < username.length(); i++)
	{
		username[i] -= code;
	}
	for (int i = 0; i < password.length(); i++)
	{
		password[i] -= code;
	}
}
void User::fprint(fstream& acc)
{
	acc << endl;
	acc << username << " ";
	acc << password << " ";
	acc << permissions;
}
void User::fscan(fstream& acc, int key)
{
	acc >> username;
	acc >> password;
	acc >> permissions;
	User::decode(key);
}
string User::passwordSend(string CurrPermissions)
{
	string buf = password;
	if (CurrPermissions == "adminp")
	{
		return password;
	}
	else
	{
		for (int i = 0; i < buf.length(); i++)
		{
			buf[i] = '*';
		}
		return buf;
	}
}
/*void User::print(string CurrentPermissions, int counter)
{
	cout << "|| User #" << counter + 1;
	cout << "|";
	cout << " login: " << username;
	for (int j = 0; j < 35 - username.length() - strlen("login"); j++)
	{
		cout << " ";
	}
	cout << "|";
	if (CurrentPermissions=="adminp")
	{
		cout << " pass: " << password;
		for (int j = 0; j < 35 - password.length() - strlen("pass"); j++)
		{
			cout << " ";
		}
		cout << "|";
	}
	else
	{
		cout << " pass: ";
		for (int j = 0; j < password.length(); j++)
		{
			cout << "*";
		}
		for (int j = 0; j < 35 - password.length() - strlen("pass"); j++)
		{
			cout << " ";
		}
		cout << "|";
	}
	cout << " permissions: " << permissions;
	for (int j = 0; j < 43 - permissions.length() - strlen("permissions"); j++)
	{
		cout << " ";
	}
	cout << "||";
	cout << endl;
}*/