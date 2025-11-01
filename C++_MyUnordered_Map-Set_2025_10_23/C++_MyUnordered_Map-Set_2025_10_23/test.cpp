#include "Unordered_Map.h"
#include "Unordered_Set.h"
#include <unordered_map>
#include <unordered_set>
#include <time.h>

void maptest()
{
	srand(time(NULL));
	Unordered_Map<int, int> mymap;
	unordered_map<int, int> stdmap;
	vector<int> v;
	int len = 10000000;
	for (int i = 0; i < len; i++)
	{
		const int num = rand();
		v.push_back(num);
	}

	int begin1 = clock();
	for (int i = 0; i < len; i++)
	{
		const int num = v[i];
		mymap.insert(num, 1);
	}
	int end1 = clock();
	cout << "mymap:" << end1 - begin1 << endl;

	int begin2 = clock();
	for (int i = 0; i < len; i++)
	{
		const int num = v[i];
		stdmap.insert({ num, 1 });
	}
	int end2 = clock();
	cout << "stdmap:" << end2 - begin2 << endl;
	return;
}

void settest()
{
	srand(time(NULL));
	Unordered_Set<int> mymap;
	unordered_set<int> stdmap;
	vector<int> v;
	int len = 1000000;
	for (int i = 0; i < len; i++)
	{
		const int num = rand();
		v.push_back(num);
	}

	int begin1 = clock();
	for (int i = 0; i < len; i++)
	{
		const int num = v[i];
		mymap.insert(num);
	}
	int end1 = clock();
	cout << "mymap:" << end1 - begin1 << endl;

	int begin2 = clock();
	for (int i = 0; i < len; i++)
	{
		const int num = v[i];
		stdmap.insert(num);
	}
	int end2 = clock();
	cout << "stdmap:" << end2 - begin2 << endl;
	return;
}

int main()
{
	maptest();
	settest();

}