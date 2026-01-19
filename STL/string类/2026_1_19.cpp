#include<iostream>
#include<string>
using namespace std;

int main()
{
	string s1(5, 't');
	cout << s1 << endl;
	string::iterator it = s1.begin();
	
	cout << sizeof(it) <<endl;

	return  0;
}