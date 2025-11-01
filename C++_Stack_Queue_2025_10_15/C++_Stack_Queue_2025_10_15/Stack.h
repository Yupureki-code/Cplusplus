#pragma once
#include <iostream>
#include <deque>
using namespace std;

template<class T, class con = deque<T>>
class stack {
public:
	stack()
	{}
	stack(const T& num)
	{
		_data.push_back(num);
	}
	stack(const stack& st)
	{
		_data = st._data;
	}
	void push(const T& num)
	{
		_data.push_back(num);
	}
	void pop()
	{
		_data.pop_back();
	}
	T& top()
	{
		return _data.back();
	}
	size_t size()
	{
		return _data.size();
	}
	bool empty()
	{
		return _data.empty();
	}

private:
	con _data;
};