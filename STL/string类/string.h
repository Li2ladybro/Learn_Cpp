#pragma once

namespace string_2026_1_21
{
	class string
{
public:

	//string();
	//string(const char* str);

	string(const char* str="");
	string(const string& s);
	~string();
	string& operator = (const string& s);

	char& operator[](const size_t i);
	size_t size() const;

private:
	char* _str;
 };
}