#include "Vector.h"

void Menu()
{
	printf("***************************************************\n");
	printf("*******************My_Vector***********************\n");
	printf("***  1.push_back(ch)      2.clear()             ***\n");
	printf("***  3.insert(pos,n)      4.erase(pos)          ***\n");
	printf("***  5.resize(n)          6.reserve(n)          ***\n");
	printf("***  7.replace(pos,n)                           ***\n");
	printf("***************************************************\n");
	printf("ÇëÊäÈë->");
}

void AutoTest()
{
	My_Vector<int> s(0);
	int input = 0;
	char ch = 0;
	char* str = new char[100];
	int npos = 0;
	My_Vector<int>::iterator pos = nullptr;
	int len = 0;
	int n = 0;
	do {
		system("cls");
		s.Print();
		Menu();
		cin >> input;
		switch (input)
		{
		case 1:
			cin >> n;
			s.push_back(n);
			break;
		case 2:
			s.clear();
			break;
		case 3:
			cin >> npos >> n;
			pos = s.begin() + npos;
			s.insert(pos, n);
			break;
		case 4:
			cin >> npos;
			pos = s.begin() + npos - 1;
			s.erase(pos);
			break;
		case 5:
			cin >> len;
			s.resize(len);
			break;
		case 6:
			cin >> len;
			s.reserve(len);
			break;
		case 7:
			cin >> npos >> n;
			pos = s.begin() + npos - 1;
			s.replace(pos, n);
			break;
		case 0:
			break;
		}
	} while (input);
	delete[] str;
	return;
}

void UnAutoTest()
{
	My_Vector<string> v(5, "abcdef");
	v.Print();
	My_Vector<My_Vector<string>> vv(10,v);
	for (int i = 0; i < vv.size(); i++)
	{
		vv[i].Print();
	}
}

int main()
{
	UnAutoTest();
}