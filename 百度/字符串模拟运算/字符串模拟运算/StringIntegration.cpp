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

StringIntegration operator+(const StringIntegration &str1,const StringIntegration & str2)
{//unsigned int len = (str.size() > this->s.size()) ? str.size() + 1 : this->s.size() + 1;
	String ret;//返回值是局部变量，故不能用返回引用
	char carry = 0;//返回两个长度相等的整数
	auto equaladd = [](const String &maxstr, const String &minstr, String &ret,int len)->char {
		char c, carry = 0;
		/*for (int i = minstr.size(), j = i - 1,k = maxstr.size() - 1; i > 0; i--, j--,k--)
		{
			a = maxstr[k], b = minstr[j];
			c = a + b + carry - 96;
			carry = c / 10;
			ret.push_back(c % 10 + 48);
		}*/
		for (auto minrit = minstr.crbegin(), maxrit = maxstr.crbegin(); minrit != minstr.crend(); ++minrit, ++maxrit)
		{
			c = *minrit + *maxrit + carry - 96;
			carry = c / 10;
			ret.push_back(c % 10 + 48);
		}
		return carry; 
	};
	auto addone = [](const String &str, int index,String &ret,int carry)->char {
		char a;
		/*for (int i = index, j = i - 1; i > 0; i--, j--)
		{
			a = str[j] - 48 + carry;
			carry = a / 10;
			ret.push_back(a % 10 + 48);
		}*/
		
		for (auto rit = str.crbegin() + index; rit != str.crend(); ++rit)
		{
			a = *rit - 48 + carry;
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
			//carry = equaladd(str2.s,str1.s , ret, slen1);	
			//carry = addone(str2.s, slen2 - slen1, ret,carry);
			carry = addone(str2.s, slen1, ret, equaladd(str2.s, str1.s, ret, slen1));
		else
			//carry = equaladd(str1.s,str2.s, ret, slen2);
			//carry = addone(str1.s, slen1 - slen2, ret,carry);
			carry = addone(str1.s, slen2, ret, equaladd(str1.s, str2.s, ret, slen2));
	}
	if (carry)
		ret.push_back(49);

	/*for (int i = 0, size = ret.size(); i < (size >> 1); i++)
		swap(ret[i], ret[size - i - 1]);*/
	std::reverse(ret.begin(), ret.end());
	return StringIntegration(ret);
}

StringIntegration operator+(const StringIntegration & str1, const String & str2)
{
	return str1 + StringIntegration(str2);
}

StringIntegration operator+(const String & str1, const StringIntegration & str2)
{
	return StringIntegration(str1) + str2;
}

StringIntegration operator-(const StringIntegration & str1, const StringIntegration & str2)
{
	String ret;//返回值是局部变量，故不能用返回引用
	bool str1Substr2 = str1.s.size() > str2.s.size() ? true : false;//哪个数大哪个数当被减数
	/*auto equalsub = [](const String &minuend,const String &subtractor,String &ret,int len)->char {
		char a, b, c, carry = 0;
		for (int i = len,mindex = minuend.size() - 1,sindex = subtractor.size() - 1; i > 0; i--,mindex--,sindex--)
		{
			a = minuend[mindex], b = subtractor[sindex];
			c = a - b - carry + 10;
			carry = (c / 10) ^ 1;//异或，当a / 10 = 1时输出0；当a / 10 = 0时输出1
			ret.push_back(c % 10 + 48);
		}
		return carry;
	};*/
	auto equalsub = [](const String &minuend, const String &subtractor, String &ret)->char {
		char c, carry = 0;
		for (auto subrit = subtractor.crbegin(), minrit = minuend.crbegin(); subrit != subtractor.crend(); ++subrit, ++minrit)
		{
			c = *minrit - *subrit - carry + 10;
			carry = (c / 10) ^ 1;
			ret.push_back(c % 10 + 48);
		}
		return carry;
	};
	auto subone = [](const String &str, int index, String &ret, int carry)->char {
		char a;
		/*for (int i = index, j = i - 1; i > 0; i--, j--)
		{
			a = str[j] - 38 - carry;
			carry = (a / 10) ^ 1;//异或，当a / 10 = 1时输出0；当a / 10 = 0时输出1
			ret.push_back(a % 10 + 48);
		}*/
		for (auto rit = str.crbegin() + index; rit != str.crend(); ++rit)
		{
			a = *rit - 38 - carry;
			carry = (a / 10) ^ 1;
			ret.push_back(a % 10 + 48);
		}
		/*if (!(ret[0] - 48))
			ret.erase(0, 1);*/
		return carry;
	};
	bool isminus = false;
	if (str1.s.size() == str2.s.size())
	{
		//str1.s > str2.s ? equalsub(str1.s, str2.s, ret, str1.s.size()) : equalsub(str2.s, str1.s, ret, str1.s.size()),isminus = true;
		if (str1.s > str2.s)
			equalsub(str1.s, str2.s, ret);
		else
		{
			equalsub(str2.s, str1.s, ret);
			isminus = true;
		}
	}
	else
	{
		if (str1.s.size() > str2.s.size())
			//int carry = equalsub(str1.s, str2.s, ret);
			//subone(str1.s, str1.s.size() - str2.s.size(), ret, carry);
			subone(str1.s, str2.s.size(), ret, equalsub(str1.s, str2.s, ret));
		else
		{
			//int carry = equalsub(str2.s, str1.s, ret);
			//subone(str2.s, str2.s.size() - str1.s.size(), ret, carry);
			subone(str2.s, str1.s.size(), ret, equalsub(str2.s, str1.s, ret));
			isminus = true;
		}
	}
	/*for (int i = 0, size = ret.size(); i < (size >> 1); i++)
		swap(ret[i], ret[size - i - 1]);*/
	std::reverse(ret.begin(), ret.end());
	if (!(ret[0] - 48))
		ret.erase(0, 1);
	if (isminus)
		ret.insert(0, 1, '-');
	return StringIntegration(ret);
}

StringIntegration operator-(const StringIntegration & str1, const String & str2)
{
	return str1 - StringIntegration(str2);
}

StringIntegration operator-(const String & str1, const StringIntegration & str2)
{
	return StringIntegration(str1) - str2;
}

StringIntegration operator*(const StringIntegration & str1, const StringIntegration & str2)
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
		for (auto rit = s.crbegin(); rit != s.crend(); ++rit)
		{
			a = (*rit - 48)*cbit + carry;
			carry = a / 10;
			ret.push_back(a % 10 + 48);
		}
		if (carry)
			ret.push_back(carry + 48);
		std::reverse(ret.begin(), ret.end());
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
	return ret;
}

StringIntegration operator*(const StringIntegration & str1, const String & str2)
{
	return str1 * StringIntegration(str2);
}

StringIntegration operator*(const String & str1, const StringIntegration & str2)
{
	return StringIntegration(str1) * str2;
}

StringIntegration operator/(const StringIntegration & str1, const StringIntegration & str2)
{
	bool isminus = (str1.s[0] == '-' && str2.s[0] != '-' || (str1.s[0] != '-' && str2.s[0] == '-')) ? true : false;//符号判断
	StringIntegration dividend = StringIntegration(str1.s); StringIntegration divisor = StringIntegration(str2.s);
	if (dividend.s[0] == '-')
		dividend.s.erase(0, 1);
	if (divisor.s[0] == '-')
		divisor.s.erase(0, 1);
	String ret;
	for (int diff = dividend.s.size() - divisor.s.size() + 1; diff > 0; --diff)
	{
		StringIntegration carry = StringIntegration("1");
		for (int i = 1; i < diff; i++)
			carry.s.push_back('0');
		StringIntegration tempdivisor = divisor * carry;
		char n = 48;
		while (dividend > tempdivisor)
		{
			dividend = dividend - tempdivisor;
			n++;
		}
		ret.push_back(n);
	}

	//ret.append(dividend.s);
	if (ret[0] == 48)
		ret.erase(0, 1);
	if (isminus)
		ret.insert(0, 1, '-');
	return StringIntegration(ret);
}

bool operator>(const StringIntegration & str1, const StringIntegration & str2)
{
	if (str1.s[0] == '-' && str2.s[0] != '-')//str1为负，str2为正
		return false;
	if (str1.s[0] != '-' && str2.s[0] == '-') //str1为正，str2为负
		return true;
	if (str1.s[0] != '-' && str2.s[0] != '-')//都为正
	{
		if (str1.s.size() > str2.s.size())//str1更长
			return true;
		else if (str1.s.size() < str2.s.size())
			return false;
		else//一样长
		{
			for (auto it1 = str1.s.cbegin(), it2 = str2.s.cbegin(); it1 != str1.s.cend(); ++it1, ++it2)
			{
				if (*it1 > *it2)
					return true;
				else if (*it1 < *it2)
					return false;				
			}
			return false;
		}
		return false;
	}
	if (str1.s[0] == '-' && str2.s[0] == '-')//都为负
	{
		String s1 = str1.s, s2 = str2.s;
		s1.erase(0, 1), s2.erase(0, 1);
		if (s1.size() < s2.size())//str1更长
			return true;
		else if (s1.size() > s2.size())
			return false;
		else//一样长
		{
			for (auto it1 = s1.cbegin(), it2 = s2.cbegin(); it1 != s1.cend(); ++it1, ++it2)
			{
				if (*it1 < *it2)
					return true;
				else if (*it1 > *it2)
					return false;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool operator>(const String & str1, const StringIntegration & str2)
{
	return StringIntegration(str1) > str2;
}

bool operator>(const StringIntegration & str1, const String & str2)
{
	return str1 > StringIntegration(str2);
}

bool operator<(const StringIntegration & str1, const StringIntegration & str2)
{
	return str2 > str1;
}

bool operator<(const String & str1, const StringIntegration & str2)
{
	return StringIntegration(str1) < str2;
}

bool operator<(const StringIntegration & str1, const String & str2)
{
	return str1 < StringIntegration(str2);
}

bool operator==(const StringIntegration & str1, const StringIntegration & str2)
{
	if (str1.s.size() != str2.s.size())
		return false;
	else
	{
		for (auto it1 = str1.s.cbegin(), it2 = str2.s.cbegin(); it1 != str1.s.cend(); ++it1, ++it2)
		{
			if (*it1 != *it2)
				return false;
		}
		return true;
	}
	return false;
}

bool operator==(const String & str1, const StringIntegration & str2)
{
	return StringIntegration(str1) == str2;
}

bool operator==(const StringIntegration & str1, const String & str2)
{
	return str1 == StringIntegration(str2);
}

StringIntegration & StringIntegration::operator++(){
	char a,carry = 1;
	/*for (int i = s.size(), j = i - 1; i > 0; i--, j--)
	{
		a = s[j] - 48 + carry;
		carry = a / 10;
		s[j] = a % 10 + 48;
		if (!carry)
			break;
	}*/
	for (auto rit = s.rbegin(); rit != s.rend(); ++rit)
	{
		a = *rit - 48 + carry;
		carry = a / 10;
		*rit = a % 10 + 48;
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
	/*for (int i = s.size(), j = i - 1; i > 0; i--, j--)
	{
		a = s[j] - 38 - carry;
		carry = (a / 10) ^ 1;//异或，当a / 10 = 1时输出0；当a / 10 = 0时输出1
		s[j] = a % 10 + 48;
		if (!carry)
			break;
	}*/
	for (auto rit = s.rbegin(); rit != s.rend(); ++rit)
	{
		a = *rit - 38 - carry;
		carry = (a / 10) ^ 1;
		*rit = a % 10 + 48;
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