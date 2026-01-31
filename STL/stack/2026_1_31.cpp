#include <iostream>

#include "stack.h"

using namespace std;

int main()
{
	//stack_2026_1_31::stack<int,list<int>> sk;
	stack_2026_1_31::stack<int, vector<int>> sk;

	sk.push(2);
	sk.push(3);
	sk.push(4);
	sk.push(5);
	while (!sk.empty())
	{
		cout << sk.top()<<' ';
		sk.pop();
	}

	return 0;
}