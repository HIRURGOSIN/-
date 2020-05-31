#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include "classes.h"
using namespace std;

char DataToSend[100];
char DataToRecv[100];

void passscan(char password[])
{
	cout << "Введите пароль: ";
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
		cout << "Недопустимый пароль!" << endl;
		cout << "Повторите попытку:" << endl;
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
		cout << "Недопустимый пароль!" << endl;
		cout << "Повторите попытку:" << endl;
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
		switch (menu.CreateMenu("Меню рабочих*Меню аккаунтов*Выход*"))
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
		switch (menu.CreateMenu("Список рабочих*Поиск по фамилии*Меню сортировки*Сменить пароль*Выход*"))
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
		switch (menu.CreateMenu("Список пользователей*Добавить пользователя*Удалить пользователя*Сменить пароль*Сгенерировать новый ключ*"))
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
			switch (menu.CreateMenu("Добавить администратора*Добавить эксперта*Добавить пользователя*"))
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
			cout << "Имя пользователя уже занято, повторите ввод" << endl;
	}
	while (true)
	{
		passscan(DataToSend);
		cout << "Для подтверждения повторите ввод" << endl;
		passscan(bufch);
		if (!strcmp(DataToSend, bufch))
			break;
		else
			cout << "Ошибка, пароли не совпадают" << endl;
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
	passscan(pass1, "Введите текущий пароль: ");
	if (pass1 != account.getPassword())
	{
		cout << "Пароли не совпадают" << endl;
		send(s, "Error", SIZE, 0);
		_getch();
		return;
	}
	passscan(pass1, "Введите новый пароль: ");
	passscan(pass2, "Введите новый пароль еще раз: ");
	if (!strcmp(pass1, pass2))
	{
		send(s, pass1, SIZE, 0);
		cout << "Успешно" << endl;
		_getch();
		return;
	}
	else
	{
		cout << "Пароли не совпадают" << endl;
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
		switch (menu.CreateMenu("Заполнить профиль*Показать профиль*Выйти*"))
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
	table.CreateTable("ID*Фамилия*Имя*Отчество*Должность*Ученая степень*Ученое звание*Кол-во научных работ*Коэфицент компетентности*", vec, 1);
	_getch();
}
void expertFill(SOCKET& s)
{
	Menu menu;
	int x;
	string buf;
	cout << "Введите свою фамилию: ";
	cin >> buf;
	sendString(s, buf);
	cout << "Введите свое имя: ";
	cin >> buf;
	sendString(s, buf);
	cout << "Введите свое отчество: ";
	cin >> buf;
	sendString(s, buf);
	x = menu.CreateMenu("Ведущий инженер и ниже*Научный сотрудник*Главный научный сотрудник и выше*", "Выберите свою должность");
	sendInt(s, x-1);
	x = menu.CreateMenu("Отсутствует*Кандидат наук*Доктор наук*Академик*", "Выберите свою ученую степень");
	sendInt(s, x-1);
	x = menu.CreateMenu("Отсутствует*Младший научный сотрудник*Доцент*Профессор*", "Выберите свое ученое звание");
	sendInt(s, x-1);
	x = menu.CreateMenu("0*1-2*3 и более*", "Выберите кол-во своих научных работ");
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
		cout << "Неверный логин/пароль" << endl;
		_getch();
		return;
	}
	account.setPermissions(DataToRecv);
	cout << "Вы вошли в систему с правами " << account.getPermissions();
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
	cout << "Имя пользователя: ";
	cin >> DataToSend;
	send(s, DataToSend, SIZE, 0);
	while (true)
	{
		passscan(DataToSend);
		cout << "Для подтверждения повторите ввод" << endl;
		passscan(pwBuf1);
		if (!strcmp(DataToSend, pwBuf1))
			break;
		else
			cout << "Ошибка, пароли не совпадают" << endl;
	}
	send(s, DataToSend, SIZE, 0);
	cout << "Успешно" << endl;
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
		switch (menu.CreateMenu("Список*Добавление*Удаление*Изменение*Найти рабочего*Меню сортировки*Начать процесс оценивания*Рейтинг*"))
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
			throw logic_error("Список рабочих пуст");
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
	table.CreateTable("Фамилия*Имя*Отчество*Положит. отзывы*Жалобы*Часы*Детали*Оценка экспертов*", vec, size);
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
	cout << "Введите фамилию рабочего" << endl;
	cin >> buf;
	sendString(s, buf);
	cout << "Введите имя рабочего" << endl;
	cin >> buf;
	sendString(s, buf);
	cout << "Введите отчество рабочего" << endl;
	cin >> buf;
	sendString(s, buf);
	cout << "Введите количество положительных отзывов о рабочем" << endl;
	cin >> ix;
	sendInt(s, ix);
	cout << "Введите количество жалоб на рабочего" << endl;
	cin >> ix;
	sendInt(s, ix);
	cout << "Введите количество отработанных рабочим часов" << endl;
	cin >> ix;
	sendInt(s, ix);
	cout << "Введите кол-во деталей, которые сделал рабочий" << endl;
	cin >> ix;
	sendInt(s, ix);
	cout << "Успешно" << endl;
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
			throw logic_error("Список рабочих пуст");
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
	int x = table.CreateTableMenu("Фамилия*Имя*Отчество*Положит. отзывы*Жалобы*Часы*Детали*Оценка экспертов*", vec, size, "Выберите редактируемого рабочего");
	vec->clear();
	if (!x)
	{
		return;
	}
	sendInt(s, x);
	x = menu.CreateMenu("Фамилия*Имя*Отчество*Положит. отзывы*Жалобы*Часы*Детали*", "Выберите редактируемый параметр");
	sendInt(s, x);
	switch (x)
	{
	case 1: cout << "Введите новую фамилию" << endl; cin >> bufsend; sendString(s, bufsend); break;
	case 2: cout << "Введите новое имя" << endl; cin >> bufsend; sendString(s, bufsend); break;
	case 3: cout << "Введите новое отчество" << endl; cin >> bufsend; sendString(s, bufsend); break;
	case 4: cout << "Введите новое кол-во положительных отзывов " << endl; cin >> integer; sendInt(s, integer); break;
	case 5: cout << "Введите новое кол-во жалоб" << endl; cin >> integer; sendInt(s, integer); break;
	case 6: cout << "Введите новое кол-во отработанных часов" << endl; cin >> integer; sendInt(s, integer); break;
	case 7: cout << "Введите новое кол-во деталей" << endl; cin >> integer; sendInt(s, integer); break;
	case 0: return;
	}
	cout << "Успешно" << endl;
	_getch();
}
void workersSort(SOCKET& s)
{
	send(s, "Sort", SIZE, 0);
	Menu menu;
	int x = menu.CreateMenu("Фамилия*Имя*Отчество*Положит. отзывы*Жалобы*Часы*Детали*", "Выберите параметр сортировки");
	sendInt(s, x);
	int size = recvInt(s);
	try
	{
		if (!size)
		{
			throw logic_error("Список рабочих пуст");
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
	table.CreateTable("Фамилия*Имя*Отчество*Положит. отзывы*Жалобы*Часы*Детали*Оценка экспертов*", vec, size);
	vec->clear();
	_getch();
}
void workersSearch(SOCKET& s)
{
	system("cls");
	send(s, "Search", SIZE, 0);
	cout << "Введите фамилию искомого рабочего" << endl;
	cin >> DataToSend;
	send(s, DataToSend, SIZE, 0);
	system("cls");
	if (recvString(s) == "Error")
	{
		cout << "Не найдено" << endl;
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
	table.CreateTable("Фамилия*Имя*Отчество*Положит. отзывы*Жалобы*Часы*Детали*Оценка экспертов*", vec, 1);
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
			throw logic_error("Список рабочих пуст");
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
	int x = table.CreateTableMenu("Фамилия*Имя*Отчество*Положит. отзывы*Жалобы*Часы*Детали*Оценка экспертов*", vec, size);
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
		iBuf = table.CreateTableMenu("Фамилия*Имя*Отчество*", vec, x, "Выберите экспертов, которые будут оценивать рабочих");
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
		cout << "Список рабочих пуст" << endl;
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
		table.CreateTable("Фамилия*Имя*Отчество*Положит. отзывы*Жалобы*Часы*Детали*Оценка экспертов*", vec, 1);
		vec[0].clear();
		_getch();
		system("cls");
		for (int j = 0; j < expertsAmount; j++)
		{
			stringForCustomMsg = "Выберите оценку данному рабочему, эксперт #"+ to_string(j+1);
			iBuf = menu.CreateMenu("0*1*2*3*4*5*6*7*8*9*10*", stringForCustomMsg);
			sendInt(s, iBuf);
		}
	}
}
void workersRating(SOCKET& s)
{
	send(s, "Rating", SIZE, 0);
	system("cls");
	cout << "Рейтинг рабочих на основании мнений экспертов: " << endl;
	int x = recvInt(s);
	string buf;
	Table table;
	vector<string> vec[20];
	for (int i = 0; i < x; i++)
	{
		buf = recvString(s);
		vec[i].push_back(buf);
	}
	table.CreateTable("Рабочий*", vec, x);
	_getch();
}