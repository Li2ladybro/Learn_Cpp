#pragma once
#include<iostream>
using namespace std;

class Data
{

public:
	void Print() const;
	int GetMonthDay(int year, int month) const;
	Data(int year = 0, int month = 1, int day = 1); // 全缺省构造函数
	Data(const Data& d);							// 拷贝构造函数
	~Data();										// 析构函数
	Data& operator =(const Data& d);				// 赋值运算符重载
	Data* operator&();								// 取地址重载
	const Data* operator&()const;					// const取地址重载
	bool operator == (const Data& d) const;
	bool operator !=(const Data& d) const;
	bool operator > (const Data& d) const;
	bool operator >=(const Data& d) const;
	bool operator <(const Data& d) const;
	bool operator <=(const Data& d) const;
	Data operator + (const int day) const;
	Data& operator +=(const int day);
	Data operator -(const int day) const;
	Data& operator -=(const int day);
	Data& operator ++();							// 默认后置++
	Data operator ++(int);
	Data& operator --();							// 默认后置--
	Data operator --(int);
	int operator -(const Data& d) const;

private:
	int _year;
	int _month;
	int _day;
};
