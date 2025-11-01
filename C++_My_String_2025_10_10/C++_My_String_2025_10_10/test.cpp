#include <iostream>
#include <string>
#include "My_String.h"
#include "windows.h"
using namespace std;


void Menu()
{
	printf("***************************************************\n");
	printf("*******************My_String***********************\n");
	printf("***  1.push_back(ch)      2.append(str)         ***\n");
	printf("***  3.find(ch,pos)       4.find(str,pos)       ***\n");
	printf("***  5.insert(pos,ch)     6.insert(pos,str)     ***\n");
	printf("***  7.erase(pos,len)     8.clear()             ***\n");
	printf("***  9.resize(n)          10.reserve(n)         ***\n");
	printf("*** 11.operator=(str)                           ***\n");
	printf("***************************************************\n");
	printf("ÇëÊäÈë->");
}

int main()
{
	My_String s;
	int input = 0;
	char ch = 0;
	char* str = new char[100];
	int pos = 0;
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
			cin >> ch;
			s.push_back(ch);
			break;
		case 2:
			cin >> str;
			s.append(str);
			break;
		case 3:
			cin >> ch>>pos;
			cout<<s.find(ch, pos)<<endl;
			break;
		case 4:
			cin >> str >> pos;
			cout<<s.find(str, pos)<<endl;
			break;
		case 5:
			cin >> pos >> ch;
			s.insert(pos, ch);
			break;
		case 6:
			cin >> pos >> str;
			s.insert(pos, str);
			break;
		case 7:
			cin >> pos >> len;
			s.erase(pos, len);
			break;
		case 8:
			s.clear();
			break;
		case 9:
			cin >> n;
			s.resize(n);
			break;
		case 10:
			cin >> n;
			s.reserve(n);
			break;
		case 11:
			cin >> str;
			s = str;
			break;
		case 0:
			break;
		}
	} while (input);
	delete[] str;
	return 0;
}