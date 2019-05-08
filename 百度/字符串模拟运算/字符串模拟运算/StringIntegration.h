#pragma once

#include <string>
#include <vector>
#include <algorithm>

typedef std::string			String;
typedef std::vector<String> StringBuffer;

class StringIntegration
{
public:
	StringIntegration();
	StringIntegration(const String &str);
	//StringIntegration(StringIntegration &copy);
	~StringIntegration();
	//StringIntegration operator = (StringIntegration &copy);
	friend StringIntegration operator + (const StringIntegration &str1,const StringIntegration &str2);
	friend StringIntegration operator + (const StringIntegration &str1, const String &str2);
	friend StringIntegration operator + (const String &str1, const StringIntegration &str2);
	StringIntegration & operator ++ ();
	StringIntegration operator ++ (int);
	StringIntegration & operator += (const String &str);
	StringIntegration & operator += (const StringIntegration &str);
	friend StringIntegration operator - (const StringIntegration &str1, const StringIntegration &str2);
	friend StringIntegration operator - (const StringIntegration &str1, const String &str2);
	friend StringIntegration operator - (const String &str1, const StringIntegration &str2);
	StringIntegration & operator -- ();
	StringIntegration operator -- (int);
	StringIntegration & operator -= (const String & str);
	StringIntegration & operator -= (const StringIntegration & str);
	friend StringIntegration operator * (const StringIntegration &str1, const StringIntegration &str2);
	friend StringIntegration operator * (const StringIntegration &str1, const String &str2);
	friend StringIntegration operator * (const String &str1, const StringIntegration &str2);
	StringIntegration & operator *= (const String &str);
	StringIntegration & operator *= (const StringIntegration &str);
	friend StringIntegration operator / (const StringIntegration &str1, const StringIntegration &str2);
	friend StringIntegration operator / (const StringIntegration &str1, const String &str2);
	friend StringIntegration operator / (const String &str1, const StringIntegration &str2);

	friend bool operator > (const StringIntegration &str1, const StringIntegration &str2);
	friend bool operator > (const String &str1, const StringIntegration &str2);
	friend bool operator > (const StringIntegration &str1, const String &str2);
	friend bool operator < (const StringIntegration &str1, const StringIntegration &str2);
	friend bool operator < (const String &str1, const StringIntegration &str2);
	friend bool operator < (const StringIntegration &str1, const String &str2);
	friend bool operator == (const StringIntegration &str1, const StringIntegration &str2);
	friend bool operator == (const String &str1, const StringIntegration &str2);
	friend bool operator == (const StringIntegration &str1, const String &str2);
	friend bool operator >= (const StringIntegration &str1, const StringIntegration &str2);
	friend bool operator >= (const String &str1, const StringIntegration &str2);
	friend bool operator >= (const StringIntegration &str1, const String &str2);
	friend bool operator <= (const StringIntegration &str1, const StringIntegration &str2);
	friend bool operator <= (const String &str1, const StringIntegration &str2);
	friend bool operator <= (const StringIntegration &str1, const String &str2);
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

