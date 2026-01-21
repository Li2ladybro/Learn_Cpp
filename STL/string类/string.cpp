#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

#include"string.h"

//string_2026_1_21::string::string()
//	:_str(new char[1])
//{
//	_str = '\0';
//}
//
//string_2026_1_21::string::string(const char* str)
//	:_str(new char[strlen(str)+1])
//{
//	strcpy(_str, str);
//}

// 默认构造函数
string_2026_1_21::string::string(const char* str)
	:_str(new char[strlen(str) + 1])
{
	strcpy(_str, str);
}

// 拷贝构造
string_2026_1_21::string::string(const string& s)
	:_str(new char[strlen(s._str)+1])
{
	strcpy(_str, s._str);
}

// 析构
string_2026_1_21::string::~string()
{
	delete[] _str;
	_str = nullptr;
}

// 赋值
string_2026_1_21::string& string_2026_1_21::string::operator = (const string& s)
{
	if (this != &s)
	{
		char* tmp = new char[strlen(s._str) + 1];
		strcpy(tmp, s._str);
		delete[] _str;
		_str = tmp;
	}
	return *this;
}

char& string_2026_1_21::string::operator[](const size_t i)
{
	return _str[i];
}

size_t string_2026_1_21::string::size() const
{
	return strlen(_str);
}
	


//
//
//string_2026_1_21::string::string_2026_1_21::string::
//string_2026_1_21::string::
//
