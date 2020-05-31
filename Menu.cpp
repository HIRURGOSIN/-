#include "Menu.h"


using namespace std;
void Menu::Jump()
{
	if (highlighter > MenuBullet.size())
	{
		highlighter = 1;
	}
	if (highlighter < 1)
	{
		highlighter = MenuBullet.size();
	}
}
int Menu::CreateMenu(string str)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	string buf;
	MenuBullet.clear();
	highlighter = 1;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '*')
		{
			MenuBullet.push_back(buf);
			buf.erase();
			continue;
		}
		buf += str[i];
	}
	char x;
	while (true)
	{
		system("cls");
		for (int i = 0; i < MenuBullet.size(); i++)
		{
			cout << "\t\t\t\t\t\t";
			if (i == highlighter - 1)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((15 << 4 | 0)));
			}
			cout << MenuBullet[i] << endl;
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 15)));
		}
		x = _getch();
		if (x == 0 || x == 0xE0)
		{
			x = _getch();
		}
		switch (x)
		{
		case 72: highlighter--; Jump(); break;
		case 80: highlighter++; Jump(); break;
		case 77: return highlighter; break;
		case 75: return 0; break;
		}
	}
	return 0;
}
int Menu::CreateMenu(string str, string msg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	string buf;
	MenuBullet.clear();
	highlighter = 1;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '*')
		{
			MenuBullet.push_back(buf);
			buf.erase();
			continue;
		}
		buf += str[i];
	}
	char x;
	while (true)
	{
		system("cls");
		cout << msg << endl;
		for (int i = 0; i < MenuBullet.size(); i++)
		{
			cout << "\t\t\t\t\t\t";
			if (i == highlighter - 1)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((15 << 4 | 0)));
			}
			cout << MenuBullet[i] << endl;
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4 | 15)));
		}
		x = _getch();
		if (x == 0 || x == 0xE0)
		{
			x = _getch();
		}
		switch (x)
		{
		case 72: highlighter--; Jump(); break;
		case 80: highlighter++; Jump(); break;
		case 77: return highlighter; break;
		case 75: return 0; break;
		}
	}
	return 0;
}