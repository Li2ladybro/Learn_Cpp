#include <iostream>

#include "queue.h"

using namespace std;

int main()
{
	queue_2026_1_31::quequ<int, list<int>> qe;
	qe.push(1);
	qe.push(2);
	qe.push(3);
	qe.push(4);
	qe.push(5);
	qe.push(6);
	while (!qe.empty())
	{
		cout << qe.top() << ' ';
			qe.pop();
	}
	return 0;
}