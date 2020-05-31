#pragma once
#include <iostream>

using namespace std;
class Expert
{
public:
	Expert() {}
	~Expert() {}
	void FillProfile(void* client_socket);
	void SendProfile(void* client_socket);
	void set(string str);
	void fscan(fstream& exp);
	void fprint(fstream& exp);
	string getId()
	{
		return id;
	}
	string getName()
	{
		return name;
	}
	string getSurname()
	{
		return surname;
	}
	string getPatronymic()
	{
		return patronymic;
	}
	float getKoef()
	{
		return (float)expertiseK;
	}
private:
	string id;
	string surname = "NotSetYet";
	string name = "NoTseTyeT";
	string patronymic = "NoTSeTYet";
	struct Expertise
	{
		int post = 0;
		int grade = 0;
		int rank = 0;
		int treatise = 0;
	} expertise;
	int expertiseK = 0;
};