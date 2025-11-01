#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <assert.h>
using namespace std;

template<class K,class V>
struct HashNode {
	list<pair<K, V>> _kv;

	HashNode()
	{}
};
template<class K>
struct hashfunc
{
	size_t operator()(K key)
	{
		size_t ret = key;
		return ret;
	}
};

template<class K, class V,class Hash = hashfunc<K>>
class HashTable{
	typedef HashNode<K, V> Node;
public:
	HashTable()
	{
		_table.resize(37);
	}

	V& operator[](const K& key)
	{
		pair<K, V>* ret = find(key);
		if (!ret) {
			insert({ key, V() });
			ret = find(key);
		}
		assert(ret);
		return ret->second;
	}

	size_t keyfunc(size_t key)
	{
		// 改进的乘法哈希
		const double A = 0.6180339887;
		double val = key * A;
		return static_cast<size_t>(_table.size() * (val - static_cast<int>(val)));
	}
	
	void insert(const pair<K, V>& kv)
	{
		K key = kv.first;
		V value = kv.second;
		Hash hash;
		auto node = find(key);
		if (node) {
			node->second++; 
			return;
		}
		if ((double)_n / _table.size() > 0.7)
		{
			HashTable<K, V> tmp;
			tmp._table.resize(_table.size() * 1.5);
			typename vector<Node>::iterator it1 = _table.begin();
			while (it1 != _table.end())
			{
				typename list<pair<K, V>>::iterator it2 = (*it1)._kv.begin();
				while (it2 != (*it1)._kv.end())
				{
					tmp.insert(*it2);
					it2++;
				}
				it1++;
			}
			swap(*this, tmp);
		}
		size_t hash0 = keyfunc(hash(key)) % _table.size();
		_table[hash0]._kv.push_front({ key,value });
		_n++;
		return;
	}

	pair<K,V>* find(const K& key)
	{
		Hash hash;
		size_t hash0 = keyfunc(hash(key)) % _table.size();
		if (hash0 >= _table.size())
			return nullptr;
		if (_table[hash0]._kv.size() == 0)
			return nullptr;
		typename list<pair<K, V>>::iterator it = _table[hash0]._kv.begin();
		while (it != _table[hash0]._kv.end())
		{
			if (it->first == key)
				return &(*it);
			it++;
		}
		return nullptr;
	}

	bool erase(K key)
	{
		Hash hash;
		size_t hash0 = keyfunc(hash(key)) % _table.size();
		if (hash0 > _table.size())
			return false;
		if (_table[hash0]._kv.size() == 0)
			return false;
		typename list<pair<K, V>>::iterator it = _table[hash0]._kv.begin();
		while (it != _table[hash0]._kv.end())
		{
			if (it->first == key)
				break;
			it++;
		}
		if (it == _table[hash0]._kv.end())
			return false;
		else
		{
			_table[hash0]._kv.erase(it);
			_n--;
			return true;
		}
		
		
	}

	void Print()
	{
		typename vector<Node>::iterator it = _table.begin();
		while (it != _table.end())
		{
			typename list<pair<K, V>>::iterator it2 = (*it)._kv.begin();
			if (it2 != (*it)._kv.end())
			{
				while (it2 != (*it)._kv.end())
				{
					cout << it2->first << "[" << it2->second << "] ";
					it2++;
				}
			}
			else
			{
				it++;
				continue;
				cout << "NULL ";
			}
			cout << endl;
			it++;
		}
		cout << endl;
	}
private:
	vector<Node> _table;
	size_t _n = 0;
};

