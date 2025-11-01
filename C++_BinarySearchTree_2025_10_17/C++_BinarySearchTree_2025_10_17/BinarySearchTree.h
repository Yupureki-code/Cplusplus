#pragma once
#include <iostream>
#include <assert.h>
#include <windows.h>
using namespace std;
template<class T, class V>
struct BSNode {
	typedef BSNode<T,V> Node;
	T key;
	V value;
	Node* left;
	Node* right;
	BSNode(const T& k = T(), const V& v = V())
		:key(k)
		,value(v)
		,left(nullptr)
		,right(nullptr)
	{}
	BSNode(const Node* node)
	{
		key = node->key;
		value = node->value;
		left = node->left;
		right = node->right;
	}
};

template<class T, class V>
class BSTree {
	typedef BSNode<T,V> Node;
public:
	BSTree()
	{}
	BSTree(const Node* root)
	{
		_root->key = root->key;
		_root->value = root->value;
		_root->left = nullptr;
		_root->right = nullptr;
	}
	bool insert(const T& k,const V& v)
	{
		if (_root == nullptr)
		{
			_root = new Node(k, v);
			return true;
		}
		Node* cur = _root;
		Node* prev = nullptr;
		while (cur)
		{
			if (k <= cur->key)
			{
				prev = cur;
				cur = cur->left;
			}
			else if (k > cur->key)
			{
				prev = cur;
				cur = cur->right;
			}
			else
				return false;
		}
		Node* newnode = new Node(k, v);
		if (k <= prev->key)
		{
			prev->left = newnode;
		}
		else if (k > prev->key)
		{
			prev->right = newnode;
		}
	}

	Node* erase(const T& k)
	{
		assert(_root);
		Node* cur = _root;
		Node* prev = cur;
		while (cur)
		{
			if (cur->key == k)
			{
				break;
			}
			else if (k <= cur->key)
			{
				prev = cur;
				cur = cur->left;
			}
			else if (k > cur->key)
			{
				prev = cur;
				cur = cur->right;
			}
		}
		if (cur == nullptr)
		{
			return nullptr;
		}
		else if (cur->left == nullptr && cur->right == nullptr)
		{
			if (cur == _root)
			{
				_root = cur->right;
			}
			else
			{
				if (prev->left == cur)
				{
					prev->left = nullptr;
				}
				if (prev->right == cur)
				{
					prev->right = nullptr;
				}
			}
			delete cur;
		}
		else if (cur->left == nullptr)
		{
			if (cur == _root)
			{
				_root = cur->right;
			}
			else
			{
				if (prev->left == cur)
				{
					prev->left = cur->right;
				}
				if (prev->right == cur)
				{
					prev->right = cur->right;
				}
			}
			delete cur;
		}
		else if(cur->right == nullptr)
		{
			if (cur == _root)
			{
				_root = cur->left;
			}
			else
			{
				if (prev->left == cur)
				{
					prev->left = cur->left;
				}
				if (prev->right == cur)
				{
					prev->right = cur->left;
				}
			}
			delete cur;
		}
		else
		{
			Node* rightmin = cur->right;
			prev = cur;
			if (rightmin->left == nullptr)
			{
				cur->right = rightmin->right;
				cur->key = rightmin->key;
				cur->value = rightmin->value;
				delete rightmin;
				return cur;
			}
			while (rightmin->left)
			{
				prev = rightmin;
				rightmin = rightmin->left;
			}
			cur->key = rightmin->key;
			cur->value = rightmin->value;
			prev->left= rightmin->right;
			delete rightmin;
		}
		return cur;
	}

	Node* find(const T& k)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->key == k)
			{
				break;
			}
			else if (k <= cur->key)
			{
				cur = cur->left;
			}
			else if (k > cur->key)
			{
				cur = cur->right;
			}
		}
		return cur;
	}
	void Inorder()
	{
		if (_root == nullptr)
		{
			cout << "NULL";
			return;
		}
		Print(_root);
	}
	void Print(Node* cur)
	{
		if (cur == nullptr)
			return;
		Print(cur->left);
		cout << cur->key << " ";
		Print(cur->right);
	}
	Node* GetRoot()
	{
		return _root;
	}
private:
	Node* _root;
};