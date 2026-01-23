#include"string.h"

//
////string_2026_1_21::string::string()
////	:_str(new char[1])
////{
////	_str = '\0';
////}
////
////string_2026_1_21::string::string(const char* str)
////	:_str(new char[strlen(str)+1])
////{
////	strcpy(_str, str);
////}
//
//// 默认构造函数
//string_2026_1_21::string::string(const char* str)
//	:_str(new char[strlen(str) + 1])
//{
//	strcpy(_str, str);
//}
//
//// 拷贝构造
//string_2026_1_21::string::string(const string& s)
//	:_str(new char[strlen(s._str)+1])
//{
//	strcpy(_str, s._str);
//}
//
//// 析构
//string_2026_1_21::string::~string()
//{
//	delete[] _str;
//	_str = nullptr;
//}
//
//// 赋值
//string_2026_1_21::string& string_2026_1_21::string::operator = (const string& s)
//{
//	if (this != &s)
//	{
//		char* tmp = new char[strlen(s._str) + 1];
//		strcpy(tmp, s._str);
//		delete[] _str;
//		_str = tmp;
//	}
//	return *this;
//}
//
//char& string_2026_1_21::string::operator[](const size_t i)
//{
//	return _str[i];
//}
//
//size_t string_2026_1_21::string::size() const
//{
//	return strlen(_str);
//}
//
//
//string_2026_1_21::string::string_2026_1_21::string::
//string_2026_1_21::string::




namespace string_2026_1_23
{
	ostream& operator<< (ostream& out, const string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
			out << s[i] << ' ';
		return out;
	}

	size_t string::npose = -1;

	string::string(const char* str)
		:_str(new char[strlen(str) + 1])  // '\0'，不是有效字符，+1给 '\0'
		, _size(strlen(str))
		, _capacity(_size)
	{
		strcpy(_str, str);
	}

	string:: ~string()
	{
		delete[] _str;
		_str = nullptr;
		_size = _capacity = 0;
	}

	size_t string_2026_1_23::string::size() const
	{
		return _size;
	}

	size_t string::capacity() const
	{
		return _capacity;
	}

	char& string:: operator[](const size_t i)
	{
		assert(i < _size);
		return _str[i];
	}

	const char& string:: operator[](const size_t i) const
	{
		assert(i < _size);
		return _str[i];
	}

	const char* string::c_str()
	{
		return _str;
	}

	string::iterator string::begin()
	{
		return _str;
	}

	string::iterator string::end()
	{
		return _str + _size;
	}

	void string::reserve(const size_t n)
	{
		if (n > _capacity)
		{
			char* newstr = new char[n + 1]; // 多开一个给'\0'不是有效字符
			strcpy(newstr, _str);
			delete[] _str;
			_str = newstr;
			_capacity = n;
		}
	}

	void string::push_back(const char ch)
	{
		if (_size == _capacity)
		{
			size_t newcapacity = _size == 0 ? 2 : _capacity * 1.5;
			reserve(newcapacity);
		}
		_str[_size++] = ch;
		_str[_size] = '\0';
	}

	void string::append(const char* str)
	{
		if (_size + strlen(str) > _capacity)
		{
			size_t newcapacity = _size + strlen(str);
			reserve(newcapacity);
		}
		strcpy(_str + _size, str);
		_size += strlen(str);
	}

	string& string::operator+=(const char ch)
	{
		this->push_back(ch);
		return *this;
	}

	string& string::operator+=(const char* str)
	{
		this->append(str);
		return *this;
	}

	//string_2026_1_23::string::
	//string_2026_1_23::string::
	//string_2026_1_23::string::

}