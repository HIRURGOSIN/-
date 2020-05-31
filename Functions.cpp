#include "classes.h"

using namespace std;

char DataToSend[100];
char DataToRecv[100];

void sendString(void* client_socket, string str)
{
	const char* cStr;
	cStr = str.c_str();
	send((SOCKET)client_socket, cStr, SIZE, 0);
}
string recvString(void* client_socket)
{
	recv((SOCKET)client_socket, DataToRecv, SIZE, 0);
	string str = DataToRecv;
	return str;
}

void sendInt(void* client_socket, int a)
{
	_itoa_s(a, DataToSend, 10);
	send((SOCKET)client_socket, DataToSend, SIZE, 0);
}
int recvInt(void* client_socket)
{
	recv((SOCKET)client_socket, DataToRecv, SIZE, 0);
	return atoi(DataToRecv);
}

void sendFloat(void* client_socket, float a)
{
	sprintf_s(DataToSend, "%f", a);
	send((SOCKET)client_socket, DataToSend, SIZE, 0);
}

void workersFscan()
{
	fstream workers;
	Worker workerbuf;
	worker.clear();
	workers.open("workers.txt", ios::in);
	while (!workers.eof())
	{
		workerbuf.fscan(workers);
		worker.push_back(workerbuf);
	}
	workers.close();
}
void workersFprint()
{
	fstream workers;
	workers.open("workers.txt", ios::out | ios::trunc);
	for (int i = 0; i < worker.size(); i++)
	{
		worker[i].fprint(workers);
		if (i != worker.size() - 1)
		{
			workers << endl;
		}
	}
	workers.close();
}

int login(void* client_socket, Account& account)
{
	recv((SOCKET)client_socket, DataToRecv, SIZE, 0); account.UsernameSet(DataToRecv);
	recv((SOCKET)client_socket, DataToRecv, SIZE, 0); account.PasswordSet(DataToRecv);
	account.fscan();
	if (account.login() != "0")
	{
		cout << account.UsernameGet() << " logged in" << endl;
		sendString(client_socket, account.login());
	}
	else
	{
		cout << "Someone tried to login and failed" << endl;
		sendString(client_socket, "0");
		return 0;
	}
	if (account.PermissionsGet() == "adminp" || account.PermissionsGet() == "admin")
	{
		return 1;
	}
	if (account.PermissionsGet() == "expert")
	{
		return 2;
	}
	if (account.PermissionsGet() == "user")
	{
		return 3;
	}
	return -1;
}
void reg(void* client_socket, Account& account)
{
	User userbuf;
	recv((SOCKET)client_socket, DataToRecv, SIZE, 0);
	userbuf.usernameSet(DataToRecv);
	recv((SOCKET)client_socket, DataToRecv, SIZE, 0);
	userbuf.passwordSet(DataToRecv);
	userbuf.permissionsSet("user");
	account.fscan();
	account.user.push_back(userbuf);
	account.fprint();
	cout << userbuf.usernameGet() << " just registered" << endl;
}
void MainMenu(void* client_socket)
{
	Account account;
	int x;
	while (true)
	{
		recv((SOCKET)client_socket, DataToRecv, SIZE, 0);
		if (!strcmp(DataToRecv, "Login"))
		{
			x = login(client_socket, account);
			if (x == 1)
			{
				adminMenu(client_socket, account);
			}
			else if (x == 2)
			{
				expertMenu(client_socket, account);
			}
			else if (x == 3)
			{
				userMenu(client_socket, account);
			}
		}
		else if (!strcmp(DataToRecv, "Register"))
		{
			reg(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Exit"))
		{
			break;
		}
	}
}

void adminMenu(void* client_socket, Account& account)
{
	while (true)
	{
		recv((SOCKET)client_socket, DataToRecv, SIZE, 0);
		if (!strcmp(DataToRecv, "workersMenu"))
		{
			workersMenu(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "AccMenu"))
		{
			accountsMenu(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Exit"))
		{
			break;
		}
	}
}
void userMenu(void* client_socket, Account& account)
{
	while (true)
	{
		recv((SOCKET)client_socket, DataToRecv, SIZE, 0);
		if (!strcmp(DataToRecv, "List"))
		{
			workersList(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Search"))
		{
			workersSearch(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Sort"))
		{
			workersSort(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Pass"))
		{
			accountsPassch(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Exit"))
		{
			break;
		}
	}
}
void expertMenu(void* client_socket, Account& account)
{
	while (true)
	{
		recv((SOCKET)client_socket, DataToRecv, SIZE, 0);
		if (!strcmp(DataToRecv, "ProfileFill"))
		{
			cout << account.UsernameGet() << " запросил заполнение своего профиля" << endl;
			account.fscan();
			for (int i = 0; i < account.expert.size(); i++)
			{
				if (account.UsernameGet() == account.expert[i].getId())
				{
					account.expert[i].FillProfile(client_socket);
				}
			}
			account.fprint();
		}
		else if (!strcmp(DataToRecv, "ProfileShow"))
		{
			cout << account.UsernameGet() << " запросил отправку своего профиля" << endl;
			account.fscan();
			for (int i = 0; i < account.expert.size(); i++)
			{
				if (account.UsernameGet() == account.expert[i].getId())
				{
					account.expert[i].SendProfile(client_socket);
				}
			}
		}
		else if (!strcmp(DataToRecv, "Exit"))
		{
			break;
		}
	}
}

void accountsMenu(void* client_socket, Account& account)
{
	while (true)
	{
		recv((SOCKET)client_socket, DataToRecv, SIZE, 0);
		if (!strcmp(DataToRecv, "List"))
		{
			accountsList(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Add"))
		{
			accountsAdd(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Rem"))
		{
			accountsRem(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Pass"))
		{
			accountsPassch(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Key"))
		{
			accountsKeygen(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Exit"))
		{
			break;
		}
	}
}
void accountsList(void* client_socket, Account& account)
{
	cout << account.UsernameGet() << " запросил список пользователей" << endl;
	account.fscan();
	sendInt(client_socket, account.getAmountOfUsers());
	for (int i = 0; i < account.getAmountOfUsers(); i++)
	{
		sendString(client_socket, account.user[i].usernameGet());
		sendString(client_socket, account.user[i].passwordSend(account.PermissionsGet()));
		sendString(client_socket, account.user[i].permissionsGet());
	}
}
void accountsAdd(void* client_socket, Account& account)
{
	cout << account.UsernameGet() << " запросил добавление пользователя" << endl;
	User userbuf;
	int f;
	account.fscan();
	while (true)
	{
		f = 0;
		userbuf.usernameSet(recvString(client_socket));
		for (int i = 0; i < account.user.size(); i++)
		{
			if (userbuf.usernameGet() == account.user[i].usernameGet())
			{
				f++;
			}
		}
		if (!f)
		{
			send((SOCKET)client_socket, "OK", SIZE, 0);
			break;
		}
		cout << account.UsernameGet() << " попытался добавить существующий логин пользователя, ожидается новый" << endl;
		send((SOCKET)client_socket, "ERR", SIZE, 0);
	}
	userbuf.passwordSet(recvString(client_socket));
	userbuf.permissionsSet(recvString(client_socket));
	account.user.push_back(userbuf);
	account.fprint();
	cout << account.UsernameGet() << " добавил пользователя " << userbuf.usernameGet() << endl;
}
void accountsRem(void* client_socket, Account& account)
{
	cout << account.UsernameGet() << " запросил удаление пользователя" << endl;
	account.fscan();
	sendInt(client_socket, account.getAmountOfUsers());
	for (int i = 0; i < account.getAmountOfUsers(); i++)
	{
		sendString(client_socket, account.user[i].usernameGet());
		sendString(client_socket, account.user[i].passwordSend(account.PermissionsGet()));
		sendString(client_socket, account.user[i].permissionsGet());
	}
	int x = recvInt(client_socket) - 1;
	if (x == -1)
	{
		cout << "Удаление пользователя отменено" << endl;
		return;
	}
	int Ex = -1;
	if (account.user[x].permissionsGet() == "expert")
	{
		for (int i = 0; i < account.expert.size(); i++)
		{
			if (account.expert[i].getId() == account.user[x].usernameGet())
			{
				Ex = i;
			}
		}
	}
	if (Ex != -1)
	{
		account.expert.erase(account.expert.begin() + Ex);
	}
	cout << account.UsernameGet() << " удалил пользователя " << account.user[x].usernameGet() << endl;
	account.user.erase(account.user.begin() + x);
	account.fprint();
}
void accountsPassch(void* client_socket, Account& account)
{
	cout << account.UsernameGet() << " запросил изменение своего пароля" << endl;
	recv((SOCKET)client_socket, DataToRecv, SIZE, 0);
	if (!strcmp(DataToRecv, "Error"))
	{
		cout << "Ошибка ввода пароля пользователем" << account.UsernameGet() << endl;
		return;
	}
	account.fscan();
	for (int i = 0; i < account.user.size(); i++)
	{
		if (account.user[i].usernameGet() == account.UsernameGet())
		{
			account.user[i].passwordSet(DataToRecv);
			account.PasswordSet(DataToRecv);
		}
	}
	cout << account.UsernameGet() << " изменил свой пароль" << endl;
	account.fprint();
}
void accountsKeygen(void* client_socket, Account& account)
{
	cout << account.UsernameGet() << " запросил изменение ключа шифрования" << endl;
	account.fscan();
	int newkey;
	random_device rd;
	default_random_engine generator(rd());
	uniform_int_distribution<int> distribution(1, 30);
	newkey = distribution(generator);
	fstream acc;
	acc.open("acc.txt", ios::out | ios::trunc);
	acc.seekp(0, ios::beg);
	acc << newkey;
	for (int i = 0; i < account.user.size(); i++)
	{
		account.user[i].encode(newkey);
		account.user[i].fprint(acc);
		account.user[i].decode(newkey);
	}
	acc.close();
	account.fscan();
	cout << "Новый ключ сгенерирован!" << endl;
	return;
}

void workersMenu(void* client_socket, Account& account)
{
	while (true)
	{
		recv((SOCKET)client_socket, DataToRecv, SIZE, 0);
		if (!strcmp(DataToRecv, "List"))
		{
			workersList(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Add"))
		{
			workersAdd(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Rem"))
		{
			workersRem(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Edit"))
		{
			workersEdit(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Sort"))
		{
			workersSort(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Search"))
		{
			workersSearch(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Estimate"))
		{
			workersEstimate(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Rating"))
		{
			workersRating(client_socket, account);
		}
		else if (!strcmp(DataToRecv, "Exit"))
		{
			break;
		}
	}
}
void workersList(void* client_socket, Account& account)
{
	cout << account.UsernameGet() << " запросил список работников" << endl;
	workersFscan();
	sendInt(client_socket, worker.size());
	for (int i = 0; i < worker.size(); i++)
	{
		worker[i].send(client_socket);
	}
}
void workersAdd(void* client_socket, Account& account)
{
	cout << account.UsernameGet() << " запросил добавление работника" << endl;
	workersFscan();
	Worker workerbuf;
	workerbuf.set(client_socket);
	worker.push_back(workerbuf);
	workersFprint();
}
void workersRem(void* client_socket, Account& account)
{
	cout << account.UsernameGet() << " запросил удаление работника" << endl;
	workersFscan();
	sendInt(client_socket, worker.size());
	for (int i = 0; i < worker.size(); i++)
	{
		worker[i].send(client_socket);
	}
	int x = recvInt(client_socket) - 1;
	if (x == -1)
	{
		cout << "Удаление работника отменено" << endl;
	}
	cout << account.UsernameGet() << " удалил работника " << worker[x].getName() << endl;
	worker.erase(worker.begin() + x);
	workersFprint();
}
void workersEdit(void* client_socket, Account& account)
{
	cout << account.UsernameGet() << " запросил меню редактирования" << endl;
	workersFscan();
	sendInt(client_socket, worker.size());
	for (int i = 0; i < worker.size(); i++)
	{
		worker[i].send(client_socket);
	}
	int x = recvInt(client_socket) - 1;
	if (x == -1)
	{
		cout << "Редактирование работника отменено" << endl;
	}
	int parameter = recvInt(client_socket);
	switch (parameter)
	{
	case 1: worker[x].setSurname(recvString(client_socket)); break;
	case 2: worker[x].setName(recvString(client_socket)); break;
	case 3: worker[x].setPatronymic(recvString(client_socket)); break;
	case 4: worker[x].setCommends(recvInt(client_socket)); break;
	case 5: worker[x].setReports(recvInt(client_socket)); break;
	case 6: worker[x].setHours(recvInt(client_socket)); break;
	case 7: worker[x].setDetails(recvInt(client_socket)); break;
	case 0: cout << "Редактирование работника отменено" << endl; return;
	}
	workersFprint();
}
void workersSort(void* client_socket, Account& account)
{
	cout << account.UsernameGet() << " запросил меню сортировки" << endl;
	workersFscan();
	int x = recvInt(client_socket);
	switch (x)
	{
	case 1:
	{
		sort(worker.begin(), worker.end(), surnameCmp);
		sendInt(client_socket, worker.size());
		for (int i = 0; i < worker.size(); i++)
		{
			worker[i].send(client_socket);
		}
	} break;
	case 2:
	{
		sort(worker.begin(), worker.end(), nameCmp);
		sendInt(client_socket, worker.size());
		for (int i = 0; i < worker.size(); i++)
		{
			worker[i].send(client_socket);
		}
	} break;
	case 3:
	{
		sort(worker.begin(), worker.end(), patronymicCmp);
		sendInt(client_socket, worker.size());
		for (int i = 0; i < worker.size(); i++)
		{
			worker[i].send(client_socket);
		}
	} break;
	case 4:
	{
		sort(worker.begin(), worker.end(), commendsCmp);
		sendInt(client_socket, worker.size());
		for (int i = 0; i < worker.size(); i++)
		{
			worker[i].send(client_socket);
		}
	} break;

	case 5:
	{
		sort(worker.begin(), worker.end(), reportsCmp);
		sendInt(client_socket, worker.size());
		for (int i = 0; i < worker.size(); i++)
		{
			worker[i].send(client_socket);
		}
	} break;

	case 6:
	{
		sort(worker.begin(), worker.end(), hoursCmp);
		sendInt(client_socket, worker.size());
		for (int i = 0; i < worker.size(); i++)
		{
			worker[i].send(client_socket);
		}
	} break;

	case 7:
	{
		sort(worker.begin(), worker.end(), detailsCmp);
		sendInt(client_socket, worker.size());
		for (int i = 0; i < worker.size(); i++)
		{
			worker[i].send(client_socket);
		}
	} break;

	case 0: return;
	}
}
void workersSearch(void* client_socket, Account& account)
{
	cout << account.UsernameGet() << " запросил поиск работника" << endl;
	workersFscan();
	string buf = recvString(client_socket);
	Worker workerbuf;
	workerbuf.setSurname(buf);
	auto it = find(worker.begin(), worker.end(), workerbuf);
	if (it != worker.end())
	{
		sendString(client_socket, "OK");
		worker[distance(worker.begin(), it)].send(client_socket);
	}
	else
		sendString(client_socket, "Error");
}
void workersEstimate(void* client_socket, Account& account)
{
	cout << account.UsernameGet() << " начал процесс оценивания" << endl;
	int x;
	account.fscan();
	vector<Expert> bufvec = account.expert;
	vector<Expert> activeExp;
	sendInt(client_socket, account.expert.size());
	while (bufvec.size())
	{
		for (int i = 0; i < bufvec.size(); i++)
		{
			sendString(client_socket, bufvec[i].getSurname());
			sendString(client_socket, bufvec[i].getName());
			sendString(client_socket, bufvec[i].getPatronymic());
		}
		x = recvInt(client_socket) -1;
		if (x == -1)
		{
			break;
		}
		activeExp.push_back(bufvec[x]);
		bufvec.erase(bufvec.begin() + x);
	}
	workersFscan();
	sendInt(client_socket, worker.size());
	sendInt(client_socket, activeExp.size());
	float sum=0;
	float koef, FinalMark =0;
	for (int i = 0; i < activeExp.size(); i++)
	{
		sum += activeExp[i].getKoef();
	}
	for (int i = 0; i < worker.size(); i++)
	{
		worker[i].send(client_socket);
		for (int j = 0; j < activeExp.size(); j++)
		{
			x = recvInt(client_socket)-1;
			koef = activeExp[j].getKoef() / sum;
			FinalMark+=x*koef;
		}
		worker[i].setMark(FinalMark);
		FinalMark = 0;
	}
	workersFprint();
}
void workersRating(void* client_socket, Account& account)
{
	workersFscan();
	cout << account.UsernameGet() << " запросил рейтинг работников" << endl;
	sort(worker.begin(), worker.end(), markCmp);
	sendInt(client_socket, worker.size());
	for (int i = 0; i < worker.size(); i++)
	{
		sendString(client_socket, worker[i].getName());
	}
}

int surnameCmp(Worker& l, Worker& r)
{
	return l.getSurname() > r.getSurname();
}
int nameCmp(Worker& l, Worker& r)
{
	return l.getName() > r.getName();
}
int patronymicCmp (Worker& l, Worker& r)
{
	return l.getPatronymic() > r.getPatronymic();
}
int commendsCmp(Worker& l, Worker& r)
{
	return l.getCommends() > r.getCommends();
}
int reportsCmp(Worker& l, Worker& r)
{
	return l.getReports() > r.getReports();
}
int hoursCmp(Worker& l, Worker& r)
{
	return l.getHours() > r.getHours();
}
int detailsCmp(Worker& l, Worker& r)
{
	return l.getDetails() > r.getDetails();
}
int markCmp(Worker& l, Worker& r)
{
	return l.getMark() > r.getMark();
}