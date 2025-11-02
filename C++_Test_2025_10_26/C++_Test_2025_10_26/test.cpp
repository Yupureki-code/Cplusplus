#include <iostream>
#include <string>
#include <functional>
using namespace std;



template<class T>
class myunique_ptr{
public:
	typedef myunique_ptr<T> Self;
	myunique_ptr(T* ptr = nullptr)
		:_ptr(ptr)
	{}

	myunique_ptr(const Self& ptr) = delete;
	
	myunique_ptr(Self&& ptr)
		:_ptr(ptr._ptr)
	{
		ptr._ptr = nullptr;
	}

	~myunique_ptr()
	{
		delete _ptr;
	}

	void operator=(const Self& ptr) = delete;

	Self& operator=(Self&& ptr)
	{
		if (_ptr != ptr._ptr)
		{
			delete _ptr;
			_ptr = ptr._ptr;
			ptr._ptr = nullptr;
		}
		return *this;
	}

	T& operator*()const
	{
		return *_ptr;
	}

	T* operator->()const
	{
		return _ptr;
	}

private:
	T* _ptr;
};

template<class T>
class myshared_ptr {
public:
	typedef myshared_ptr<T> Self;
	myshared_ptr(T* ptr)
		:_ptr(ptr)
		,_pcount(new int(1))
	{}
	template<class U>
	myshared_ptr(T* ptr, U del)
		: _ptr(ptr)
		, _pcount(new int(1))
		, _del(del)
	{}

	myshared_ptr(const Self& ptr)
	{
		_ptr = ptr._ptr;
		_pcount = ptr._pcount;
		(*_pcount)++;
	}

	Self& operator=(const Self& ptr)
	{
		_ptr = ptr._ptr;
		_pcount = ptr._pcount;
		(*_pcount)++;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
	~myshared_ptr()
	{
		if (--(*_pcount) == 0)
		{
			_del(_ptr);
			delete _pcount;
		}
	}
private:
	T* _ptr;
	int* _pcount;
	function<void(T*)> _del = [](T* ptr) {delete ptr; };
};


class Date {
public:
	Date(int year,int month,int day)
		:_year(year)
		,_month(month)
		,_day(day)
	{}

	Date(const Date& date)
		:_year(date._year)
		, _month(date._month)
		, _day(date._day)
	{}

	~Date()
	{}

	int _year;
	int _month;
	int _day;

};

int main()
{
	//myunique_ptr<int> p1(new int(1));
	//myunique_ptr<int> p2(new int(2));
	//p1 = move(p2);
	//cout << *p1;
	/*myshared_ptr<Date> p1(new Date(1,2,3));
	myshared_ptr<Date> p2(p1);
	cout << (*p2)._day;*/
	myshared_ptr<int> p1(new int(1));
	myshared_ptr<int> p2(p1);

	cout << *p2;
		
	return 0;
}