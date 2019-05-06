#pragma once

#include <string>
#include <algorithm>

typedef std::string		String;

class StringIntegration
{
public:
	StringIntegration();
	StringIntegration(const String &str);
	//StringIntegration(StringIntegration &copy);
	~StringIntegration();
	//StringIntegration operator = (StringIntegration &copy);
	friend String operator + (const StringIntegration &str1,const StringIntegration &str2);
	friend String operator + (const StringIntegration &str1, const String &str2);
	friend String operator + (const String &str1, const StringIntegration &str2);
	StringIntegration & operator ++ ();
	StringIntegration operator ++ (int);
	friend String operator - (const StringIntegration &str1, const StringIntegration &str2);
	friend String operator - (const StringIntegration &str1, const String &str2);
	friend String operator - (const String &str1, const StringIntegration &str2);
	StringIntegration & operator -- ();
	StringIntegration operator -- (int);
	const String & string();
private:
	String s;
	int add(const String & s1, const String & s2, String & s,int minlen);
};

template<typename T>
inline void swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

