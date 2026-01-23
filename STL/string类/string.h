#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<assert.h>
#include"string.h"
using namespace std;

//namespace string_2026_1_21
//{
//	class string
//{
//public:
//
//	//string();
//	//string(const char* str);
//
//	string(const char* str="");
//	string(const string& s);
//	~string();
//	string& operator = (const string& s);
//
//	char& operator[](const size_t i);
//	size_t size() const;
//
//private:
//	char* _str;
// };
//}

namespace string_2026_1_23
{
	class string
	{
	public:

		typedef char* iterator;

		string(const char* str = "");
		~string();
		size_t size() const;
		size_t capacity() const;
		char& operator[](const size_t i);
		const char& operator[](const size_t i) const;
		const char* c_str();
		iterator begin();
		iterator end();
		void reserve(const size_t n);
		void push_back(const char ch);
		void append(const char* str);
		string& operator+=(const char ch);
		string& operator+=(const char* str);


	private:
		char* _str;
		size_t  _size;			// 已经有几个有效字符
		size_t	_capacity;		// 可以存几个有效字符 ，'\0'不是有效字符
		static size_t npose;
	};
	ostream& operator <<(ostream& out, const string_2026_1_23::string& s);
}
