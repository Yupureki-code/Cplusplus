#pragma once
#include <iostream>
#include <vector>
using namespace std;


class BitSet {
public:
	BitSet(const vector<int>& v,size_t n)
		:_bit_table(n/32+1)
	{
		insert(v);
	}

	bool find(size_t pos)
	{
		int n = pos / 32;
		int m = pos % 32;
		int num = 1;
		num = num << m;
		if (n >= _bit_table.size())
			return false;
		if (_bit_table[n] & num)
		{
			return true;
		}
		return false;
	}

private:
	void insert(const vector<int>& v)
	{
		vector<int>::const_iterator it = v.begin();
		while (it != v.end())
		{
			int n = *it / 32;
			int m = *it % 32;
			int num = 1;
			num = num << m;
			_bit_table[n] = _bit_table[n] | num;
			it++;
		}
	}
	vector<int> _bit_table;
};