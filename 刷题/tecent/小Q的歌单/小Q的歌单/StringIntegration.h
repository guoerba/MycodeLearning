#pragma once

#include <string>
#include <vector>
#include <algorithm>

#define SIDLL	__declspec(dllexport)

typedef std::string			String;
typedef std::vector<String> StringBuffer;
//友元函数不在类的作用域，应该对友元函数单独进行出入口申明 
class SIDLL StringIntegration
{
public:
	StringIntegration();
	StringIntegration(const String &str);
	//StringIntegration(StringIntegration &copy);
	~StringIntegration();
	//StringIntegration operator = (StringIntegration &copy);
	SIDLL friend StringIntegration operator + (const StringIntegration &str1, const StringIntegration &str2);
	SIDLL friend StringIntegration operator + (const StringIntegration &str1, const String &str2);
	SIDLL friend StringIntegration operator + (const String &str1, const StringIntegration &str2);
	StringIntegration & operator ++ ();
	StringIntegration operator ++ (int);
	StringIntegration & operator += (const String &str);
	StringIntegration & operator += (const StringIntegration &str);
	SIDLL friend StringIntegration operator - (const StringIntegration &str1, const StringIntegration &str2);
	SIDLL friend StringIntegration operator - (const StringIntegration &str1, const String &str2);
	SIDLL friend StringIntegration operator - (const String &str1, const StringIntegration &str2);
	StringIntegration & operator -- ();
	StringIntegration operator -- (int);
	StringIntegration & operator -= (const String & str);
	StringIntegration & operator -= (const StringIntegration & str);
	SIDLL friend StringIntegration operator * (const StringIntegration &str1, const StringIntegration &str2);
	SIDLL friend StringIntegration operator * (const StringIntegration &str1, const String &str2);
	SIDLL friend StringIntegration operator * (const String &str1, const StringIntegration &str2);
	StringIntegration & operator *= (const String &str);
	StringIntegration & operator *= (const StringIntegration &str);
	SIDLL friend StringIntegration operator / (const StringIntegration &str1, const StringIntegration &str2);
	SIDLL friend StringIntegration operator / (const StringIntegration &str1, const String &str2);
	SIDLL friend StringIntegration operator / (const String &str1, const StringIntegration &str2);

	SIDLL friend bool operator > (const StringIntegration &str1, const StringIntegration &str2);
	SIDLL friend bool operator > (const String &str1, const StringIntegration &str2);
	SIDLL friend bool operator > (const StringIntegration &str1, const String &str2);
	SIDLL friend bool operator < (const StringIntegration &str1, const StringIntegration &str2);
	SIDLL friend bool operator < (const String &str1, const StringIntegration &str2);
	SIDLL friend bool operator < (const StringIntegration &str1, const String &str2);
	SIDLL friend bool operator == (const StringIntegration &str1, const StringIntegration &str2);
	SIDLL friend bool operator == (const String &str1, const StringIntegration &str2);
	SIDLL friend bool operator == (const StringIntegration &str1, const String &str2);
	SIDLL friend bool operator >= (const StringIntegration &str1, const StringIntegration &str2);
	SIDLL friend bool operator >= (const String &str1, const StringIntegration &str2);
	SIDLL friend bool operator >= (const StringIntegration &str1, const String &str2);
	SIDLL friend bool operator <= (const StringIntegration &str1, const StringIntegration &str2);
	SIDLL friend bool operator <= (const String &str1, const StringIntegration &str2);
	SIDLL friend bool operator <= (const StringIntegration &str1, const String &str2);
	const String & string();
private:
	String s;
};

template<typename T>
inline void swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

