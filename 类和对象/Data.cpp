#include"Data.h"

ostream& operator << (ostream& out, const Data& d)
{
	out << d._year << '-' << d._month << '-' << d._day;
	return out;
}

istream& operator >> (istream& in,  Data& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}

int Data::GetMonthDay(int year, int month) const
{
	static int monthDays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		return 29;
	return monthDays[month];
}

Data::Data(int year, int month , int day )
	:_year(year)
	,_month(month)
	,_day(day)
{
	// 全缺省构造函数
	if (year >= 0
		&& month < 13 && month>0
		&& day <= GetMonthDay(year, month) && day > 0)
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

Data::Data(const Data& d)
{
	// 拷贝构造函数
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

Data::~Data()
{
	// 析构函数
	_year = 0;
	_month = 1;
	_day = 1;
}

Data& Data::operator =(const Data& d)
{
	// 赋值运算符重载
	if (this != &d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	return *this;
}

Data* Data::operator&()
{
	// 取地址重载
	return nullptr;

}

const Data* Data::operator&() const
{
	// const取地址重载
	return nullptr;
}

bool Data::operator == (const Data& d) const
{
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}

bool Data::operator !=(const Data& d) const
{
	return !(*this == d);
}

bool Data::operator > (const Data& d) const
{
	if (_year > d._year)
	{
		return true;
	}
	else if (_year == d._year && _month > d._month)
	{
		return true;
	}
	else if (_year == d._year && _month == d._month && _day > d._day)
	{
		return true;
	}
	return false;
	//return _year * 100 + _month * 10 + _day > d._year * 100 + d._month * 10 + d._day;
}

bool Data::operator >=(const Data& d) const
{
	return *this > d || *this == d;
}

bool Data::operator <(const Data& d) const
{
	return !(*this >= d);
}

bool Data::operator <=(const Data& d) const
{
	return !(*this > d);
}

Data Data::operator + (const int day) const
{
	// 复用
	Data ret(*this);
	//		ret._day += day;
	//		while (ret._day > ret.GetMonthDay(ret._year, ret._month))
	//		{
	//			ret._day -= ret.GetMonthDay(ret._year, ret._month);
	//			ret._month += 1;
	//			if (ret._month > 13)
	//			{
	//				ret._year += 1;
	//				ret._month = 1;
	//			}
	//		}
	//		return ret;
	return ret += day;
}

Data& Data::operator +=(const int day)
{
	if (day < 0)
	{
		return *this -= -day;
	}

	_day += day;
	while (_day > (*this).GetMonthDay(_year, _month))
	{
		_day -= (*this).GetMonthDay(_year, _month);
		_month += 1;
		if (_month > 13)
		{
			_year += 1;
			_month = 1;
		}
	}
	return *this;
}

Data Data::operator -(const int day) const
{
	// 复用
	Data ret(*this);
	//		ret._day -= day;
	//		while (ret._day < 1)
	//		{
	//			ret._month-=1;
	//			if (ret._month ==0)
	//			{
	//				ret._year -= 1;
	//				ret._month = 12;
	//			}
	//			ret._day += ret.GetMonthDay(ret._year, ret._month);
	//		}
	//		return ret;
	return ret -= day;
}

Data& Data::operator -=(const int day)
{
	_day -= day;
	while (_day < 1)
	{
		_month -= 1;
		if (_month == 0)
		{
			_year -= 1;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}

Data& Data::operator ++()
{
	// 默认后置++
	return *this += 1;
}

Data Data::operator ++(int)
{
	Data tmp(*this);
	*this += 1;
	return tmp;
}

Data& Data::operator --()
{
	// 默认后置--
	return *this -= 1;
}

Data Data::operator --(int)
{
	Data tmp(*this);
	*this -= 1;
	return tmp;
}

int Data::operator -(const Data& d) const
{
	int flag = 1;
	Data max = *this;
	Data min = d;
	if (max < min)
	{
		max = d;
		min = *this;
		flag = -1;
	}
	int count = 0;
	while (max != min)
	{
		++min;
		++count;
	}
	return count * flag;
}

