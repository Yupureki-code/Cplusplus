#pragma once
#include <iostream>
using namespace std;
class Date
{
public:
	int GetMonthDay(int year, int month);
	Date(int year = 1900, int month = 1, int day = 1);
	Date(const Date& d);
	Date& operator=(const Date& d);
	~Date();
	Date& operator+=(int day);
	Date& operator-=(int day);
	Date& operator++();
	Date& operator--();
	bool operator>(const Date& d);
	bool operator==(const Date& d);
	bool operator >= (const Date& d);
	bool operator < (const Date& d);
	bool operator <= (const Date& d);
	bool operator != (const Date& d);
	int operator-(const Date& d);
	bool isleapyear(int year);
	void Print();
	void Check();
private:
	int _year;
	int _month;
	int _day;
};
