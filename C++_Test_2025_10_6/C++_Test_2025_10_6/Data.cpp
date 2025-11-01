#define _CRT_SECURE_NO_WARNINGS 1
#include "Data.h"

Date::Date(int year, int month, int day) {
	_year = year;
	_month = month;
	_day = day;
}

Date::Date(const Date& d) {
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

	Date& Date::operator=(const Date& d)
	{
		if (*this != d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}
	bool Date::isleapyear(int year)
	{
		if (year % 4 == 0)
		{
			if (year % 100 == 0)
			{
				if (year % 400 == 0)
					return true;
				else
					return false;
			}
			else
				return true;
		}
		else
			return false;
	}
	int Date::GetMonthDay(int year, int month)
	{
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			return 31;
		else if (month == 2)
		{
			if (isleapyear(year))
			{
				return 29;
			}
			return 28;
		}
		else
			return 30;
	}
	Date& Date::operator+=(int day)
	{
		_day += day;
		Check();
		return *this;
	}
	Date& Date::operator-=(int day)
	{
		_day -= day;
		Check();
		return *this;
	}
	Date& Date::operator++()
	{
		++_day;
		Check();
		return *this;
	}
	Date& Date::operator--()
	{
		--_day;
		Check();
		return *this;
	}
	bool Date::operator>(const Date& d)
	{
		if (_year > d._year) return true;
		if (_year == d._year && _month > d._month) return true;
		if (_year == d._year && _month == d._month && _day > d._day) return true;
		return false;
	}
	bool Date::operator==(const Date& d)
	{
		return _year == d._year && _month == d._month && _day == d._day;
	}
	bool Date::operator >= (const Date& d)
	{
		return operator>(d) || operator==(d);
	}
	bool Date::operator < (const Date& d)
	{
		if (_year < d._year) return true;
		if (_year == d._year && _month < d._month) return true;
		if (_year == d._year && _month == d._month && _day < d._day) return true;
		return false;
	}
	bool Date::operator <= (const Date& d)
	{
		return Date::operator<(d) || Date::operator==(d);
	}
	bool Date::operator != (const Date& d)
	{
		return !Date::operator==(d);
	}
	int Date::operator-(const Date& d)
	{
		int maxyear,minyear,maxmonth,minmonth,maxday,minday;
		if (operator>=(d))
		{
			maxyear = _year;
			minyear = d._year;
			maxmonth = _month;
			minmonth = d._month;
			maxday = _day;
			minday = d._day;
		}
		else
		{
			maxyear = d._year;
			minyear = _year;
			maxmonth = d._month;
			minmonth = _month;
			maxday = d._day;
			minday = _day;
		}
		while (maxmonth != 1)
		{
			int day = GetMonthDay(maxyear,maxmonth - 1);
			maxday += day;
			maxmonth--;
		}
		while (minmonth != 1)
		{
			int day = GetMonthDay(minyear, minmonth - 1);
			minday += day;
			minmonth--;
		}
		while (maxyear - minyear)
		{
			if (isleapyear(maxyear-1))
			{
				maxday += 366;
			}
			else
			{
				maxday += 365;
			}
			maxyear--;
		}
		return maxday - minday;
	}
	Date::~Date()
	{
		_year = 0;
		_month = 0;
		_day = 0;
	}
	void Date::Print()
	{
		cout << _year << " " << _month << " " << _day << endl;
	}
	void Date::Check()
	{
		while (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			_month++;
			if (_month == 13)
			{
				_month = 1;
				_year++;
			}
		}
		while (_day <= 0) {
			_month--;
			if (_month < 1) {
				_month = 12;
				_year--;
			}
			_day += GetMonthDay(_year, _month);
		}
		
	}