#pragma once
#include "RBTree.h"
template<class K>
class Set {
	struct MapOfKey
	{
		K& operator()(K& x)
		{
			return x;
		}
	};

	struct MapOfValue
	{
		K& operator()(K& x)
		{
			return x;
		}
	};
public:
	typedef typename RBTree<K, K, MapOfKey, MapOfValue>::Iterator iterator;
	typedef typename RBTree<K, K, MapOfKey, MapOfValue>::const_Iterator const_iterator;

	void insert(K key)
	{
		MySet.Insert(key);
	}

	void Print()
	{
		MySet.PrintHorizontal();
	}

	iterator begin()
	{
		return MySet.Begin();
	}

	iterator end()
	{
		return MySet.End();
	}

	const_iterator begin() const
	{
		return MySet.Begin();
	}

	const_iterator end() const
	{
		return MySet.End();
	}


private:
	RBTree<K, K, MapOfKey, MapOfValue,false> MySet;
};
