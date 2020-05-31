#pragma once
#include "Integer.h"
using namespace std;
Integer::Integer()
{
	core = 0;
}
Integer::~Integer()
{
	core = 0;
}
Integer& Integer::operator=(int val)
{
	core = val;
	return *this;
}
Integer& Integer::operator=(char* str)
{
	core = atoi(str);
	return *this;
}
const Integer operator++(Integer& num, int)
{
	num.core++;
	return num;
}
const Integer operator--(Integer& num, int)
{
	num.core--;
	return num;
}
const Integer operator+(const Integer& l, int val)
{
	Integer ret;
	ret.core = l.core + val;
	return ret;
}
const Integer operator+(const Integer& l, const Integer& r)
{
	Integer ret;
	ret.core = l.core + r.core;
	return ret;
}
const Integer operator-(const Integer& l, int val)
{
	Integer ret;
	ret.core = l.core - val;
	return ret;
}
const Integer operator*(const Integer& l, int val)
{
	Integer ret;
	ret.core = l.core * val;
	return ret;
}
bool operator==(const Integer& l, int val)
{
	return l.core == val;
}
bool operator>(const Integer& l, int val)
{
	return l.core > val;
}
bool operator<(const Integer& l, int val)
{
	return l.core < val;
}
bool operator<=(const Integer& l, int val)
{
	return l.core <= val;
}
bool operator<=(const Integer& l, const Integer& r)
{
	return l.core <= r.core;
}
bool operator>=(const Integer& l, const Integer& r)
{
	return l.core >= r.core;
}
bool operator>=(const Integer& l, int val)
{
	return l.core >= val;
}
bool operator==(const Integer& l, const Integer& r)
{
	return l.core == r.core;
}
