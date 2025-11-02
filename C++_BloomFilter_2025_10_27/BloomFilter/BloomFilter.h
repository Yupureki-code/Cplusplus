#pragma once
#include <iostream>
#include <vector>
using namespace std;

template<size_t capacity = 1000>
class BloomFilter {
public:

	BloomFilter()
		:_table(capacity/32+1)
	{}


	unsigned int hashfunc1(const char* str, unsigned int len)
	{
		unsigned int b = 378551;
		unsigned int a = 63689;
		unsigned int hash = 0;
		unsigned int i = 0;

		for (i = 0; i < len; str++, i++)
		{
			hash = hash * a + (*str);
			a = a * b;
		}
		return hash % (_table.size() * 32);
	}

	unsigned int hashfunc2(const char* str, unsigned int len)
	{
		unsigned int hash = 1315423911;
		unsigned int i = 0;

		for (i = 0; i < len; str++, i++)
		{
			hash ^= ((hash << 5) + (*str) + (hash >> 2));
		}
		return hash % (_table.size() * 32);
	}

	unsigned int hashfunc3(const char* str, unsigned int len)
	{
		const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
		const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
		const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
		const unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
		unsigned int hash = 0;
		unsigned int test = 0;
		unsigned int i = 0;

		for (i = 0; i < len; str++, i++)
		{
			hash = (hash << OneEighth) + (*str);

			if ((test = hash & HighBits) != 0)
			{
				hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
			}
		}
		return hash % (_table.size() * 32);
	}

	void insert(const string& s)
	{
		size_t key1 = hashfunc1(s.c_str(), s.size());
		size_t key2 = hashfunc2(s.c_str(), s.size());
		size_t key3 = hashfunc3(s.c_str(), s.size());
		vector<size_t> v({ key1,key2,key3 });
		vector<size_t>::iterator it = v.begin();
		while (it != v.end())
		{
			size_t n = *it / 32;
			size_t m = *it % 32;
			int num = 1;
			num = num << m;
			_table[n] = _table[n] | num;
			it++;
		}

	}

	bool isexist(const string& s)
	{
		size_t key1 = hashfunc1(s.c_str(), s.size());
		size_t key2 = hashfunc2(s.c_str(), s.size());
		size_t key3 = hashfunc3(s.c_str(), s.size());
		vector<size_t> v({ key1,key2,key3 });
		vector<size_t>::iterator it = v.begin();
		while (it != v.end())
		{
			size_t n = *it / 32;
			size_t m = *it % 32;
			int num = 1;
			num = num << m;
			if (!(_table[n] & num))
			{
				return false;
			}
			
			it++;
		}
		return true;
	}

	bool isempty(const string& s)
	{
		return !isexist(s);
	}


private:
	vector<size_t> _table;
};