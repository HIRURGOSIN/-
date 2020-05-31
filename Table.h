#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
using namespace std;
class Table
{
public:
	Table() {}
	~Table() {}
	void CreateTable(string str, vector<string>* vec, int amount);
	int CreateTableMenu(string str, vector<string>* vec, int amount);
	int CreateTableMenu(string str, vector<string>* vec, int amount, string custommsg);
	void Line(char);
	void FillBullet(string STR);
	int WidthByBiggest();
	int FindMaxBullet();
	int FindSizeOfCol(int);
private:
	int n = 0;
	int m = 0;
	vector<string> TableBullet;
	vector<string>* Info = nullptr;
	vector<int> sizeOfCol;
	int maxInfo = 0;
	int amountOfVectors = 0;
};