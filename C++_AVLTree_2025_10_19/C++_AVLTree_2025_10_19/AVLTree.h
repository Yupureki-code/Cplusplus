#pragma once
#include <iostream>
#include <assert.h>
#include <queue>
using namespace std;

template<class T>
struct AVLTreeNode
{
	AVLTreeNode(const T& data = T())
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(data)
		, _bf(0)
	{}

	AVLTreeNode<T>* _left;
	AVLTreeNode<T>* _right;
	AVLTreeNode<T>* _parent;
	T _data;
	int _bf;
};


template<class T>
class AVLTree
{
	typedef AVLTreeNode<T> Node;
public:
	AVLTree()
		: _root(nullptr)
	{}


	void InsertCheck(Node* prev)
	{
		while (prev)
		{
			if (prev->_bf == -1 || prev->_bf == 1)
			{
				if (prev->_parent && prev->_parent->_left == prev)
				{
					prev->_parent->_bf--;
				}
				else if (prev->_parent && prev->_parent->_right == prev)
				{
					prev->_parent->_bf++;
				}
				prev = prev->_parent;
			}
			else if (prev->_bf == 0)
			{
				return;
			}
			else
			{
				if (prev->_bf == -2)
				{
					if (prev->_left->_bf == -1)
					{
						RotateR(prev);
					}
					else if (prev->_left->_bf == 1)
					{
						RotateL(prev->_left);
						RotateR(prev);
					}
				}
				else if (prev->_bf == 2)
				{
					if (prev->_right->_bf == 1)
					{
						RotateL(prev);
					}
					else if (prev->_right->_bf == -1)
					{
						RotateR(prev->_right);
						RotateL(prev);
					}
				}
			}
		}
	}

	void EraseCheck(Node* prev)
	{
		while (prev)
		{
			if (prev->_bf == -1 || prev->_bf == 1)
			{
				return;
			}
			else  if (prev->_bf == 0)
			{
				if (prev->_parent && prev->_parent->_left == prev)
				{
					prev->_parent->_bf++;
					prev = prev->_parent;
				}
				else if (prev->_parent && prev->_parent->_right == prev)
				{
					prev->_parent->_bf--;
					prev = prev->_parent;
				}
				else
				{
					prev = prev->_parent;
				}
			}
			else
			{
				if (prev->_bf == -2)
				{
					if (prev->_left->_bf == -1 || prev->_left->_bf == 0)
					{
						RotateR(prev);
					}
					else if (prev->_left->_bf == 1)
					{
						RotateL(prev->_left);
						RotateR(prev);
					}
				}
				else if (prev->_bf == 2)
				{
					if (prev->_right->_bf == 1||prev->_right->_bf == 0)
					{
						RotateL(prev);
					}
					else if (prev->_right->_bf == -1)
					{
						RotateR(prev->_right);
						RotateL(prev);
					}
				}
				prev = prev->_parent;
			}
		}
	}

	bool Insert(const T& data)
	{
		Node* newnode = new Node(data);
		if (_root == nullptr)
		{
			_root = newnode;
			return true;
		}
		Node* cur = _root;
		Node* prev = _root;
		while (cur)
		{
			if(data <=cur->_data)
			{
				prev = cur;
				cur = cur->_left;
			}
			else
			{
				prev = cur;
				cur = cur->_right;
			}
		}
		if (data <= prev->_data)
		{
			prev->_bf--;
			prev->_left = newnode;
			newnode->_parent = prev;
		}
		else
		{
			prev->_bf++;
			newnode->_parent = prev;
			prev->_right = newnode;
		}
		InsertCheck(prev);
		return true;
	}

	// AVLÊ÷µÄÑéÖ¤
	bool IsAVLTree()
	{
		if (_IsAVLTree(_root))
		{
			cout << "yes" << endl;
			return true;
		}
		else
		{
			cout << "no" << endl;
			return false;
		}
	}

	void InOrder()
	{
		if (_root == nullptr)
		{
			cout << "NULL";
			return;
		}
		_InOrder(_root);
	}

	Node* find(const T& k)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_data == k)
			{
				break;
			}
			else if (k <= cur->_data)
			{
				cur = cur->_left;
			}
			else if (k > cur->_data)
			{
				cur = cur->_right;
			}
		}
		return cur;
	}

	int height()
	{
		return _height(_root);
	}

	int size()
	{
		return _size(_root);
	}

	bool erase(const T& k)
	{
		Node* node = find(k);
		if (node == nullptr)
			return false;
		Node* parent = node->_parent;
		Node* child = node->_right;
		Node* cparent = child;
		if (child == nullptr)
		{
			if (node == _root)
			{
				if (node->_left == nullptr)
					delete _root;
				else
				{
					_root = _root->_left;
					delete node;
				}
			}
			else
			{
				if (parent->_left == node)
				{
					parent->_left = node->_left;
					parent->_bf++;
				}
				else
				{
					parent->_right = node->_left;
					parent->_bf--;
				}
				if (node->_left)
				{
					node->_left->_parent = node->_parent;
				}
				delete node;
				EraseCheck(parent);
			}
		}
		else
		{
			if (child->_left == nullptr)
			{
				node->_right = child->_right;
				if(child->_right)
					child->_right->_parent = node;
				node->_data = child->_data;
				node->_bf--;
				EraseCheck(node);
				delete child;
			}
			else
			{
				while (child)
				{
					cparent = child;
					child = child->_left;
				}
				cparent->_parent->_left = cparent->_right;
				if (cparent->_right)
					cparent->_right->_parent = cparent->_parent;
				node->_data = cparent->_data;
				cparent->_parent->_bf++;
				EraseCheck(cparent->_parent);
				delete cparent;
			}
		}
		return true;
	}

	void LevelPrint()
	{
		Node* root = _root;
		queue<Node*> q;
		int num = 1;
		int count = 1;
		int level = 0;
		q.push(root);
		while (q.size())
		{
			for (int i = 0; i < 50 - level;i++)
			{
				cout << " ";
			}
			while (num >= count && num < count*2)
			{
				if (q.size() == 0)
					break;
				Node* node = q.front();
				if (node)
				{
					if (node->_left)
						q.push(node->_left);
					if(node->_right)
						q.push(node->_right);
					q.pop();
					cout/* << node->_data << ":"*/<<node->_bf<<" ";
					num++;
				}
				else
					break;
			}
			level++;
			cout << endl;
			count *= 2;
		}
	}
	void PrintHorizontalPretty() 
	{
		_PrintHorizontalPretty(_root, 0, "", true);
		cout << endl;
	}

private:
	void _PrintHorizontalPretty(Node* root, int level, const string& prefix, bool isLeft) 
	{
		if (root == nullptr) {
			return;
		}
		cout << prefix;
		cout << (isLeft ? "©À©¤©¤" : "©¸©¤©¤");
		cout << root->_data << "[" << root->_bf << "]" << endl;
		string newPrefix = prefix + (isLeft ? "©¦   " : "    ");
		_PrintHorizontalPretty(root->_right, level + 1, newPrefix, true);
		_PrintHorizontalPretty(root->_left, level + 1, newPrefix, false);
	}

	int _height(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		int left = _height(root->_left);
		int right = _height(root->_right);
		return left > right ? left + 1: right + 1;
	}

	int _size(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		return _size(root->_left) + _size(root->_right) + 1;
	}

	bool _IsAVLTree(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}
		if (root->_bf == -2 || root->_bf == 2)
		{
			return false;
		}
		if (root->_left != nullptr && root->_left->_data > root->_data)
		{
			return false;
		}
		if (root->_right != nullptr && root->_right->_data < root->_data)
		{
			return false;
		}
		if (_IsAVLTree(root->_left) && _IsAVLTree(root->_right))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	size_t _Height(Node* root);


	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_data << " " << root->_bf << endl;
		_InOrder(root->_right);
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
		child->_bf = 0;
		parent->_bf = 0;
	}
	void RotateL(Node* parent)
	{
		Node* pparent = parent->_parent;
		Node* child = parent->_right;
		Node* cchild = child->_left;
		parent->_right = cchild;
		if(cchild)
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
		child->_bf = 0;
		parent->_bf = 0;

	}
private:
	Node* _root;
};