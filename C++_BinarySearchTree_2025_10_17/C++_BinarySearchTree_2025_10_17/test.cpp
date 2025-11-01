#include "BinarySearchTree.h"
void Menu()
{
	printf("***************************************************\n");
	printf("****************BinarySearchTree*******************\n");
	printf("***  1.Insert(key,value)  2.erase(key)          ***\n");
	printf("***  3.find(key)                                ***\n");
	printf("***************************************************\n");
	printf("ÇëÊäÈë->");
}

int main()
{
	BSTree<int,int> s;
	int key, value,input;
	do {
		system("cls");
		s.Inorder();
		cout << endl;
		Menu();
		cin >> input;
		switch (input)
		{
		case 1:
			cin >> key>>value;
			s.insert(key, value);
			break;
		case 2:
			cin >> key;
			s.erase(key);
			break;
		case 3:
			cin >> key;
			s.find(key)->value++;
			break;
		case 0:
			break;
		}
	} while (input);
	return 0;
}