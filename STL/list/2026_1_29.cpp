#include<iostream>
#include"list.h"

using namespace std;

int main()
{
	list_2026_1_29::list<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);

	list_2026_1_29::list<int>::iterator it = l1.begin();
	while (it != l1.end())
	{
		cout << *it << ' '; it++;
	}

	cout << endl;

	return 0;
}

