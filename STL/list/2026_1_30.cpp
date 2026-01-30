#include<iostream>
#include"list.h"

using namespace std;

void PrintList(const list_2026_1_29::list<int>& lt)
{
	list_2026_1_29::list<int>::const_iterator it = lt.begin();
	while (it != lt.end())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;

}
int main()
{
	list_2026_1_29::list<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);
	l1.push_back(6);
	l1.push_back(7);
	l1.push_back(8);
	l1.push_front(0);
	l1.push_front(-1);

	PrintList(l1);

	l1.pop_back();
	l1.pop_front();
	PrintList(l1);

	list_2026_1_29::list<int> l2(l1);
	PrintList(l2);

	list_2026_1_29::list<int> l3;
	l3.push_back(10);
	l3.push_back(20);
	l3.push_back(30);
	l3.push_back(40);
	l3 = l1;
	PrintList(l3);


	return 0;
}

