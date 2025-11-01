#include "AVLTree.h"
#include <vector>
#include <time.h>
#include <algorithm>

void Menu()
{
	printf("***************************************************\n");
	printf("********************AVLTree************************\n");
	printf("***  1.Insert(key,value)  2.erase(key)          ***\n");
	printf("***  3.find(key)                                ***\n");
	printf("***************************************************\n");
	printf("ÇëÊäÈë->");
}


void AutoTest()
{
	AVLTree<int> s;
	int data, input;
	do {
		system("cls");
		s.PrintHorizontalPretty();
		cout << endl;
		cout << "size:" << s.size() << " height:" << s.height() << endl;
		Menu();
		cin >> input;
		switch (input)
		{
		case 1:
			cin >> data;
			s.Insert(data);
			break;
		case 2:
			cin >> data;
			s.erase(data);
			break;
		case 3:
			cin >> data;
			s.find(data);
			break;
		case 0:
			break;
		}
	} while (input);
}

void UnAutoTest()
{
	AVLTree<int> s;
	srand(time(0));
	for (int i = 0; i < 100; i++)
	{
		int num = rand() % 100;
		s.Insert(num);
	}
	s.PrintHorizontalPretty();
	cout << "size:" << s.size() << " height:" << s.height() << endl;
}

int main()
{
	UnAutoTest();
}