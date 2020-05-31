#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include "classes.h"
using namespace std;

char DataToSend[100];
char DataToRecv[100];

void passscan(char password[])
{
	cout << "������� ������: ";
	char buf;
	for (int i = 0; i < 256; i++)
	{
		buf = _getch();
		if (buf == '\b' && i != 0)
		{
			cout << "\b \b";
			password[i - 1] = '\0';
			i -= 2;
		}
		else if (buf == '\b' && i == 0)
		{
			i--;
			continue;
		}
		else if (buf == '\r')
		{
			break;
		}
		else
		{
			password[i] = buf;
			password[i + 1] = '\0';
			cout << "*";
		}
	}
	if (password == " ")
	{
		system("cls");
		cout << "������������ ������!" << endl;
		cout << "��������� �������:" << endl;
		_getch();
		passscan(password);
	}
	cout << endl;
}
void passscan(char password[], string custommsg)
{
	cout << custommsg;
	char buf;
	for (int i = 0; i < 256; i++)
	{
		buf = _getch();
		if (buf == '\b' && i != 0)
		{
			cout << "\b \b";
			password[i - 1] = '\0';
			i -= 2;
		}
		else if (buf == '\b' && i == 0)
		{
			i--;
			continue;
		}
		else if (buf == '\r')
		{
			break;
		}
		else
		{
			password[i] = buf;
			password[i + 1] = '\0';
			cout << "*";
		}
	}
	if (password == " ")
	{
		system("cls");
		cout << "������������ ������!" << endl;
		cout << "��������� �������:" << endl;
		_getch();
		passscan(password);
	}
	cout << endl;
}

void sendString(SOCKET& s, string str)
{
	const char* cStr;
	cStr = str.c_str();
	send(s, cStr, SIZE, 0);
}
string recvString(SOCKET& s)
{
	recv(s, DataToRecv, SIZE, 0);
	string str = DataToRecv;
	return str;
}

int recvInt(SOCKET& s)
{
	strcpy_s(DataToRecv, "\0");
	recv(s, DataToRecv, SIZE, 0);
	int x = atoi(DataToRecv);
	return x;
}
void sendInt(SOCKET& s, int a)
{
	_itoa_s(a, DataToSend, 10);
	send(s, DataToSend, SIZE, 0);
}
void sendInt(SOCKET& s, Integer a)
{
	_itoa_s(a.core, DataToSend, 10);
	send(s, DataToSend, SIZE, 0);
}

void adminMenu(SOCKET& s)
{
	Menu menu;
	while (true)
	{
		switch (menu.CreateMenu("���� �������*���� ���������*�����*"))
		{
		case 1: workersMenu(s); break;
		case 2: accountsMenu(s); break;
		case 3: send(s, "Exit", SIZE, 0); return;
		}
	}
}
void userMenu(SOCKET& s)
{
	Menu menu;
	while (true)
	{
		switch (menu.CreateMenu("������ �������*����� �� �������*���� ����������*������� ������*�����*"))
		{
		case 1: workersList(s);  break;
		case 2: workersSearch(s); break;
		case 3: workersSort(s); break;
		case 4: accountsPassch(s); break;
		case 5: send(s, "Exit", SIZE, 0); return;
		}
	}
}

void accountsMenu(SOCKET& s)
{
	Menu menu;
	send(s, "AccMenu", SIZE, 0);
	while (true)
	{
		switch (menu.CreateMenu("������ �������������*�������� ������������*������� ������������*������� ������*������������� ����� ����*"))
		{
		case 1: accountsList(s); break;
		case 2: accountsAdd(s); break;
		case 3: accountsRem(s); break;
		case 4: accountsPassch(s);  break;
		case 5: accountsKeygen(s); break;
		case 0: send(s, "Exit", SIZE, 0); return;
		}
	}
}
void accountsList(SOCKET& s)
{
	send(s, "List", SIZE, 0);
	Table table;
	int size = recvInt(s);
	string usBuf;
	string pwBuf;
	string prBuf;
	vector<string> vec[30];
	for (int i = 0; i < size; i++)
	{
		usBuf = recvString(s);
		pwBuf = recvString(s);
		prBuf = recvString(s);
		vec[i].push_back(usBuf);
		vec[i].push_back(pwBuf);
		vec[i].push_back(prBuf);
	}
	table.CreateTable("Login*Pass*Permissions*", vec, size);
	vec->clear();
	_getch();
}
void accountsAdd(SOCKET& s)
{
	system("cls");
	Account accbuf;
	Menu menu;
	string buf;
	char bufch[50];
	int f = 0;
	if (account.getPermissions() == "user")
	{
		accbuf.setPermissions("user");
	}
	else if (account.getPermissions() == "admin" || account.getPermissions() == "adminp")
	{
		while (!f)
		{
			switch (menu.CreateMenu("�������� ��������������*�������� ��������*�������� ������������*"))
			{
			case 1: accbuf.setPermissions("admin"); f++; break;
			case 2: accbuf.setPermissions("expert"); f++; break;
			case 3: accbuf.setPermissions("user"); f++; break;
			case 0: return;
			}
		}
	}
	send(s, "Add", SIZE, 0);
	while (true)
	{
		accbuf.setUsername();
		sendString(s, accbuf.getUsername());
		recv(s, DataToRecv, SIZE, 0);
		if (!strcmp(DataToRecv, "OK"))
			break;
		else
			cout << "��� ������������ ��� ������, ��������� ����" << endl;
	}
	while (true)
	{
		passscan(DataToSend);
		cout << "��� ������������� ��������� ����" << endl;
		passscan(bufch);
		if (!strcmp(DataToSend, bufch))
			break;
		else
			cout << "������, ������ �� ���������" << endl;
	}
	accbuf.setPassword(bufch);
	sendString(s, accbuf.getPassword());
	sendString(s, accbuf.getPermissions());
	cout << "Added succesfully" << endl;
	_getch();
}
void accountsRem(SOCKET& s)
{
	send(s, "Rem", SIZE, 0);
	Table table;
	int size = recvInt(s);
	string usBuf;
	string pwBuf;
	string prBuf;
	vector<string> vec[30];
	for (int i = 0; i < size; i++)
	{
		usBuf = recvString(s);
		pwBuf = recvString(s);
		prBuf = recvString(s);
		vec[i].push_back(usBuf);
		vec[i].push_back(pwBuf);
		vec[i].push_back(prBuf);
	}
	int x = table.CreateTableMenu("Login*Pass*Permissions*", vec, size);
	vec->clear();
	if (!x)
	{
		return;
	}
	sendInt(s, x);
	cout << "Succesfull" << endl;
	_getch();
}
void accountsPassch(SOCKET& s)
{
	char pass1[50], pass2[50];
	send(s, "Pass", SIZE, 0);
	passscan(pass1, "������� ������� ������: ");
	if (pass1 != account.getPassword())
	{
		cout << "������ �� ���������" << endl;
		send(s, "Error", SIZE, 0);
		_getch();
		return;
	}
	passscan(pass1, "������� ����� ������: ");
	passscan(pass2, "������� ����� ������ ��� ���: ");
	if (!strcmp(pass1, pass2))
	{
		send(s, pass1, SIZE, 0);
		cout << "�������" << endl;
		_getch();
		return;
	}
	else
	{
		cout << "������ �� ���������" << endl;
		send(s, "Error", SIZE, 0);
		_getch();
		return;
	}
}
void accountsKeygen(SOCKET& s)
{
	send(s, "Key", SIZE, 0);
	cout << "New key generated" << endl;
	_getch();
}

void expertMenu(SOCKET& s)
{
	Menu menu;
	while (true)
	{
		switch (menu.CreateMenu("��������� �������*�������� �������*�����*"))
		{
		case 1: send(s, "ProfileFill", SIZE, 0); expertFill(s); break;
		case 2: send(s, "ProfileShow", SIZE, 0); expertShow(s); break;
		case 3: send(s, "Exit", SIZE, 0); return;
		}
	}
}
void expertShow(SOCKET& s)
{
	Table table;
	string buf;
	vector<string>* vec = new vector<string>;
	buf = recvString(s);
	vec->push_back(buf); // ID
	buf = recvString(s);
	vec->push_back(buf); // fam
	buf = recvString(s);
	vec->push_back(buf); // nam
	buf = recvString(s);
	vec->push_back(buf); // otc
	buf = to_string(recvInt(s));
	vec->push_back(buf); // dolj
	buf = to_string(recvInt(s));
	vec->push_back(buf); //step
	buf = to_string(recvInt(s));
	vec->push_back(buf); //zvan
	buf = to_string(recvInt(s));
	vec->push_back(buf); //naur
	buf = to_string(recvInt(s));
	vec->push_back(buf); //koef
	table.CreateTable("ID*�������*���*��������*���������*������ �������*������ ������*���-�� ������� �����*��������� ��������������*", vec, 1);
	_getch();
}
void expertFill(SOCKET& s)
{
	Menu menu;
	int x;
	string buf;
	cout << "������� ���� �������: ";
	cin >> buf;
	sendString(s, buf);
	cout << "������� ���� ���: ";
	cin >> buf;
	sendString(s, buf);
	cout << "������� ���� ��������: ";
	cin >> buf;
	sendString(s, buf);
	x = menu.CreateMenu("������� ������� � ����*������� ���������*������� ������� ��������� � ����*", "�������� ���� ���������");
	sendInt(s, x-1);
	x = menu.CreateMenu("�����������*�������� ����*������ ����*��������*", "�������� ���� ������ �������");
	sendInt(s, x-1);
	x = menu.CreateMenu("�����������*������� ������� ���������*������*���������*", "�������� ���� ������ ������");
	sendInt(s, x-1);
	x = menu.CreateMenu("0*1-2*3 � �����*", "�������� ���-�� ����� ������� �����");
	sendInt(s, x-1);
}

void Login(SOCKET& s)
{
	char passbuf[30];
	send(s, "Login", SIZE, 0);
	system("cls");
	account.setUsername();
	sendString(s, account.getUsername());
	passscan(passbuf);
	account.setPassword(passbuf);
	sendString(s, account.getPassword());
	recv(s, DataToRecv, SIZE, 0);
	if (!strcmp(DataToRecv, "0"))
	{
		cout << "�������� �����/������" << endl;
		_getch();
		return;
	}
	account.setPermissions(DataToRecv);
	cout << "�� ����� � ������� � ������� " << account.getPermissions();
	_getch();
	if (account.getPermissions() == "adminp" || account.getPermissions() == "admin")
	{
		adminMenu(s);
	}
	else if (account.getPermissions() == "expert")
	{
		expertMenu(s);
	}
	else if (account.getPermissions() == "user")
	{
		userMenu(s);
	}
}
void Register(SOCKET& s)
{
	char pwBuf1[30];
	send(s, "Register", SIZE, 0);
	cout << "��� ������������: ";
	cin >> DataToSend;
	send(s, DataToSend, SIZE, 0);
	while (true)
	{
		passscan(DataToSend);
		cout << "��� ������������� ��������� ����" << endl;
		passscan(pwBuf1);
		if (!strcmp(DataToSend, pwBuf1))
			break;
		else
			cout << "������, ������ �� ���������" << endl;
	}
	send(s, DataToSend, SIZE, 0);
	cout << "�������" << endl;
	_getch();
}
void Disconnect(SOCKET& s)
{
	send(s, "Exit", SIZE, 0);
	cout << "Disconnected from server" << endl;
	exit(0);
}

void workersMenu(SOCKET& s)
{
	Menu menu;
	send(s, "workersMenu", SIZE, 0);
	while (true)
	{
		switch (menu.CreateMenu("������*����������*��������*���������*����� ��������*���� ����������*������ ������� ����������*�������*"))
		{
		case 1: workersList(s); break;
		case 2: workersAdd(s); break;
		case 3: workersRem(s); break;
		case 4: workersEdit(s); break;
		case 5: workersSearch(s); break;
		case 6: workersSort(s); break;
		case 7: workersEstimate(s); break;
		case 8: workersRating(s); break;
		case 0: send(s, "Exit", SIZE, 0); return;
		}
	}
}
void workersList(SOCKET& s)
{
	system("cls");
	send(s, "List", SIZE, 0);
	int size = recvInt(s);
	try
	{
		if (!size)
		{
			throw logic_error("������ ������� ����");
		}
	}
	catch (logic_error err)
	{
		cerr << err.what();
		_getch();
		return;
	}
	Table table;
	string buf[8];
	vector<string> vec[30];
	for (int i = 0; i < size; i++)
	{
		buf[0] = recvString(s);
		buf[1] = recvString(s);
		buf[2] = recvString(s);
		buf[3] = recvString(s);
		buf[4] = recvString(s);
		buf[5] = recvString(s);
		buf[6] = recvString(s);
		buf[7] = recvString(s);
		vec[i].push_back(buf[0]);
		vec[i].push_back(buf[1]);
		vec[i].push_back(buf[2]);
		vec[i].push_back(buf[3]);
		vec[i].push_back(buf[4]);
		vec[i].push_back(buf[5]);
		vec[i].push_back(buf[6]);
		vec[i].push_back(buf[7]);
	}
	table.CreateTable("�������*���*��������*�������. ������*������*����*������*������ ���������*", vec, size);
	vec->clear();
	_getch();
}
void workersAdd(SOCKET& s)
{
	system("cls");
	send(s, "Add", SIZE, 0);
	Menu menu;
	string buf;
	Integer ix;
	cout << "������� ������� ��������" << endl;
	cin >> buf;
	sendString(s, buf);
	cout << "������� ��� ��������" << endl;
	cin >> buf;
	sendString(s, buf);
	cout << "������� �������� ��������" << endl;
	cin >> buf;
	sendString(s, buf);
	cout << "������� ���������� ������������� ������� � �������" << endl;
	cin >> ix;
	sendInt(s, ix);
	cout << "������� ���������� ����� �� ��������" << endl;
	cin >> ix;
	sendInt(s, ix);
	cout << "������� ���������� ������������ ������� �����" << endl;
	cin >> ix;
	sendInt(s, ix);
	cout << "������� ���-�� �������, ������� ������ �������" << endl;
	cin >> ix;
	sendInt(s, ix);
	cout << "�������" << endl;
	_getch();
}
void workersEdit(SOCKET& s)
{
	system("cls");
	send(s, "Edit", SIZE, 0);
	int size = recvInt(s);
	try
	{
		if (!size)
		{
			throw logic_error("������ ������� ����");
		}
	}
	catch (logic_error err)
	{
		cerr << err.what();
		_getch();
		return;
	}
	Table table;
	Menu menu;
	string buf[8];
	string bufsend;
	Integer integer;
	vector<string> vec[30];
	for (int i = 0; i < size; i++)
	{
		buf[0] = recvString(s);
		buf[1] = recvString(s);
		buf[2] = recvString(s);
		buf[3] = recvString(s);
		buf[4] = recvString(s);
		buf[5] = recvString(s);
		buf[6] = recvString(s);
		buf[7] = recvString(s);
		vec[i].push_back(buf[0]);
		vec[i].push_back(buf[1]);
		vec[i].push_back(buf[2]);
		vec[i].push_back(buf[3]);
		vec[i].push_back(buf[4]);
		vec[i].push_back(buf[5]);
		vec[i].push_back(buf[6]);
		vec[i].push_back(buf[7]);
	}
	int x = table.CreateTableMenu("�������*���*��������*�������. ������*������*����*������*������ ���������*", vec, size, "�������� �������������� ��������");
	vec->clear();
	if (!x)
	{
		return;
	}
	sendInt(s, x);
	x = menu.CreateMenu("�������*���*��������*�������. ������*������*����*������*", "�������� ������������� ��������");
	sendInt(s, x);
	switch (x)
	{
	case 1: cout << "������� ����� �������" << endl; cin >> bufsend; sendString(s, bufsend); break;
	case 2: cout << "������� ����� ���" << endl; cin >> bufsend; sendString(s, bufsend); break;
	case 3: cout << "������� ����� ��������" << endl; cin >> bufsend; sendString(s, bufsend); break;
	case 4: cout << "������� ����� ���-�� ������������� ������� " << endl; cin >> integer; sendInt(s, integer); break;
	case 5: cout << "������� ����� ���-�� �����" << endl; cin >> integer; sendInt(s, integer); break;
	case 6: cout << "������� ����� ���-�� ������������ �����" << endl; cin >> integer; sendInt(s, integer); break;
	case 7: cout << "������� ����� ���-�� �������" << endl; cin >> integer; sendInt(s, integer); break;
	case 0: return;
	}
	cout << "�������" << endl;
	_getch();
}
void workersSort(SOCKET& s)
{
	send(s, "Sort", SIZE, 0);
	Menu menu;
	int x = menu.CreateMenu("�������*���*��������*�������. ������*������*����*������*", "�������� �������� ����������");
	sendInt(s, x);
	int size = recvInt(s);
	try
	{
		if (!size)
		{
			throw logic_error("������ ������� ����");
		}
	}
	catch (logic_error err)
	{
		cerr << err.what();
		_getch();
		return;
	}
	system("cls");
	Table table;
	string buf[8];
	vector<string> vec[30];
	for (int i = 0; i < size; i++)
	{
		buf[0] = recvString(s);
		buf[1] = recvString(s);
		buf[2] = recvString(s);
		buf[3] = recvString(s);
		buf[4] = recvString(s);
		buf[5] = recvString(s);
		buf[6] = recvString(s);
		buf[7] = recvString(s);
		vec[i].push_back(buf[0]);
		vec[i].push_back(buf[1]);
		vec[i].push_back(buf[2]);
		vec[i].push_back(buf[3]);
		vec[i].push_back(buf[4]);
		vec[i].push_back(buf[5]);
		vec[i].push_back(buf[6]);
		vec[i].push_back(buf[7]);
	}
	table.CreateTable("�������*���*��������*�������. ������*������*����*������*������ ���������*", vec, size);
	vec->clear();
	_getch();
}
void workersSearch(SOCKET& s)
{
	system("cls");
	send(s, "Search", SIZE, 0);
	cout << "������� ������� �������� ��������" << endl;
	cin >> DataToSend;
	send(s, DataToSend, SIZE, 0);
	system("cls");
	if (recvString(s) == "Error")
	{
		cout << "�� �������" << endl;
		_getch();
		return;
	}
	Table table;
	string buf[8];
	vector<string> vec[1];
	buf[0] = recvString(s);
	buf[1] = recvString(s);
	buf[2] = recvString(s);
	buf[3] = recvString(s);
	buf[4] = recvString(s);
	buf[5] = recvString(s);
	buf[6] = recvString(s);
	buf[7] = recvString(s);
	vec[0].push_back(buf[0]);
	vec[0].push_back(buf[1]);
	vec[0].push_back(buf[2]);
	vec[0].push_back(buf[3]);
	vec[0].push_back(buf[4]);
	vec[0].push_back(buf[5]);
	vec[0].push_back(buf[6]);
	vec[0].push_back(buf[7]);
	table.CreateTable("�������*���*��������*�������. ������*������*����*������*������ ���������*", vec, 1);
	vec->clear();
	_getch();
}
void workersRem(SOCKET& s)
{
	system("cls");
	send(s, "Rem", SIZE, 0);
	int size = recvInt(s);
	try
	{
		if (!size)
		{
			throw logic_error("������ ������� ����");
		}
	}
	catch (logic_error err)
	{
		cerr << err.what();
		_getch();
		return;
	}
	Table table;
	string buf[8];
	vector<string> vec[30];
	for (int i = 0; i < size; i++)
	{
		buf[0] = recvString(s);
		buf[1] = recvString(s);
		buf[2] = recvString(s);
		buf[3] = recvString(s);
		buf[4] = recvString(s);
		buf[5] = recvString(s);
		buf[6] = recvString(s);
		buf[7] = recvString(s);
		vec[i].push_back(buf[0]);
		vec[i].push_back(buf[1]);
		vec[i].push_back(buf[2]);
		vec[i].push_back(buf[3]);
		vec[i].push_back(buf[4]);
		vec[i].push_back(buf[5]);
		vec[i].push_back(buf[6]);
		vec[i].push_back(buf[7]);
	}
	int x = table.CreateTableMenu("�������*���*��������*�������. ������*������*����*������*������ ���������*", vec, size);
	vec->clear();
	if (!x)
	{
		return;
	}
	sendInt(s, x);
	cout << "Succesfull" << endl;
	_getch();
}
void workersEstimate(SOCKET& s)
{
	send(s, "Estimate", SIZE, 0);
	int x = recvInt(s);
	int iBuf;
	Table table;
	Menu menu;
	vector<string> vec[20];
	string buf[8];
	string strf, strn, stro;
	while (true)
	{
		for (int i = 0; i < x; i++)
		{
			strf = recvString(s);
			strn = recvString(s);
			stro = recvString(s);
			vec[i].push_back(strf);
			vec[i].push_back(strn);
			vec[i].push_back(stro);
		}
		iBuf = table.CreateTableMenu("�������*���*��������*", vec, x, "�������� ���������, ������� ����� ��������� �������");
		for (int i = 0; i < x; i++)
		{
			vec[i].clear();
		}
		sendInt(s, iBuf);
		if (iBuf == 0)
		{
			break;
		}
		x--;
		if (x == 0)
		{
			break;
		}
	}
	vec->clear();
	x = recvInt(s);
	int expertsAmount = recvInt(s);
	string stringForCustomMsg;
	if (!x)
	{
		cout << "������ ������� ����" << endl;
		_getch();
		return;
	}
	for (int i = 0; i < x; i++)
	{
		buf[0] = recvString(s);
		buf[1] = recvString(s);
		buf[2] = recvString(s);
		buf[3] = recvString(s);
		buf[4] = recvString(s);
		buf[5] = recvString(s);
		buf[6] = recvString(s);
		buf[7] = recvString(s);
		vec[0].push_back(buf[0]);
		vec[0].push_back(buf[1]);
		vec[0].push_back(buf[2]);
		vec[0].push_back(buf[3]);
		vec[0].push_back(buf[4]);
		vec[0].push_back(buf[5]);
		vec[0].push_back(buf[6]);
		vec[0].push_back(buf[7]);
		system("cls");
		table.CreateTable("�������*���*��������*�������. ������*������*����*������*������ ���������*", vec, 1);
		vec[0].clear();
		_getch();
		system("cls");
		for (int j = 0; j < expertsAmount; j++)
		{
			stringForCustomMsg = "�������� ������ ������� ��������, ������� #"+ to_string(j+1);
			iBuf = menu.CreateMenu("0*1*2*3*4*5*6*7*8*9*10*", stringForCustomMsg);
			sendInt(s, iBuf);
		}
	}
}
void workersRating(SOCKET& s)
{
	send(s, "Rating", SIZE, 0);
	system("cls");
	cout << "������� ������� �� ��������� ������ ���������: " << endl;
	int x = recvInt(s);
	string buf;
	Table table;
	vector<string> vec[20];
	for (int i = 0; i < x; i++)
	{
		buf = recvString(s);
		vec[i].push_back(buf);
	}
	table.CreateTable("�������*", vec, x);
	_getch();
}