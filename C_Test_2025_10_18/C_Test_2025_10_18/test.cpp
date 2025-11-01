#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void test1()
{
	/*string s("abcdefasdd");
	string::iterator it = s.begin();
	int len = 0;
	while (it != s.end())
	{
		int tmp = s.find(*it, it - s.begin() + 1);
		if (tmp > len)
		{
			len = tmp;
		}
		it++;
	}
	cout << len;*/
	vector<string> v{"xdpple","bed","cdasd","dasfas"};
	map<string, int> m;
	vector<string>::iterator iv = v.begin();
	while (iv != v.end())
	{
		m.insert({ *iv,1 });
		iv++;
	}
	map<string, int>::iterator im = m.begin();
	vector<pair<string, int>> ret(m.begin(),m.end());
	vector<pair<string, int>>::iterator ir = ret.begin();
	//sort(ret.begin(), ret.end());
	while (ir != ret.end())
	{
		cout << ir->first << " " << ir->second << endl;
		ir++;
	}
	if (ret[0].first > ret[1].first)
	{
		cout << "yes";
	}
	else
	{
		cout << "no";
	}

	return;
}


void friendfunc()
{
	cout << "friendfunc" << endl;
}

class Person {
	friend void friendfunc();
protected:
	string _name = "zhangsan";
public:
	static int id;
	void identity() {
		cout << "身份验证: " << _name << endl;
	}
};

int Person::id = 123456;

class Student : public Person {
protected:
	int _stuNum;
	string _name = "lisi";

public:
	void identity() {
		cout << "身份验证: " << _name << endl;
	}

	void PersonPrint()
	{
		identity();
		Person::identity();
		cout << _name << endl;
	}

	void study() {
		cout << _name << "正在学习" << endl;
	}
};

//int main()
//{
//	Student s;
//	Person p;
//	cout << s.id << endl;
//	cout << p.id << endl;
//
//	s.PersonPrint();
//}

class Base
{
public:
	virtual void Func1()
	{
		cout << "Func1()" << endl;
	}
protected:
	int _b = 1;
	char _ch = 'x';
};
int main()
{
	Base b;
	cout << sizeof(b) << endl;
	return 0;
}