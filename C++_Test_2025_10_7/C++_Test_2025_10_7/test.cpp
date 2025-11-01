#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

class A
{
public:
	A(int a1 = 1)
		:_a1(a1)
		,_a2(_a1)
	{
		cout << "A(int)" << endl;
	}
	A(const A& A1)
	{
		_a1 = A1._a1;
		_a2 = A1._a2;
		cout << "A(const A&)" << endl;
	}
	void Add(int x, int y)
	{
		_a1 += x;
		_a2 += y;
	}
	void Print()
	{
		cout << _a1 << " " << _a2 <<endl;
	}
	void printstatic()
	{
		cout << _a3 << endl;
	}
private:
	int _a2;
	int _a1;
	static int _a3;
};

int A::_a3 = 5;


A& fun()
{
	A a1 = 5;
	a1.Add(100, 100);
	cout << endl;
	return a1;
}

template<class T>
void Swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

class B {
public:
	void Add()
	{
		b1++;
	}
	void Print()
	{
		cout << b2 << endl;
	}
private:
	static int b2;
	int b1 = 1;
};
int B::b2 = 2;

class C {
public:
	C(int _c1 = 2)
		:c1(_c1)
	{ }
	void Print()
	{
		cout << c1 << endl;
	}
private:
	int c1 = 1;
};

template<class T>
class Stack {
public:
	Stack()
		:arr(new T[4])
		,size(0)
		,capacity(4)
	{}
	void StackPush(T data)
	{
		if (size == capacity)
		{
			T* tmp = new T[capacity * 2];
			memcpy(tmp, arr, sizeof(T) * size);
			arr = tmp;
			capacity *= 2;
		}
		arr[size] = data;
		size++;
	}
	void StackPop()
	{
		size--;
	}
	void StackPrint()
	{
		for (int i = 0; i < size; i++)
		{
			printf("%d ", arr[i]);
		}
	}
	~Stack()
	{
		delete[] arr;
		size = 0;
		capacity = 0;
	}
private:
	T* arr;
	size_t size;
	size_t capacity;
};

int main()
{
	Stack<int>st;
	st.StackPush(1);
	st.StackPush(2);
	st.StackPush(3);
	st.StackPush(5);
	st.StackPush(4);
	st.StackPrint();
	st.StackPop();
	st.StackPrint();

	return 0;
}