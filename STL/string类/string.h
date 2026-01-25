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
//	//string(const char* s);
//
//	string(const char* s="");
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

		string(const char* s = "");
		~string();

		size_t size() const;
		size_t capacity() const;

		char& operator[](const size_t i);
		const char& operator[](const size_t i) const;

		const char* c_str() const;

		iterator begin();
		iterator end();

		void reserve(const size_t n); 
		void resize(const size_t n, const char ch = '\0');
		void push_back(const char ch);
		void append(const char* s);

		string& operator+=(const char ch);
		string& operator+=(const char* s);

		string& insert(const size_t pos,const char ch);
		string& insert(const size_t pos, const char* s);	    
		string& erase(size_t pos, size_t len= npose);

		size_t find(const char ch,const size_t pos=0) const;
		size_t find(const char* s,const size_t pos = 0) const;

		bool operator < (const string& s) const;
		bool operator == (const string& s) const;
		bool operator > (const string& s) const;

		bool operator <= (const string& s) const;
		bool operator >= (const string& s) const;

		bool operator != (const string& s) const;
		
		istream& getline(istream& in, string& s);


	private:
		char* _str;
		size_t  _size;			// 已经有几个有效字符
		size_t	_capacity;		// 可以存几个有效字符 ，'\0'不是有效字符
		static size_t npose;
	};

	ostream& operator << (ostream& out, const string_2026_1_23::string& s);
	istream& operator >> (istream& in, string_2026_1_23::string& s);

}


class String
{

public:
	String(const char* s="");

	// 传统写法
	//String(const String& s );
	//String& operator=(const String& s);

	// 现代写法
	String(const String& s);
	String& operator=(String s);

	~String();	
	char& operator[](const size_t i);

private:
	char* _str;
};
