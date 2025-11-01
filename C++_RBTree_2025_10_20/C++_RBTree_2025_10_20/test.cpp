#include "RBTree.h"


void Menu()
{
	printf("***************************************************\n");
	printf("********************AVLTree************************\n");
	printf("***  1.Insert(key,value)  2.erase(key)          ***\n");
	printf("***  3.find(key)->value                         ***\n");
	printf("***************************************************\n");
	printf("ÇëÊäÈë->");
}


void AutoTest()
{
	RBTree<int, int> s;
	int key, value, input;
	do {
		system("cls");
		s.PrintHorizontal();
		cout << endl;
		cout << "size:" << s.size() << " maxheight:" << s.maxheight() << " minheight:" << s.minheight() << endl;
		if (s.Check())
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
		Menu();
		cin >> input;
		switch (input)
		{
		case 1:
			cin >> key >> value;
			s.Insert(key, value);
			break;
			/*case 2:
				cin >> data;
				s.erase(data);
				break;*/
		case 3:
			cin >> key>>value;
			s.find(key)->_kv.second = value;
			break;
		case 0:
			break;
		}
	} while (input);
}

void UnAutoTest()
{
	RBTree<int,int> s;
	srand(time(0));
	for (int i = 0; i < 1000; i++)
	{
		int num = rand() % 1000;
		s.Insert(num,1);
	}
	s.PrintHorizontal();
	cout << "size:" << s.size() << " maxheight:" << s.maxheight() << " minheight:" << s.minheight()<< endl;
	cout << "BlackNums:"<<s.BlackCount() << endl;
	if (s.Check())
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
}

int main()
{
	UnAutoTest();
	return 0;
}
