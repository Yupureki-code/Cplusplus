#pragma once
#include <iostream>
#include <assert.h>
#include <windows.h>
using namespace std;


enum COLOR {
	BLACK,
	RED
};


template<class K,class V>
struct RBTreeNode {
	RBTreeNode* _left;
	RBTreeNode* _right;
	RBTreeNode* _parent;
	pair<K, V> _kv;
	COLOR _col;

	RBTreeNode(const pair<K,V> kv = pair<K,V>())
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_kv(kv)
	{}
};

template<class K,class V>
class RBTree {
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(nullptr)
	{}

	bool Insert(const K& key, const V& value)
	{
		if (_root == nullptr)
		{
			_root = new Node({key,value});
			_root->_col = BLACK;
			return true;
		}
		Node* newnode = new Node({ key,value });
		newnode->_col = RED;
		Node* cur = _root;
		Node* child = cur;
		while (cur)
		{
			if (key < cur->_kv.first)
			{
				child = cur;
				cur = cur->_left;
			}
			else if (key > cur->_kv.first)
			{
				child = cur;
				cur = cur->_right;
			}
			else
			{
				find(key)->_kv.second++;
				return true;
			}
		}
		if (key < child->_kv.first)
		{
			child->_left = newnode;
			newnode->_parent = child;
		}
		else
		{
			child->_right = newnode;
			newnode->_parent = child;
		}
		child = newnode;
		Node* parent = child->_parent;
		while (child->_col == RED && parent && parent->_col == RED)
		{
			parent = child->_parent;
			Node* pparent = parent->_parent;
			Node* uncle = nullptr;
			if (pparent == nullptr)
				break;
			else
			{
				if (pparent->_left == parent)
					uncle = pparent->_right;
				else
					uncle = pparent->_left;

				if (uncle && uncle->_col == RED)
				{
					uncle->_col = BLACK;
					parent->_col = BLACK;
					pparent->_col = RED;
					child = pparent;
					parent = child->_parent;
				}
				else
				{
					if (pparent->_left == parent)
					{
						if (parent->_right == child)
						{
							RotateL(parent);
							RotateR(pparent);
							child->_col = BLACK;
							pparent->_col = RED;
							
						}
						else
						{
							RotateR(pparent);
							parent->_col = BLACK;
							pparent->_col = RED;
							child = parent;
							parent = child->_parent;
						}
					}
					else
					{
						if (parent->_left == child)
						{
							RotateR(parent);
							RotateL(pparent);
							child->_col = BLACK;
							pparent->_col = RED;
						}
						else
						{
							RotateL(pparent);
							parent->_col = BLACK;
							pparent->_col = RED;
							child = parent;
							parent = child->_parent;
						}
					}
				}
			}
		}
		_root->_col = BLACK;

		return true;
	}

	Node* find(const K& k)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first == k)
				break;
			else if (k <= cur->_kv.first)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		return cur;
	}

	int maxheight()
	{
		return _maxheight(_root);
	}

	int minheight()
	{
		return _minheight(_root);
	}

	int size()
	{
		return _size(_root);
	}

	void PrintHorizontal()
	{
		_PrintHorizontal(_root, 0, "", true);
		cout << endl;
	}

	bool Check()
	{
		int sum = BlackCount();
		return _Check(_root,0,sum);
	}

	int BlackCount()
	{
		return _BlackCount(_root,0);
	}

private:

	int _BlackCount(Node* root, int sum)
	{
		if (root == nullptr)
		{
			return sum;
		}
		if (root->_col == BLACK)
			sum++;
		_BlackCount(root->_left, sum);
	}

	bool _Check(Node* root, int ret, const int sum)
	{
		if (root == nullptr)
		{
			if (ret != sum)
			{
				cout << root->_kv.first << " BlackNums ERROR" << endl;
				return false;
			}
			else
				return true;
		}
		if (root->_col == BLACK)
			ret++;
		if (root != _root && root->_col == RED && root->_parent->_col == RED)
		{
			cout << root->_kv.first << " RED-RED ERROR" << endl;
			return false;
		}
		return _Check(root->_left,ret,sum) && _Check(root->_right,ret,sum);
	}


	void _PrintHorizontal(Node* root, int level, const string& prefix, bool isLeft)
	{
		if (root == nullptr) {
			return;
		}

		cout << prefix;
		cout << (isLeft ? "©À©¤©¤" : "©¸©¤©¤");

		if (root->_col == RED) {
			cout << "\033[1;31m";
		}
		else {
			cout << "\033[1;37m";
		}

		cout << root->_kv.first;
		cout << "\033[0m";

		cout << "[" << root->_kv.second;
		cout << "]" << endl;
		string newPrefix = prefix + (isLeft ? "©¦   " : "    ");
		_PrintHorizontal(root->_right, level + 1, newPrefix, true);
		_PrintHorizontal(root->_left, level + 1, newPrefix, false);
	}

	int _maxheight(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		int left = _maxheight(root->_left);
		int right = _maxheight(root->_right);
		return left > right ? left + 1 : right + 1;
	}

	int _minheight(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		int left = _minheight(root->_left);
		int right = _minheight(root->_right);
		return left > right ? right + 1 : left + 1;
	}

	int _size(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		return _size(root->_left) + _size(root->_right) + 1;
	}

	void RotateR(Node* parent)
	{
		Node* pparent = parent->_parent;
		Node* child = parent->_left;
		Node* cchild = child->_right;
		parent->_left = cchild;
		if (cchild)
			cchild->_parent = parent;
		child->_right = parent;
		if (pparent != nullptr)
		{
			if (pparent->_left == parent)
				pparent->_left = child;
			else
				pparent->_right = child;
		}
		else
			_root = child;
		child->_parent = pparent;
		parent->_parent = child;
	}
	void RotateL(Node* parent)
	{
		Node* pparent = parent->_parent;
		Node* child = parent->_right;
		Node* cchild = child->_left;
		parent->_right = cchild;
		if (cchild)
			cchild->_parent = parent;
		child->_left = parent;
		if (pparent != nullptr)
		{
			if (pparent->_left == parent)
				pparent->_left = child;
			else
				pparent->_right = child;
		}
		else
			_root = child;
		child->_parent = pparent;
		parent->_parent = child;
	}


	Node* _root;
};