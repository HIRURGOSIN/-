#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

class Integer
{
public:
	int core;
public:
	friend ostream& operator<<(ostream& out, const Integer& num)
	{
		out << num.core;
		return out;
	}
	friend istream& operator>>(istream& in, Integer& num)
	{
		char str[30];
		char buf;
		int i = 0;
		for (i = 0; i < 10; i++)
		{
			buf = _getch();
			if (buf == '\b' && i != 0)
			{
				cout << "\b \b";
				str[i - 1] = '\0';
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
			else if (buf > 47 && buf < 58)
			{
				str[i] = buf;
				str[i + 1] = '\0';
				cout << buf;
			}
			else
			{
				i--;
				continue;
			}
		}
		cout << endl;
		num.core = atoi(str);
		return in;
	}
	friend fstream& operator>>(fstream& in, Integer& num)
	{
		in >> num.core;
		return in;
	}
	friend fstream& operator<<(fstream& out, Integer& num)
	{
		out << num.core;
		return out;
	}
	friend const Integer operator++(Integer& I, int);
	friend const Integer operator--(Integer& I, int);
	friend const Integer operator+(const Integer& l, int val);
	friend const Integer operator+(const Integer& l, const Integer& r);
	friend const Integer operator-(const Integer& l, int val);
	friend const Integer operator*(const Integer& l, int val);
	friend bool operator==(const Integer& l, int val);
	friend bool operator==(const Integer& l, const Integer& r);
	friend bool operator>(const Integer& l, int val);
	friend bool operator<(const Integer& l, int val);
	friend bool operator<=(const Integer& l, int val);
	friend bool operator<=(const Integer& l, const Integer& r);
	friend bool operator>=(const Integer& l, int val);
	friend bool operator>=(const Integer& l, const Integer& r);
	Integer& operator=(int val);
	Integer& operator=(char* str);
	Integer();
	~Integer();
};