#include<iostream>
using namespace std;

int main()
{
	size_t size = 1;
	//void* ptr = malloc(1024 * 1024 * 1024 *2* size);
	//void* ptr1 = operator new(1024 * 1024 * 1024 * 2 * size);
	//cout << ptr << endl;
	//cout << ptr1<< endl;
	void* ptr = new char[size * 4* 1024 * 1024 * 1024];
	cout << ptr << endl;

	void* ptr1 = new char[size * 4 * 1024 * 1024 * 1024];
	cout << ptr1 << endl;

	void* ptr2= new char[size * 4 * 1024 * 1024 * 1024];
	cout << ptr2 << endl;

	void* ptr3 = new char[size * 4 * 1024 * 1024 * 1024];
	cout << ptr3 << endl;
	int a;
	cin >> a;

	void* ptr4 = new char[size * 4 * 1024 * 1024 * 1024];
	cout << ptr4<<endl;

	return  0;
}