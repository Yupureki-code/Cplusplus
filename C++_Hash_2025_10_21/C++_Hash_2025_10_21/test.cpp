#include "Hash.h"
#include "time.h"

void Menu()
{
	printf("***************************************************\n");
	printf("******************HashTable************************\n");
	printf("***  1.Insert(key,value)  2.erase(key)          ***\n");
	printf("***  3.find(key)->value   4.[key] = value       ***\n");
	printf("***************************************************\n");
	printf("ÇëÊäÈë->");
}

void UnAutoTest()
{
	HashTable<int, int> hash;
	srand(time(NULL));

	int begin = clock();
	for (int i = 0; i < 1500;i++)
	{
		int num = rand() % 1000;
		hash.insert({ num, 1 });
	}
	int end = clock();
	cout << endl << end - begin;
	hash.Print();
}

void AutoTest()
{
	HashTable<int, int> s;
	int key, value, input;
	do {
		system("cls");
		s.Print();
		cout << endl;
		Menu();
		cin >> input;
		switch (input)
		{
		case 1:
			cin >> key >> value;
			s.insert({ key, value });
			break;
		case 2:
			cin >> key;
			s.erase(key);
			break;
		case 3:
			cin >> key;
			cout << s.find(key)->second;
			break;
		case 4:
			cin >> key >> value;
			s[key] = value;
			break;
		case 0:
			break;
		}
	} while (input);
}

int main()
{
	UnAutoTest();
}