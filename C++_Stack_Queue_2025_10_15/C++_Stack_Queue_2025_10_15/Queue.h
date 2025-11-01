#pragma once
#include <iostream>
#include <deque>
using namespace std;

template<class T,class con = deque<T>>
class queue {
public:
	queue()
	{}
	queue(const T& num)
	{
		_data.push_back(num);
	}
	queue(const queue& qu)
	{
		_data = qu._data;
	}
	void push(const T& num)
	{
		_data.push_front(num);
	}
	void pop()
	{
		_data.pop_back();
	}
	T& top()
	{
		return _data.front();
	}
	void size()
	{
		return _data.size();
	}
	void empty()
	{
		return _data.empty();
	}
private:
	con _data;
};