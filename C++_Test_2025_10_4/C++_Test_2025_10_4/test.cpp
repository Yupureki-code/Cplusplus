#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

namespace test {
	namespace test2 {
		int strlen = 5;
	}
	int rand = 10;
	int Add(int x = 1, int y = 2)
	{
		return x + y;
	}
	int main = 20;
	int a = 3;
}



int Add(int x = 1, int y = 2)
{
	return x + y;
}

double Add(double x = 1, double y = 2.2)
{
	return x + y;
}

int main()
{
	cout << Add(1, 2) << endl;
	cout << Add(3.3) << endl;
	return 0;
}


//int main()
//{
//	printf("%d", a);
//	test::rand += 1;
//	cout << test::rand << endl;
//	cout << test::test2::strlen << endl;
//	cout << test::main << " "<<test::Add(3,4) << endl;
//	cout << Add(10,10)<<" "<<Add(3.14, 5.20) << endl;
//	int a = 5;
//	int b = 7;
//	test1(a, b);
//	cout << a<<" "<<b << endl;
//	Print(a+b);
//	return 0;
//}