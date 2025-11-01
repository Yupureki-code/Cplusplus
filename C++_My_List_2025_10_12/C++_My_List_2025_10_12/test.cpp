#include <list>
#include <iostream>
#include "List.h"
using namespace std;

void Menu()
{
	printf("***************************************************\n");
	printf("********************My_List************************\n");
	printf("***  1.push_back(n)      2.clear()              ***\n");
	printf("***  3.push_front(n)     4.pop_front()          ***\n");
	printf("***  5.pop_back()        6.pop(pos)             ***\n");
	printf("***  7.replace(pos,n)    8.resize(n)            ***\n");
	printf("***  9.insert(pos,n)                            ***\n");
	printf("***************************************************\n");
	printf("ÇëÊäÈë->");
}

int main()
{
	List<int> s;
	int input = 0;
	int npos = 0;
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
			cin >> n;
			s.push_front(n);
			break;
		case 4:
			s.pop_front();
			break;
		case 5:
			s.pop_back();
			break;
		case 6:
			cin >> npos;
			s.pop(npos);
			break;
		case 7:
			cin >> npos >> n;
			s.replace(npos, n);
			break;
		case 8:
			cin >> n;
			s.resize(n);
			break;
		case 9:
			cin >> npos >> n;
			s.insert(npos, n);
		}
	} while (input);
	return 0;
}