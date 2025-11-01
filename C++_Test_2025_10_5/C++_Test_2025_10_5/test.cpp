#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <assert.h>
using namespace std;

class Stack {
public:
	Stack(int n = 4)
	{
		_data = (int*)malloc(sizeof(int) * n);
		assert(_data);
		_size = 0;
		_capacity = n;
	}
	Stack(const Stack& st)
	{
		_data = (int*)malloc(sizeof(int) * st._capacity);
		assert(_data);
		_capacity = st._capacity;
		_size = st._size;
		memcpy(_data, st._data, sizeof(int) * st._capacity);
	}

	void StackCheck()
	{
		if (_size == _capacity)
		{
			_capacity *= 2;
			_data = (int*)realloc(_data, sizeof(int) * _capacity);
			assert(_data);
		}
	}
	void StackPush(int num)
	{
		StackCheck();
		_data[_size] = num;
		_size++;
	}
	int StackPop()
	{
		if (_size == 0)
		{
			cout << "栈中无数据" << endl;
			return 0;
		}
		int ret = _data[_size - 1];
		_size--;
		return ret;
	}
	int StackTop()
	{
		if (_size == 0)
		{
			cout << "栈中无数据" << endl;
			return 0;
		}
		return _data[_size - 1];
	}
	void StackPrint()
	{
		for (int i = 0; i < _size; i++)
		{
			printf("%d ", _data[i]);
		}
		printf("\n");
	}
	~Stack()
	{
		free(_data);
		_size = 0;
		_capacity = 0;
	}
private:
	int* _data;
	int _size;
	int _capacity;
};

int main()
{
	Stack st1;
	st1.StackPush(1);
	st1.StackPush(4);
	st1.StackPush(3);
	st1.StackPush(2);
	st1.StackPush(5);
	st1.StackPrint();
	Stack st2(st1);
	cout<<st2.StackPop()<<endl;
	st2.StackPrint();
	return 0;
}