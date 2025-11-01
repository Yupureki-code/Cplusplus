#include "MyMap.h"
#include "MySet.h"
#include <time.h>
void MyMapTest()
{
	Map<int,int> m;
	m.insert(1, 1);
	m.insert(2, 1);
	m.insert(3, 1);
	m.insert(7, 1);
	m.insert(8, 1);
	m.insert(4, 1);
	m.insert(5, 1);
	m.insert(6, 1);
	m.insert(10, 1);
	m.insert(9, 1);
	m[11] = 3;
	m.Print();
}

void MySetTest()
{
	srand(time(0));
	Set<int> s;
	for (int i = 0; i < 100; i++)
	{
		int num = rand() % 100;
		s.insert(num);
	}
	s.Print();
}

int main()
{
	MySetTest();
	/*MyMapTest();*/
}