#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <assert.h>
using namespace std;

template<class T>
struct HashNode {
	list<T> _kv;
	HashNode()
	{}

	bool operator!=(HashNode* node)
	{
		return _kv != node->_kv;
	}

	bool operator==(HashNode* node)
	{
		return _kv == node->_kv;
	}

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

template<>
struct hashfunc<string>
{
	size_t operator()(const string& key)
	{
		size_t hash = 0;
		for (auto ch : key)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};

template<class T,class Ptr,class Ref>
struct HashTableIterator {
	typedef HashNode<T> Node;
	typedef HashTableIterator<T, Ptr, Ref> Self;
	Node* _node;
	typename list<T>::iterator _it;
	vector<Node>* _tables;
	size_t _bucket_index;
	HashTableIterator(vector<Node>* tables = nullptr, size_t bucket_idx = 0, Node* node = nullptr)
		: _tables(tables), _bucket_index(bucket_idx), _node(node)
	{
		if (_node && !_node->_kv.empty()) 
		{
			_it = _node->_kv.begin();
		}
	}

	HashTableIterator(const Self& other)
		: _tables(other._tables)
		, _bucket_index(other._bucket_index)
		,_node(other._node)
		, _it(other._it)
	{}


	Ref operator*()
	{
		return *(_it);
	}

	Ptr operator->()
	{
		return &(*_it);
	}

	bool operator !=(const Self & it)const
	{
		return _node != it._node || _it != it._it;
	}

	bool operator==(const Self& it)const
	{
		return _node == it._node && _it == it._it;
	}

	Self& operator++()
	{
		if (_node && _it != _node->_kv.end()) {
			++_it;
		}
		if (_it == _node->_kv.end())
		{
			while (_node)
			{
				++_bucket_index;
				if (_bucket_index < _tables->size())
				{
					_node = &(*_tables)[_bucket_index];
					if (!_node->_kv.empty()) {
						_it = _node->_kv.begin();
						break;
					}
				}
				else
				{
					_node = nullptr;
					_it = typename list<T>::iterator();
					break;
				}
			}
		}
		return *this;
	}

	Self operator++(int)
	{
		Self temp = *this;
		++(*this);
		return temp;
	}

};

template<class K, class T,class PairOfKey,class PairOfValue,class Hash = hashfunc<K>>
class HashTable{
	typedef HashNode<T> Node;
public:
	HashTable()
	{
		_table.resize(37);
	}

	typedef HashTableIterator<T, T*, T&> Iterator;
	typedef HashTableIterator<T, const T*, const T&> const_Iterator;
	Iterator Begin()
	{
		int i = 0;
		for (; i < _table.size(); i++)
		{
			if (_table[i]._kv.size() != 0)
			{
				break;
			}
		}
		Iterator it(&_table,i, &(_table[i]));
		return it;
	}

	Iterator End()
	{
		return Iterator(&_table, _table.size(), nullptr);
	}

	auto& operator[](const K& key)
	{
		T* ret = Find(key);
		if (!ret) {
			Insert({ key, 1 });
			ret = Find(key);
		}
		assert(ret);
		return ret->second;
	}

	size_t keyfunc(size_t key)
	{
		const double A = 0.6180339887;
		double val = key * A;
		return static_cast<size_t>(_table.size() * (val - static_cast<int>(val)));
	}

	bool Insert(const T& kv)
	{
		PairOfKey pok;
		PairOfValue pov;
		auto key = pok(kv);
		auto value = pov(kv);
		Hash hash;
		auto it = Find(pok(kv));
		if (it)
			return false;
		if (_n == _table.size())
		{
			HashTable<K,T, PairOfKey, PairOfValue> tmp;
			tmp._table.resize(_table.size() * 1.5);
			typename vector<Node>::iterator it1 = _table.begin();
			while (it1 != _table.end())
			{
				typename list<T>::iterator it2 = (*it1)._kv.begin();
				while (it2 != (*it1)._kv.end())
				{
					tmp.Insert(*it2);
					it2++;
				}
				it1++;
			}
			swap(*this, tmp);
		}
		size_t hash0 = keyfunc(hash(key)) % _table.size();
		_table[hash0]._kv.push_front(kv);
		_n++;
		return true;
	}

	T* Find(const K& key)
	{
		Hash hash;
		PairOfKey pok;
		size_t hash0 = keyfunc(hash(key)) % _table.size();
		if (hash0 >= _table.size())
			return nullptr;
		if (_table[hash0]._kv.size() == 0)
			return nullptr;
		typename list<T>::iterator it = _table[hash0]._kv.begin();
		while (it != _table[hash0]._kv.end())
		{
			if (pok(*it) == key)
				return &(*it);
			it++;
		}
		return nullptr;
	}

	bool Erase(K key)
	{
		Hash hash;
		size_t hash0 = keyfunc(hash(key)) % _table.size();
		if (hash0 > _table.size())
			return false;
		if (_table[hash0]._kv.size() == 0)
			return false;
		typename list<T>::iterator it = _table[hash0]._kv.begin();
		while (it != _table[hash0]._kv.end())
		{
			if (pok(*it) == key)
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
		for (size_t i = 0; i < _table.size(); i++) {
			cout << "Bucket " << i << ": ";
			if (_table[i]._kv.empty()) {
				cout << "NULL";
			}
			else {
				for (const auto& kv : _table[i]._kv) {
					cout << kv.first << "[" << kv.second << "] ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

private:
	vector<Node> _table;
	size_t _n = 0;
};

