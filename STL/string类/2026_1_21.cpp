#include<iostream>
#include"string.h"
using namespace std;

int main()
{
	string_2026_1_21::string s1;
	for (size_t i = 0; i <s1.size(); ++i)
		cout << s1[i] << ' ';
	cout << endl;
	s1 = "ftyr";
	for (size_t i = 0; i < s1.size(); ++i)
		cout << s1[i] << ' ';
	cout << endl;
	for (size_t i = 0; i <s1.size(); ++i)
		s1[i]+=1;

	for (size_t i = 0; i <s1.size(); ++i)
		cout << s1[i] << ' ';
	cout << endl;

	std::string s2;
	for (size_t i = 0; i < s2.size(); ++i)
		cout << s1[i] << ' ';
	cout << endl;
	return  0;
}
