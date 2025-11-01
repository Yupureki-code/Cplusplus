#pragma once
#include "Hash.h"

template<class K,class V>
class Unordered_Map{
	struct MapOfKey {
		const K& operator()(const pair<K, V>& node)
		{
			return node.first;
		}
	};

	struct MapOfValue {
		const V& operator()(const pair<K, V>& node)
		{
			return node.second;
		}
	};
public:
	typename typedef HashTable<K, pair<K, V>, MapOfKey, MapOfValue>::Iterator iterator;
	typename typedef HashTable<K, pair<K, V>, MapOfKey, MapOfValue>::const_Iterator const_iterator;
	void insert(const K& key, const V& value)
	{
		myunordered_map.Insert({ key, value });
	}

	bool erase(const K& key)
	{
		return myunordered_map.Erase(key);
	}

	pair<K, V>* find(const K& key)
	{
		return myunordered_map.Find(key);
	}

	V& operator[](const K& key)
	{
		return myunordered_map[key];
	}

	void print()
	{
		myunordered_map.Print();
	}

	iterator begin()
	{
		return myunordered_map.Begin();
	}

	iterator end()
	{
		return myunordered_map.End();
	}


private:
	HashTable<K, pair<K,V>, MapOfKey, MapOfValue> myunordered_map;
};
