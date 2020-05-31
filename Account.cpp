#include "Account.h"
using namespace std;
void Account::setUsername()
{
	cout << "Ваш логин: ";
	cin >> username;
}
void Account::setPassword(char* str)
{
	password = str;
}
void Account::setPermissions(char* str)
{
	permissions = str;
}
void Account::setPermissions(const char* str)
{
	permissions = str;
}