#pragma once
#include "Hash.h"
template<class K>
class Unordered_Set {
	struct MapOfKey {
		const K& operator()(const K& node)
		{
			return node;
		}
	};

	struct MapOfValue {
		const K& operator()(const K& node)
		{
			return node;
		}
	};
public:
	typename typedef HashTable<K, K, MapOfKey, MapOfValue>::Iterator iterator;
	typename typedef HashTable<K, K, MapOfKey, MapOfValue>::const_Iterator const_iterator;

	void insert(const K& key)
	{
		myunordered_set.Insert(key);
	}

	bool erase(const K& key)
	{
		return myunordered_set.Erase(key);
	}

	K* find(const K& key)
	{
		return myunordered_set.Find(key);
	}

	iterator begin()
	{
		return myunordered_set.Begin();
	}

	iterator end()
	{
		return myunordered_set.End();
	}


private:
	HashTable<K, K, MapOfKey, MapOfValue> myunordered_set;
};