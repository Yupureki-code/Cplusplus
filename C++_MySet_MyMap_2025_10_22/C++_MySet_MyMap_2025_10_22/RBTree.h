#pragma once
#include <iostream>
#include <assert.h>
#include <windows.h>
using namespace std;

enum COLOR {
	BLACK,
	RED
};

template<class T>
struct RBTreeNode {
	RBTreeNode* _left;
	RBTreeNode* _right;
	RBTreeNode* _parent;
	T _data;
	COLOR _col;

	RBTreeNode(const T data = T())
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_data(data)
	{}
};

template<class T, class Ptr, class Ref>
struct RBTreeIterator {
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T, Ptr, Ref> Self;
	Node* _node;
	Node* _root;
	RBTreeIterator(Node* node = nullptr,Node* root = nullptr)
		:_node(node)
		,_root(root)
	{}

	template<class OtherPtr, class OtherRef>
	RBTreeIterator(const RBTreeIterator<T, OtherPtr, OtherRef>& other)
		: _node(other._node)
	{
	}
	Node* LeftFind(Node* node)
	{
		Node* cur = node;
		while (cur->_left)
			cur = cur->_left;
		return cur;
	}

	Node* RightFind(Node* node)
	{
		Node* cur = node;
		while (cur->_right)
			cur = cur->_right;
		return cur;
	}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &_node->_data;
	}

	bool operator!= (const Self& node)const
	{
		return _node != node._node;
	}

	bool operator== (const Self& node)const
	{
		return _node == node._node;
	}

	Self& operator++()
	{
		if (_node == nullptr)
			return *this;
		Node* parent = _node->_parent;
		if (_node->_right == nullptr)
		{
			if (parent->_left == _node)
			{
				_node = parent;
			}
			else
			{
				while (parent != nullptr && parent->_right == _node)
				{
					_node = parent;
					parent = parent->_parent;
				}
				_node = parent;
			}
		}
		else
		{
			_node = LeftFind(_node->_right);
		}
		return *this;
	}

	Self operator++(int)
	{
		Self tmp = *this;
		++(*this);
		return tmp;
	}

	Self operator+=(int i)
	{
		while (_node && i--)
		{
			++(*this);
		}
		return *this;
	}

	Self operator-=(int i)
	{
		Node* cur = LeftFind(_root);
		while (_node != cur && i--)
		{
			--(*this);
		}
		return *this;
	}

	Self operator--()
	{
		if (_node == nullptr)
		{
			_node = RightFind(_root);
		}
		if (_node->_left == nullptr)
		{
			Node* parent = _node->_parent;
			while (parent && parent->_left == _node)
			{
				_node = parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		else
		{
			_node = RightFind(_node->_left);
		}
		return *this;
	}

	Self operator--(int)
	{
		Self tmp = *this;
		--(*this);
		return tmp;
	}

};

template<class K,class T,class KeyOfPair,class ValueOfPair,bool ifmap = true>
class RBTree {
public:
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T, T*, T&> Iterator;
	typedef RBTreeIterator<T, const T*, const T&> const_Iterator;
	RBTree()
		:_root(nullptr)
	{}
	
	Iterator Begin()
	{
		Iterator cur(_root,_root);
		cur._node = cur.LeftFind(cur._node);
		return cur;
	}

	const_Iterator Begin()const
	{
		const_Iterator cur(_root,_root);
		cur._node = cur.LeftFind(cur._node);
		return cur;
	}

	Iterator End()
	{
		return Iterator(nullptr,_root);
	}

	const_Iterator End()const
	{
		return const_Iterator(nullptr,_root);
	}

	Node* Insert(T data)
	{
		KeyOfPair kop;
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return _root;
		}
		K key = kop(data);
		Node* newnode = new Node(data);
		newnode->_col = RED;
		Node* cur = _root;
		Node* child = cur;
		while (cur)
		{
			if (key < kop(cur->_data))
			{
				child = cur;
				cur = cur->_left;
			}
			else if (key > kop(cur->_data))
			{
				child = cur;
				cur = cur->_right;
			}
			else
			{
				return nullptr;
			}
		}
		if (key < kop(child->_data))
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

		return newnode;
	}

	Node* find(const K& k)
	{
		KeyOfPair kop;
		Node* cur = _root;
		while (cur)
		{
			if (kop(cur->_data) == k)
				break;
			else if (k <= kop(cur->_data))
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

	Node* root()
	{
		return _root;
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
		KeyOfPair kop;
		if (root == nullptr)
		{
			if (ret != sum)
			{
				cout << kop(root->_data) << " BlackNums ERROR" << endl;
				return false;
			}
			else
				return true;
		}
		if (root->_col == BLACK)
			ret++;
		if (root != _root && root->_col == RED && root->_parent->_col == RED)
		{
			cout << kop(root->_data) << " RED-RED ERROR" << endl;
			return false;
		}
		return _Check(root->_left,ret,sum) && _Check(root->_right,ret,sum);
	}


	void _PrintHorizontal(Node* root, int level, const string& prefix, bool isLeft)
	{
		KeyOfPair kop;
		ValueOfPair vop;
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
		
		cout << kop(root->_data);
		cout << "\033[0m";
		if (ifmap)
		{
			cout << "[" << vop(root->_data);
			cout << "]" << endl;
		}
		/*else if (root->_left && root->_right)
			cout << "©´" << endl;*/
		else
			cout << endl;
		
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