#include "Table.h"
int Table::FindSizeOfCol(int COLUMN)
{
	string max = Info[COLUMN][0];
	for (int i = 1; i < Info[COLUMN].size(); i++)
	{
		if (max.length() < Info[COLUMN][i].length())
			max = Info[COLUMN][i];
	}
	return max.length();
}
int Table::FindMaxBullet()
{
	string max = TableBullet[0];
	for (int i = 1; i < TableBullet.size(); i++)
	{
		if (max.length() < TableBullet[i].length())
			max = TableBullet[i];
	}
	return max.length();
}
int Table::WidthByBiggest()
{
	int maxBullet = 0;
	int maxBuf = 0;
	vector<int> maxofStr;
	int sum;
	for (int i = 0; i < TableBullet.size(); i++)
	{
		if (TableBullet[i].size() > maxBullet)
			maxBullet = TableBullet[i].size();
	}
	for (int i = 0; i < amountOfVectors; i++)
	{
		for (int j = 0; j < TableBullet.size(); j++)
		{
			if (Info[i][j].size() > maxBuf)
				maxBuf = Info[i][j].size();
		}
		maxofStr.push_back(maxBuf);
		maxBuf = 0;
	}
	sum = maxBullet;
	for (int i = 0; i < maxofStr.size(); i++)
	{
		sum += maxofStr[i];
	}
	return sum + (amountOfVectors)*2 + 6;
}
void Table::FillBullet(string STR)
{
	string buf;
	TableBullet.clear();
	for (int i = 0; i < STR.length(); i++)
	{
		if (STR[i] == '*')
		{
			TableBullet.push_back(buf);
			buf.erase();
			continue;
		}
		buf += STR[i];
	}
}
void Table::Line(char symb)
{
	for (int i = 0; i < WidthByBiggest(); i++)
	{
		cout << symb;
	}
	cout << endl;
}
void Table::CreateTable(string STR, vector<string>* VEC, int amount)
{
	amountOfVectors = amount;
	Info = VEC;
	FillBullet(STR);
	Line('=');
	for (int i = 0; i < TableBullet.size(); i++)
	{
		cout << setiosflags(ios::left) << "|| " << setw(FindMaxBullet() + 1) << TableBullet[i];
		for (int j = 0; j < amountOfVectors; j++)
		{
			cout << setiosflags(ios::left) << "|" << setw(FindSizeOfCol(j) + 1) << Info[j][i];
		}
		cout << "||";
		cout << endl;
		if (i < TableBullet.size() - 1)
			Line('-');
		else
			Line('=');
	}
}
int Table::CreateTableMenu(string STR, vector<string>* VEC, int amount)
{
	amountOfVectors = amount;
	Info = VEC;
	FillBullet(STR);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int highlighter = 1;
	char x;
	while (true)
	{
		system("cls");
		Line('=');
		for (int i = 0; i < TableBullet.size(); i++)
		{
			cout << setiosflags(ios::left) << "|| " << setw(FindMaxBullet() + 1) << TableBullet[i];
			for (int j = 0; j < amountOfVectors; j++)
			{
				if (j == highlighter - 1)
					SetConsoleTextAttribute(hConsole, (WORD)((15 << 4 | 0)));
					cout << setiosflags(ios::left) << "|" << setw(FindSizeOfCol(j) + 1) << Info[j][i];
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 15)));
			}
			cout << "||";
			cout << endl;
			if (i < TableBullet.size() - 1)
				Line('-');
			else
				Line('=');
		}
		x = _getch();
		if (x == 0 || x == 0xE0)
		{
			x = _getch();
		}
		switch (x)
		{
		case 72: highlighter--; if (highlighter < 1) highlighter = amountOfVectors; break;
		case 80: highlighter++; if (highlighter > amountOfVectors) highlighter = 1; break;
		case 77: return highlighter; break;
		case 75: return 0; break;
		}
	}
}
int Table::CreateTableMenu(string STR, vector<string>* VEC, int amount, string custommsg)
{
	amountOfVectors = amount;
	Info = VEC;
	FillBullet(STR);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int highlighter = 1;
	char x;
	while (true)
	{
		system("cls");
		cout << custommsg << endl;
		Line('=');
		for (int i = 0; i < TableBullet.size(); i++)
		{
			cout << setiosflags(ios::left) << "|| " << setw(FindMaxBullet() + 1) << TableBullet[i];
			for (int j = 0; j < amountOfVectors; j++)
			{
				if (j == highlighter - 1)
					SetConsoleTextAttribute(hConsole, (WORD)((15 << 4 | 0)));
				cout << setiosflags(ios::left) << "|" << setw(FindSizeOfCol(j) + 1) << Info[j][i];
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 15)));
			}
			cout << "||";
			cout << endl;
			if (i < TableBullet.size() - 1)
				Line('-');
			else
				Line('=');
		}
		x = _getch();
		if (x == 0 || x == 0xE0)
		{
			x = _getch();
		}
		switch (x)
		{
		case 72: highlighter--; if (highlighter < 1) highlighter = amountOfVectors; break;
		case 80: highlighter++; if (highlighter > amountOfVectors) highlighter = 1; break;
		case 77: return highlighter; break;
		case 75: return 0; break;
		}
	}
}