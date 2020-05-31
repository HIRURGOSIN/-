#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class Human
{
public:
	Human() {}
	~Human() {}
	string getName()
	{
		return name;
	}
	void setName(string _name)
	{
		name = _name;
	}
	string getSurname()
	{
		return surname;
	}
	void setSurname(string _surname)
	{
		surname = _surname;
	}
	string getPatronymic()
	{
		return patronymic;
	}
	void setPatronymic(string _patronymic)
	{
		patronymic = _patronymic;
	}
protected:
	string name;
	string surname;
	string patronymic;
};
class Worker : public Human
{
public:
	Worker() {}
	~Worker() {}
	void set(void* client_socket);
	void send(void* client_socket);
	void fscan(fstream& workers);
	void fprint(fstream& workers);
	bool operator==(const Worker& r) { return this->surname == r.surname; }
	void setCommends(int _commends)
	{
		commends = _commends;
	}
	int getCommends()
	{
		return commends;
	}
	void setReports(int _reports)
	{
		reports = _reports;
	}
	int getReports()
	{
		return reports;
	}
	void setHours(int _hours)
	{
		hours = _hours;
	}
	int getHours()
	{
		return hours;
	}
	void setDetails(int _details)
	{
		details = _details;
	}
	int getDetails()
	{
		return details;
	}
	void setMark(float _mark)
	{
		mark = _mark;
	}
	float getMark()
	{
		return mark;
	}
	
private:
	int commends = 0;
	int reports = 0;
	int hours = 0;
	int details = 0;
	float mark = 0;
};

void workersFscan();
void workersFprint();