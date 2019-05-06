#include "StringIntegration.h"

#define MAX(a,b)	(a > b ? a : b)
#define MIN(a,b)	(a < b ? a : b)

StringIntegration::StringIntegration()
	: s(String())
{
}

StringIntegration::StringIntegration(const String &str)
	: s(str)
{

}

/*StringIntegration::StringIntegration(StringIntegration &copy)
{
	copy.s = this->s;//浅拷贝
}*/

StringIntegration::~StringIntegration()
{
	if(!s.empty())
		s.clear();
}

/*StringIntegration StringIntegration::operator = (StringIntegration &copy)
{
	copy.s = this->s;
	return copy;
}*/

String operator+(const StringIntegration &str1,const StringIntegration & str2)
{//unsigned int len = (str.size() > this->s.size()) ? str.size() + 1 : this->s.size() + 1;
	String ret;//返回值是局部变量，故不能用返回引用
	char carry = 0;//返回两个长度相等的整数
	auto equaladd = [](const String &maxstr, const String &minstr, String &ret,int len)->char {
		char a, b, c, carry = 0;
		for (int i = minstr.size(), j = i - 1,k = maxstr.size() - 1; i > 0; i--, j--,k--)
		{
			a = maxstr[k], b = minstr[j];
			c = a + b + carry - 96;
			carry = c / 10;
			ret.push_back(c % 10 + 48);
		}
		return carry; 
	};
	auto addone = [](const String &str, int index,String &ret,int carry)->char {
		char a;
		for (int i = index, j = i - 1; i > 0; i--, j--)
		{
			a = str[j] - 48 + carry;
			carry = a / 10;
			ret.push_back(a % 10 + 48);
		}
		return carry;
	};

	int slen1 = str1.s.size(), slen2 = str2.s.size();
	if (slen1 == slen2)
		carry = equaladd(str1.s, str2.s, ret, slen1);		
	else
	{
		if (slen1 < slen2)
		{	
			carry = equaladd(str2.s,str1.s , ret, slen1);	
			carry = addone(str2.s, slen2 - slen1, ret,carry);
		}
		else
		{
			carry = equaladd(str1.s,str2.s, ret, slen2);
			carry = addone(str1.s, slen1 - slen2, ret,carry);
		}
	}
	if (carry)
		ret.push_back(49);

	for (int i = 0, size = ret.size(); i < (size >> 1); i++)
		swap(ret[i], ret[size - i - 1]);
	return ret;
}

String operator+(const StringIntegration & str1, const String & str2)
{
	return str1 + StringIntegration(str2);
}

String operator+(const String & str1, const StringIntegration & str2)
{
	return StringIntegration(str1) + str2;
}

String operator-(const StringIntegration & str1, const StringIntegration & str2)
{
	String ret;//返回值是局部变量，故不能用返回引用
	bool str1Substr2 = str1.s.size() > str2.s.size() ? true : false;//哪个数大哪个数当被减数
	auto equalsub = [](const String &minuend,const String &subtractor,String &ret,int len)->char {
		char a, b, c, carry = 0;
		for (int i = len,mindex = minuend.size() - 1,sindex = subtractor.size() - 1; i > 0; i--,mindex--,sindex--)
		{
			a = minuend[mindex], b = subtractor[sindex];
			c = a - b - carry + 10;
			carry = (c / 10) ^ 1;//异或，当a / 10 = 1时输出0；当a / 10 = 0时输出1
			ret.push_back(c % 10 + 48);
		}
		return carry;
	};
	auto subone = [](const String &str, int index, String &ret, int carry)->char {
		char a;
		for (int i = index, j = i - 1; i > 0; i--, j--)
		{
			a = str[j] - 38 - carry;
			carry = (a / 10) ^ 1;//异或，当a / 10 = 1时输出0；当a / 10 = 0时输出1
			ret.push_back(a % 10 + 48);
		}
		if (!(ret[0] - 48))
			ret.erase(0, 1);
		return carry;
	};
	bool isminus = false;
	if (str1.s.size() == str2.s.size())
	{
		//str1.s > str2.s ? equalsub(str1.s, str2.s, ret, str1.s.size()) : equalsub(str2.s, str1.s, ret, str1.s.size()),isminus = true;
		if (str1.s > str2.s)
			equalsub(str1.s, str2.s, ret, str1.s.size());
		else
		{
			equalsub(str2.s, str1.s, ret, str1.s.size());
			isminus = true;
		}
	}
	else
	{
		if (str1.s.size() > str2.s.size())
		{
			int carry = equalsub(str1.s, str2.s, ret, str2.s.size());
			subone(str1.s, str1.s.size() - str2.s.size(), ret, carry);
		}
		else
		{
			int carry = equalsub(str2.s, str1.s, ret, str1.s.size());
			subone(str2.s, str2.s.size() - str1.s.size(), ret, carry);
			isminus = true;
		}
	}
	for (int i = 0, size = ret.size(); i < (size >> 1); i++)
		swap(ret[i], ret[size - i - 1]);
	if (!(ret[0] - 48))
		ret.erase(0, 1);
	if (isminus)
		ret.insert(0, 1, '-');
	return ret;
}

String operator-(const StringIntegration & str1, const String & str2)
{
	return str1 - StringIntegration(str2);
}

String operator-(const String & str1, const StringIntegration & str2)
{
	return StringIntegration(str1) - str2;
}

String operator*(const StringIntegration & str1, const StringIntegration & str2)
{
	bool isminus = (str1.s[0] == '-' && str2.s[0] != '-' || (str1.s[0] != '-' && str2.s[0] == '-')) ? true : false;//符号判断
	String s1 = String(str1.s); String s2 = String(str2.s);
	if (s1[0] == '-')
		s1.erase(0, 1);
	if (s2[0] == '-')
		s2.erase(0, 1);
	auto bitmultiply = [](const String &s, const char &c,int index)->String {
		String ret;
		char cbit = c - 48,carry = 0,a;
		for (int i = s.size(), j = i - 1; i > 0; i--, j--)
		{
			a = (s[j] - 48)*cbit + carry;
			carry = a / 10;
			ret.push_back(a % 10 + 48);
		}
		if (carry)
			ret.push_back(carry + 48);
		for (int i = 0, size = ret.size(); i < (size >> 1); i++)
			swap(ret[i], ret[size - i - 1]);
		for (int i = 0; i < index; i++)
			ret.push_back(48);
		return ret;
	};
	//StringBuffer bitmultiplyresults(str2.s.size());
	StringIntegration ret("0");
	for (int i = s2.size(), j = 0; i > 0; i--,j++)
		ret += bitmultiply(s1, s2[i - 1],j);
	if (isminus)
		ret.s.insert(0, 1, '-');
	return ret.s;
}

String operator*(const StringIntegration & str1, const String & str2)
{
	return str1 * StringIntegration(str2);
}

String operator*(const String & str1, const StringIntegration & str2)
{
	return StringIntegration(str1) * str2;
}

StringIntegration & StringIntegration::operator++(){
	char a,carry = 1;
	for (int i = s.size(), j = i - 1; i > 0; i--, j--)
	{
		a = s[j] - 48 + carry;
		carry = a / 10;
		s[j] = a % 10 + 48;
		if (!carry)
			break;
	}
	if (carry)
		s.insert(s.begin(),49);
	return *this;
}

StringIntegration StringIntegration::operator++(int)
{
	StringIntegration old = *this;
	++(*this);
	return old;
}

StringIntegration & StringIntegration::operator+=(const String & str)
{
	*this = *this + str;
	return *this;
}

StringIntegration & StringIntegration::operator+=(const StringIntegration & str)
{
	*this = *this + str;
	return *this;
}

StringIntegration & StringIntegration::operator--()
{
	char a, carry = 1;
	for (int i = s.size(), j = i - 1; i > 0; i--, j--)
	{
		a = s[j] - 38 - carry;
		carry = (a / 10) ^ 1;//异或，当a / 10 = 1时输出0；当a / 10 = 0时输出1
		s[j] = a % 10 + 48;
		if (!carry)
			break;
	}
	if (!(s[0] - 48))
		s.erase(0, 1);
	return *this;
}

StringIntegration StringIntegration::operator--(int)
{
	StringIntegration old = *this;
	--(*this);
	return old;
}

StringIntegration & StringIntegration::operator-=(const String & str)
{
	*this = *this - str;
	return *this;
}

StringIntegration & StringIntegration::operator-=(const StringIntegration & str)
{
	*this = *this - str;
	return *this;
}

StringIntegration & StringIntegration::operator*=(const String & str)
{
	*this = *this * str;
	return *this;
}

StringIntegration & StringIntegration::operator*=(const StringIntegration & str)
{
	*this = *this * str;
	return *this;
}

const String & StringIntegration::string()
{
	return s;
}