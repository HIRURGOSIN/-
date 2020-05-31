#pragma once
#include "User.h"
#include "Expert.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
class Account
{
public:
	Account() {}
	~Account() {}
	void fscan();
	void fprint();
	string login();
	void UsernameSet(char *);
	void PasswordSet(char*);
	string UsernameGet()
	{
		return CurrUsername;
	}
	string PermissionsGet()
	{
		return CurrPermissions;
	}
	int getAmountOfUsers()
	{
		return user.size();
	}
	vector<User> user;
	vector<Expert> expert;
private:
	string CurrUsername;
	string CurrPassword;
	string CurrPermissions;
	int key = 0;
};

