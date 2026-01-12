#include<iostream>
using namespace std;
//struct Data
//{
//	void add()
//	{
//
//	}
//};
//

class Data
{
public:
	void Print()
	{
		cout << _year << '-' << _month << '-' << _day << endl;
	}

	int GetMonthDay(int year,int month)
	{
		static int monthDays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
			return 29;
		return monthDays[month];
	}

	Data(int year = 0, int month = 1,int day = 1)
	{
		// 全缺省构造函数
		if(year>=0
			&&month<13&&month>0
			&&day<=GetMonthDay(year,month)&&day>0)
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "非法日期" << endl;
		}
	}

	Data(const Data& d)
	{
		// 拷贝构造函数
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	~Data()
	{
		// 析构函数
		_year = 0;
		_month = 1;
		_day = 1;
	}

	Data& operator =(const Data& d)
	{
		// 拷贝构造函数
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}


	bool operator == (const Data& d)
	{
		return _year == d._year
			&& _month == d._month
			&& _day == d._day;
	}

	bool operator !=(const Data& d)
	{
		return !(*this == d);
	}

	bool operator > (const Data& d)
	{
		if (_year > d._year)
		{
			return true;
		}
		else if (_year == d._year && _month > d._month)
		{
			return true;
		}
		else if (_year == d._year && _month ==d._month && _day > d._day)
		{
			return true;
		}
		return false;

		//return _year * 100 + _month * 10 + _day > d._year * 100 + d._month * 10 + d._day;
	}

	bool operator >=(const Data& d)
	{
		return *this > d || *this == d;
	}

	bool operator <(const Data& d)
	{
		return !(*this >= d);
	}

	bool operator <=(const Data& d)
	{
		return !(*this > d);
	}

	Data operator + (int day)
	{
		Data ret(*this);
		ret._day += day;
		while (ret._day > ret.GetMonthDay(ret._year, ret._month))
		{
			ret._day -= ret.GetMonthDay(ret._year, ret._month);
			ret._month += 1;
			if (ret._month > 13)
			{
				ret._year += 1;
				ret._month = 1;
			}
		}
		return ret;
	}
	
	Data& operator +=(int day)
	{
		_day += day;
		while (_day > (*this).GetMonthDay(_year, _month))
		{
			 _day -= (*this).GetMonthDay(_year, _month);
			 _month += 1;
			if ( _month > 13)
			{
				 _year += 1;
				 _month = 1;
			}
		}
		return *this;
	}

private:
	int _year;
	int _month;
	int _day;
};

int main()
{

	Data a1(2026,1,12);
	Data a2 = a1;
	cout << (a2 > a1)<<endl;
//	(a1 += 1100).Print();//

	(a1 += 110000).Print();
	a1.Print();
	return 0;
}