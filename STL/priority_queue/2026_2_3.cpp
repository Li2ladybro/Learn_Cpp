#include <iostream>
#include "priority_queue.h"

using namespace std;

int main()
{
	priority_queue_2026_2_3::priority_queue<int> pq;
	pq.push(1);
	pq.push(3);
	pq.push(2);
	pq.push(4);
	pq.push(-1);
	while (!pq.empty())
	{
		cout << pq.top() << ' ';
		pq.pop();
	}
	cout << endl;

	priority_queue_2026_2_3::priority_queue<int,vector<int>,greater<int>> pq1;
	pq1.push(1);
	pq1.push(3);
	pq1.push(2);
	pq1.push(4);
	pq1.push(-1);
	while (!pq1.empty())
	{
		cout << pq1.top() << ' ';
		pq1.pop();
	}
	cout << endl;
	return 0;
 }