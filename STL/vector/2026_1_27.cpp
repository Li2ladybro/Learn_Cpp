#include"vector.h"


int main()
{
	vector_2026_1_27::vector<int> v;

	v.reserve(5);

	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	for (auto& e : v)
		cout << e << ' ';
	cout << endl;
	return 0;

}
