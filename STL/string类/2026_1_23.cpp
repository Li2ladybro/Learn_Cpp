#include<iostream>
#include"string.h"
using namespace std;

int main()
{
	//s1 = "ftyr";
	//for (size_t i = 0; i < s1.size(); ++i)
	//	cout << s1[i] << ' ';
	//cout << endl;
	//for (size_t i = 0; i <s1.size(); ++i)
	//	s1[i]+=1;

	//for (size_t i = 0; i <s1.size(); ++i)
	//	cout << s1[i] << ' ';
	//cout << endl;

	//std::string s2;
	//for (size_t i = 0; i < s2.size(); ++i)
	//	cout << s1[i] << ' ';
	//cout << endl;
	//return  0;

	//string_2026_1_23::string s1("hellpi");

	//for (size_t i=0; i < s1.size(); i++)
	//{
	//	cout << s1[i]<<' ';
	//}
	// cout << endl;

	//string_2026_1_23::string::iterator it1 = s1.begin();

	//while (it1 != s1.end())
	//{
	//	*it1 += 1;
	//	++it1;
	//}

	//cout << s1;
	//cout << endl;

	//for (auto& e:s1)
	//	e -= 1;

	//cout << s1;
	//cout << endl;

	string_2026_1_23::string s = "hiqbq";
	s.push_back('c');
	cout << s << endl;
	s.append("bunmk,l");
	cout << s << endl;

	string_2026_1_23::string s1 = "hello";
	s1 += ' ';
	cout << s1;
	cout << endl;
	s1 += "world";
	cout << s1;
	cout << endl;

}
