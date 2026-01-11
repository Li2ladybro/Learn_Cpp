#include<iostream>
using namespace std;


class A1
{
	int a;
	char f;
};

class A2
{
	void add()
	{

	}
};

class A3
{
	
};


class Data
{
public:

	void Print()
	{
		cout << _year << '-' << _month << '-' << _day << endl;
	}

//	Data()
//	{
//		_year = 0;
//		_month = 1;
//		_day = 1;
//	}

	Data(int year=0, int month=1, int day=1)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	~Data()
	{

	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	//cout << sizeof(A1)<<endl;/*
	//cout << sizeof(A2) << endl;
	//cout << sizeof(A3) << endl;*/

	int arr[5] = { 2,3,4,5,6 };
	for (auto& e : arr)
	{
		cout << (e *= 2)<< endl;
	}
	cout << "______________________________" << endl;
	Data a(2026, 1, 11);
	a.Print();



	return 0;
}