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

	size_t string::size() const
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

	const char* string::c_str() const
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

	// 只修改容量_capacity
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

	// 修改_size;
	void string::resize(const size_t n, const char ch)
	{
		if (n < _size)
		{
			_str[n] = '\0';
			_size = n;
		}

		if (n > _size)
		{
			if (n > _capacity)
				reserve(n);
			for (size_t i = _size; i < n; ++i)
				_str[i] = ch;
			_str[n] = '\0';
			_size = n;
		}
	}

	void string::push_back(const char ch)
	{
		//if (_size == _capacity)
		//{
		//	size_t newcapacity = _size == 0 ? 2 : _capacity * 1.5;
		//	reserve(newcapacity);
		//}
		//_str[_size++] = ch;
		//_str[_size] = '\0';
		insert(_size,ch);
	}

	void string::append(const char* str)
	{
		//if (_size + strlen(str) > _capacity)
		//{
		//	size_t newcapacity = _size + strlen(str);
		//	reserve(newcapacity);
		//}
		//strcpy(_str + _size, str);
		//_size += strlen(str);
		insert(_size, str);
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

	string& string::insert(const size_t pos, const char ch)
	{
		assert(pos <= _size);
		if (_size == _capacity)
		{
			size_t newcappacity = _size == 0 ? 2 : _capacity * 1.5;
			reserve(newcappacity);
		}
		int end = _size;
		while (end >= (int)pos)
		{
			_str[end + 1] = _str[end];
			--end;
		}

		_str[pos] = ch;
		_size += 1;
		return *this;
	}

	string& string::insert(const size_t pos, const char* str)
	{
		assert(pos <= _size);
		size_t len = strlen(str);
		
		if (_size+ len > _capacity)
			reserve(_size + len);
	
		int end = _size;
		const char ch = _str[pos];
		while (end >= (int)pos)
		{
			_str[end + len] = _str[end];
			--end;
		}
		strncpy(_str + pos, str,len);
		_size += len;
		return *this;
	}

	string& string::erase(size_t pos, size_t len )
	{
		assert(pos < _size);

		if (len >= _size - pos)
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			size_t i = pos+len;
			while (i<=_size )
			{
				_str[i-len ] = _str[i];
				++i;
			}
			_size -= len;
		}
		return *this;
	}

	size_t string::find(const char ch, const size_t pos) const
	{
		assert(pos < _size);

		for (size_t i = pos; i < _size; ++i)
			if (_str[i] == ch)
				return i;
		return npose;
	}

	size_t string::find(const char* str, const size_t pos) const
	{
		assert(pos < _size);
		char* p = strstr(_str+ pos, str);
		if (p == nullptr)
			return npose;
		return p - _str;
	}

	bool string::operator < (const string& s) const
	{
		int ret =strcmp(_str, s._str);
		return ret < 0;
	}

	bool string::operator == (const string& s) const
	{
		int ret = strcmp(_str, s._str);
		return ret == 0;
	}

	bool string::operator > (const string& s) const
	{
		return !(*this < s || *this == s);

	}

	bool string::operator <= (const string& s) const
	{
		return !(*this > s);
	}

	bool string::operator >= (const string& s) const
	{
		return !(*this < s);
	}

	bool string::operator != (const string & s) const
	{
		return !(*this == s);
	}

	istream& string::getline(istream& in, string& s)
	{
		while (1)
		{
			char hc;
			hc = in.get();

			if (hc == '\n')
				break;
			else
				s += hc;
		}
		return in;
	}

	ostream& operator << (ostream& out, const string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
			out << s[i] << ' ';
		return out;
	}

	istream& operator >> (istream& in, string_2026_1_23::string& s)
	{
		while (1)
		{
			char hc;
			hc=in.get();

			if (hc == ' ' || hc == '\n')
				break;
			else
				s += hc;
		}
		return in;
	}

}




String::String(const char* s )
	:_str(new char[strlen(s)+1])
{
	strcpy(_str, s);
}

// 传统写法
//String::String(const String& s )
//	:_str(new char[strlen(s._str) + 1])
//{
//	strcpy(_str, s._str);
//}
//
//String& String::operator=(const String& s)
//{
//	if (this != &s)
//	{
//		delete[] _str;
//		_str = new char[strlen(s._str) + 1];
//		strcpy(_str, s._str);
//	}
//	return *this;
//}

// 现代写法
String::String(const String& s)
	:_str(nullptr)
{
	String tmp(s._str);
	swap(_str, tmp._str);
}

String& String::operator=(String s)
{
	swap(_str, s._str);
	cout << _str;
	return *this;

}

String::~String()
{
	delete[] _str;
	_str = nullptr;
}


char& String::operator[](const size_t i)
{
	return _str[i];
}
