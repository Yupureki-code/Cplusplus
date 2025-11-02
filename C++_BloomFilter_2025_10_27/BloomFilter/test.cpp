#include "BloomFilter.h"
#include <map>
#include <time.h>
int main()
{
	srand(time(NULL));
	BloomFilter<1000> bf;
	map<int, string> m = { {0, "a"}, {1, "b"}, {2, "c"}, {3, "d"}, {4, "e"},
		{5, "f"}, {6, "g"}, {7, "h"}, {8, "i"}, {9, "j"},
		{10, "k"}, {11, "l"}, {12, "m"}, {13, "n"}, {14, "o"},
		{15, "p"}, {16, "q"}, {17, "r"}, {18, "s"}, {19, "t"},
		{20, "u"}, {21, "v"}, {22, "w"}, {23, "x"}, {24, "y"},
		{25, "z"} };
	for (int i = 0; i < 200; i++)
	{
		string s;
		for (int j = 0; j < 20; j++)
		{
			int num = rand() % 26;
			s += m[num];
		}
		cout << s<<endl;
		bf.insert(s);
	}
	for (int i = 0; i < 100; i++)
	{
		string s;
		for (int j = 0; j < 20; j++)
		{
			int num = rand() % 26;
			s += m[num];
		}
		cout << s << ":";
		if (bf.isexist(s))
			cout << "yes" << endl;
		else
			cout << "no" << endl;

	}
}