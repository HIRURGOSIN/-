#include "Account.h"
void Account::fscan()
{
	fstream acc, exp;
	User userbuf;
	Expert expertbuf;
	user.clear();
	expert.clear();
	acc.open("acc.txt", ios::in);
	exp.open("exp.txt", ios::in);
	acc >> key;
	while (!acc.eof())
	{
		userbuf.fscan(acc, key);
		if (userbuf.permissionsGet() == "expert")
		{
			expertbuf.set(userbuf.usernameGet());
			expert.push_back(expertbuf);
		}
		user.push_back(userbuf);
	}
	acc.close();
	for (int i = 0; i < expert.size(); i++)
	{
		expert[i].fscan(exp);
	}
	exp.close();
}
void Account::fprint()
{
	fstream acc, exp;
	acc.open("acc.txt", ios::out | ios::trunc);
	exp.open("exp.txt", ios::out | ios::trunc);
	acc << key;
	for (int i = 0; i < user.size(); i++)
	{
		user[i].encode(key);
		user[i].fprint(acc);
		user[i].decode(key);
	}
	acc.close();
	for (int i = 0; i < expert.size(); i++)
	{
		expert[i].fprint(exp);
		if (i != expert.size() - 1)
			exp << endl;
	}
	exp.close();
}

string Account::login()
{
	Account::fscan();
	for (int i = 0; i < user.size(); i++)
	{
		if (CurrUsername == user[i].usernameGet() && CurrPassword == user[i].passwordGet())
		{
			CurrPermissions = user[i].permissionsGet();
			return CurrPermissions;
		}
	}
	return "0";
}
void Account::UsernameSet(char* str)
{
	CurrUsername = str;
}
void Account::PasswordSet(char* str)
{
	CurrPassword = str;
}