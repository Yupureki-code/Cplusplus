#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

template<class T>
struct ListNode {
	T _data;
	ListNode* prev;
	ListNode* next;
	ListNode()
		:_data(T())
		,prev(nullptr)
		,next(nullptr)
	{}
	ListNode(T data)
		:_data(data)
		,prev(nullptr)
		,next(nullptr)
	{}
	ListNode(const ListNode<T>& pnode)
	{
		_data = pnode._data;
		next = pnode.next;
		prev = pnode.prev;
	}
	ListNode& operator=(const ListNode<T>& pnode)
	{
		_data = pnode._data;
		next = pnode.next;
		prev = pnode.prev;
		return *this;
	}
};

template<class T>
struct List_Iterator {
	typedef ListNode<T> Node;
	typedef List_Iterator iterator;
	Node* node;
	List_Iterator()
	{}

	List_Iterator(const Node* pnode)
	{
		node = new Node();
		node->_data = pnode->_data;
		node->next = pnode->next;
		node->prev = pnode->prev;
	}
	iterator& operator++()
	{
		node = node->next;
		return *this;
	}

	iterator& operator++(int)
	{
		iterator tmp = *this;
		node = node->next;
		return tmp;
	}

	iterator& operator--(int)
	{
		iterator tmp = *this;
		node = node->prev;
		return tmp;
	}

	T& operator*()const
	{
		return node->_data;
	}


	iterator& operator--()
	{
		node = node->prev;
		return *this;
	}

	bool operator==(const iterator& pnode)const
	{
		return node->_data == pnode.node->_data;
	}
	
	bool operator!=(const iterator& pnode)const
	{
		return node->_data != pnode.node->_data;
	}
};

template<class T>
class List {
	typedef ListNode<T> Node;
	typedef List_Iterator<T> iterator;
public:
	List()
	{
		_head = new Node();
		_head->_data = 0;
		_head->next = _head;
		_head->prev = _head;
		_size = 0;
	}

	List(T data)
	{
		_head = new Node();
		_head->_data = 0;
		_head->next = _head;
		_head->prev = _head;
		_size = 0;
		push_front(data);
	}

	size_t size()
	{
		return _size;
	}

	bool empty()
	{
		return _size == 0;
	}

	void push_back(T data)
	{
		insert(_size+1, data);
	}

	iterator begin()
	{
		return iterator(_head->next);
	}

	iterator end()
	{
		return iterator(_head->prev);
	}

	void push_front(T data)
	{
		insert(1, data);
	}

	void pop_back()
	{
		pop(_size);
	}

	void pop_front()
	{
		pop(1);
	}

	void insert(size_t pos, T data)
	{
		assert(pos >= 0 && pos <= _size + 1);
		Node* newnode = new Node(data);
		Node* cur(_head->next);
		Node* prev(_head);
		while (pos--)
		{
			if (pos == 0)
				break;
			cur = cur->next;
			prev = prev->next;
		}
		prev->next = newnode;
		newnode->next = cur;
		newnode->prev = prev;
		cur->prev = newnode;
		_size++;
	}

	void pop(size_t pos)
	{
		assert(pos >= 1 && pos <= _size);
		Node* cur(_head->next);
		Node* prev(_head);
		while (--pos)
		{
			cur = cur->next;
			prev = prev->next;
		}
		prev->next = cur->next;
		cur->next->prev = prev;
		_size--;
	}

	void Print()
	{
		iterator it = begin();
		cout << "head->";
		size_t count = _size;
		while (count--)
		{
			cout << *it << "->";
			it++;
		}
		cout << "tail"<<endl;
	}

	void clear()
	{
		while (_size)
		{
			pop(_size);
		}
	}
	
	void replace(size_t pos,T n)
	{
		pop(pos);
		insert(pos, n);
	}

	void resize(size_t n)
	{
		assert(n >= 0);
		if (_size < n)
		{
			while (_size != n)
			{
				push_back(T());
			}
		}
		else if (_size > n)
		{
			while (_size != n)
			{
				pop_back();
			}
		}
	}

private:
	Node* _head;
	size_t _size;
};