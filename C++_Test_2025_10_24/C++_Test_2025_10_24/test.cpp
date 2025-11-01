#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;



template<class T>
void func(T&& x)
{
	cout << x << endl;
}

class A{
public:
	A(int a = 1)
		:_a(a)
	{
		cout << "默认构造" << endl;
	}
	A(const A& _A)
	{
		_a = _A._a;
		cout << "拷贝构造" << endl;
	}

	A(A&& _A)
	{
		swap(_A);
		cout << "移动构造" << endl;
	}


	const A& operator=(const A& _A)
	{
		cout << "赋值构造" << endl;
	}

	void swap(A& _A)
	{
		_a = _A._a;
	}
	A& operator=(A&& _A)
	{
		swap(_A);
		cout << "移动赋值" << endl;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const A& obj)
	{
		out << obj._a << endl;
		return out;
	}

private:
	int _a;
};


template<class T>
void fun(T& a)
{
	cout << "左值"<<endl;
}

template<class T>
void fun(T&& a)
{
	cout << "右值" << endl;
}

template<class T>
void add(T&& a)
{
	fun(a);
	fun(forward<T>(a));
}

void test1()
{
	/*int a = 1;
	int b{ 2 };
	int& la = a;
	int&& ra = move(a);
	cout << a << " " << la << " " << ra << endl;*/

	/*A a1 = 1;
	A a2 = 2;
	a2 = move(a1);
	cout << a2 << endl;*/
	int a = 1;
	add(1);
	add(a);

	return;
}

void show()
{
	return;
}

template<class T,class ...Args>
void show(T t, Args... args)
{
	cout << t<<" ";
	show(args...);
}

template<class ...Args>
void Print(Args... args)
{
	show(args...);
}


void test2()
{
	/*Print(1, 1.23, "abcd");*/
	vector<pair<string,int>> v;
	v.emplace_back("apple",1);
	v.push_back({ "banana",2});
	//vector<int> v2;
	//v2.push_back(1);
	//v2.emplace_back(2);
	for (auto& it : v)
	{
		cout << it.first << ":"<<it.second << endl;
	}
	return;
}


void test3()
{
	
	auto func1 = [](int x, int y)->int {return x + y; };
	auto func2 = [](int x, int y)->int {return x - y; };
	auto func3 = [](int x, int y)->int {return x * y; };
	auto func4 = [](int x, int y)->int {return x / y; };
	function<int(int, int)> func[4] = { func1,func2,func3,func4 };
	vector<int> v = { 5,4,3,2,1 };
	sort(v.begin(), v.end(), [](int x, int y)->int {return x < y; });
	for (auto& it : v)
	{
		cout << it << " ";
	}
	cout << func[0](1, 2) << endl;
	return;
}
template<class X>
class cal {
public:
	X plus(X x, X y)
	{
		return x + y;
	}

	X del(X x, X y)
	{
		return x - y;
	}

	X mul(X x, X y)
	{
		return x * y;
	}

	X div(X x, X y)
	{
		return x / y;
	}

private:
};

using placeholders::_1; 
using placeholders::_2;
int main()
{
	/*cal<int> c;
	Print(c.plus(1, 2), c.del(1, 2), c.mul(1, 2), c.div(1, 2));
	function<int(int)> func[4] = { bind(&cal<int>::plus, &c, _1, 3),
		bind(&cal<int>::del, &c, _1, 3),bind(&cal<int>::mul, &c, _1, 3),
		bind(&cal<int>::div, &c, _1, 3) };
	Print(func[0](15), func[1](15), func[2](15), func[3](15));
	return 0;*/

	vector<int> v(1000);
}