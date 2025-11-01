#pragma once
#include "RBTree.h"
template<class K,class V>
class Map {
	struct MapOfKey
	{
		K& operator()(pair<K, V>& x)
		{
			return x.first;
		}
	};

	struct MapOfValue
	{
		V& operator()(pair<K, V>& x)
		{
			return x.second;
		}
	};
public:
	typedef RBTreeNode<pair<K, V>> Node;
	typedef typename RBTree<K, pair<K, V>, MapOfKey, MapOfValue>::Iterator iterator;
	typedef typename RBTree<K, pair<K, V>, MapOfKey, MapOfValue>::const_Iterator const_iterator;
	Map()
	{}

	V& operator[](K key)
	{
		Node* tmp = MyMap.find(key);
		if (tmp == nullptr)
			return insert(key, 1)->_data.second;
		else
			return tmp->_data.second;
	}

	Node* insert(K key, V value)
	{
		return MyMap.Insert({ key, value });
	}

	void Print()
	{
		MyMap.PrintHorizontal();
	}

	iterator begin()
	{
		return MyMap.Begin();
	}

	iterator end()
	{
		return MyMap.End();
	}

	const_iterator begin() const
	{
		return MyMap.Begin();
	}

	const_iterator end() const
	{
		return MyMap.End();
	}
	
private:
	RBTree<K, pair<K, V>, MapOfKey, MapOfValue> MyMap;
};