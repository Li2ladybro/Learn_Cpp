#include "vector.h"

//template <class T>
//void print_Vector(const vector_2026_1_27::vector<T>& v)
//{
//	vector_2026_1_27::vector<T>::const_iterator it = v.begin();
//	while (it != v.end())
//	{
//		cout << *it << ' ';
//		++it;
//	}
//	cout << endl;
//}

//template <class T>
//void erase_even_Vector_E(vector_2026_1_27::vector<T>& v)
//{
//	vector_2026_1_27::vector<T>::iterator it = v.begin();
//	while (it != v.end())
//	{
//		if ((*it) % 2 == 0)
//		{
//			it = v.erase(it);
//		}
//		else
//			++it;
//	}
//}

int main()
{
	vector_2026_1_27::vector<int> v;
	//cout << v.size() << ' ' << endl;

	v.reserve(5);
	cout << "size()=" << v.size() << ' ' << "capacity()=" << v.capacity() << ' ' << endl;

	v.push_back(1);
	cout << "size()=" << v.size() << ' ' << "capacity()=" << v.capacity() << ' ' << endl;

	v.push_back(2);
	cout << "size()=" << v.size() << ' ' << "capacity()=" << v.capacity() << ' ' << endl;

	v.push_back(3);
	cout << "size()=" << v.size() << ' ' << "capacity()=" << v.capacity() << ' ' << endl;

	v.push_back(4);
	cout << "size()=" << v.size() << ' ' << "capacity()=" << v.capacity() << ' ' << endl;

	v.push_back(5);
	cout << "size()=" << v.size() << ' ' << "capacity()=" << v.capacity() << ' ' << endl;

	v.push_back(6);
	cout << "size()=" << v.size() << ' ' << "capacity()=" << v.capacity() << ' ' << endl;

	v.push_back(7);
	cout << "size()=" << v.size() << ' ' << "capacity()=" << v.capacity() << ' ' << endl;

	for (auto& e : v)
		cout << e << ' ';
	cout << endl;

	//erase_even_Vector_E(v);
	//print_Vector(v);

	//for (auto& e : v)
	//	cout << e << ' ';
	//cout << endl;

	//for (size_t i = 0; i < v.size(); ++i)
	//	cout << v[i] << ' ';
	//cout << endl;

	v.resize(4);
	print_Vector(v);
	cout << "size()=" << v.size() << ' ' << "capacity()=" << v.capacity() << ' ' << endl;
	v.resize(8,4);
	print_Vector(v);
	cout << "size()=" << v.size() << ' ' << "capacity()=" << v.capacity() << ' ' << endl;
	v.resize(19,45);
	print_Vector(v);
	cout << "size()=" << v.size() << ' ' << "capacity()=" << v.capacity() << ' ' << endl;

	vector_2026_1_27::vector<int> v1(v);

	print_Vector(v1);
	vector_2026_1_27::vector<int> v2;
	v2.resize(3, 6);
	print_Vector(v2);

	v = v2;
	print_Vector(v);

	vector_2026_1_27::vector<string> v3;
	v3.push_back("1111111111111111111");
	v3.push_back("2222222222222222222");
	v3.push_back("3333333333333333333");
	v3.push_back("4444444444444444444");
	//print_Vector(v3);

	return 0;
}
