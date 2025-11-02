#include "BitSet.h"
#include <time.h>
#include <algorithm>
#include <set>
int main()
{
	srand(time(NULL));
	vector<int> v;
	for (int i = 0; i < 1000; i++)
	{
		
		int num = rand()%1000;
		/*cout << num << " ";*/
		v.push_back(num);
	}

	BitSet bs(v,2000);
	set<int> s;
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		s.insert(*it);
		it++;
	}
	for (int i = 0; i < 1000; i++)
	{
		cout << i << ":";
		if (s.find(i) != s.end())
			cout << "v" << "->";
		if (bs.find(i))
			cout << "yes" << " ";
		else
			cout << "no" << " ";
		cout << endl;
	}
}