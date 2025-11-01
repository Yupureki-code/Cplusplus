#include <iostream>
using namespace std;

class A {
public :
	A()
	:a(2)
	{
		test();
	}
	virtual void test()
	{
		cout << "A::a = " << a << endl;
		cout << "A::test()" << endl;
	}
protected:
	int a;
};

class B :public A {
public:
	B()
	{
		test();
	}
	virtual void test()
	{
		a++;
		cout << "B::a = " << a << endl;
		cout << "B::test()" << endl;
	}
	/*int a = 1;*/
};


int main()
{
	A* a = new A;
	a->test();
	return 0;
}