#include "alloc2darray.h"
#include "StringIntegration.h"
#include "stringoperation.h"

#define MAX(a,b)	(a > b ? a : b)
#define MIN(a,b)	(a < b ? a : b)

#define TEMPLATEDLL_EXPORT

/*int TestClass::getSum()
{
	return a + b;
}*/

template<class T>
Array2d<T>::Array2d(int row, int col)
	: m_row(row), m_col(col)
{
	ptr = CreateArray2D(row, col, 0);
}

template<class T>
Array2d<T>::Array2d(int row, int col, T init)
	: m_row(row), m_col(col)
{
	ptr = CreateArray2D(row, col, init);
}

template<class T>
Array2d<T>::Array2d(int row, int col, std::function<T(int, int)>f)
	: m_row(row), m_col(col)
{
	ptr = CreateArray2D(row, col, f);
}

template<class T>
Array2d<T>::Array2d(int row, int col, T **a, std::function<T(int, int, T**)>f)
	: m_row(row), m_col(col)
{
	ptr = CreateArray2D(row, col, a, f);
}

template<class T>
Array2d<T>::~Array2d()
{
	DeleteArray2D(ptr);
}

template<class T>
const T Array2d<T>::getItem(int row,int col)
{
	return ptr[row][col];
}

template<class T>
void Array2d<T>::setItem(int row, int col, T val)
{
	ptr[row][col] = val;
}

template<typename T>
T &Array2d<T>::operator()(int i, int j) const//可以通过调用a(i,j)的方式来读取、修改(i,j)处的值
{
	return *(*(ptr + i) + j);
}

template<typename T>
T * Array2d<T>::operator[](int index)//可以通过调用a[i][j]的方式来读取、修改(i,j)处的值
{
	return *(ptr + index);
}

template<class T>
T** Array2d<T>::CreateArray2D(int row, int col, T initialize)
{
	T **p = new T*[row];
	*p = new T[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = initialize;
	return p;
}

/*template<class T>
std::vector<T> **Array2d<T>::CreateArray2D(int row, int col)
{
	std::vector<T> **p = new std::vector<T>*[row];
	*p = new std::vector<T>[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = std::vector<T>();
	return p;
}*/

template<class T>
T **Array2d<T>::CreateArray2D(int row, int col, std::function<T(int, int)> f)
{
	T **p = new T*[row];
	*p = new T[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = f(i, j);
	return p;
}

template<class T>
T **Array2d<T>::CreateArray2D(int row, int col, T **a, std::function<T(int, int, T**)> f)
{
	T **p = new T*[row];
	*p = new T[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = f(i, j, a);
	return p;
}


template<class T>
void Array2d<T>::DeleteArray2D(T **p)
{
	//std::cout << "type is: " << typeid(p).name() << std::endl;
	/*String tname(typeid(p).name());
	if (tname.find("std::vector"))
	{
		std::cout << "isvector" << std::endl;
		for (int i = 0; i < m_row; i++)
			for (int j = 0; j < m_col; j++)
				ptr[i][j].clear();
	}*/
	delete[] * p;
	delete[] p;
	p = NULL;
}

template <> void Array2d< std::vector<int> >::DeleteArray2D(std::vector<int> **p)
{
	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
		{
			std::vector<int> tmp;
			ptr[i][j].swap(tmp);
		}
	delete[] * p;
	delete[] p;
	p = NULL;
}


template class Array2d<short>;
template class Array2d<unsigned short>;
template class Array2d<int>;
template class Array2d<unsigned int>;
template class Array2d<long>;
template class Array2d<unsigned long>;
template class Array2d<long long>;
template class Array2d<unsigned long long>;
template class Array2d<float>;
template class Array2d<double>;
template class Array2d<bool>;
template class Array2d< std::vector<int> >;

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
	if (!s.empty())
		s.clear();
}

/*StringIntegration StringIntegration::operator = (StringIntegration &copy)
{
	copy.s = this->s;
	return copy;
}*/

StringIntegration operator+(const StringIntegration &str1, const StringIntegration & str2)
{
	String ret;//返回值是局部变量，故不能用返回引用
	char carry = 0;//返回两个长度相等的整数
	auto equaladd = [](const String &maxstr, const String &minstr, String &ret, int len)->char {
		char c, carry = 0;
		for (auto minrit = minstr.crbegin(), maxrit = maxstr.crbegin(); minrit != minstr.crend(); ++minrit, ++maxrit)
		{
			c = *minrit + *maxrit + carry - 96;
			carry = c / 10;
			ret.push_back(c % 10 + 48);
		}
		return carry;
	};
	auto addone = [](const String &str, int index, String &ret, int carry)->char {
		char a;
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
			carry = addone(str2.s, slen1, ret, equaladd(str2.s, str1.s, ret, slen1));
		else
			carry = addone(str1.s, slen2, ret, equaladd(str1.s, str2.s, ret, slen2));
	}
	if (carry)
		ret.push_back(49);

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

StringIntegration & StringIntegration::operator++() {
	char a, carry = 1;
	for (auto rit = s.rbegin(); rit != s.rend(); ++rit)
	{
		a = *rit - 48 + carry;
		carry = a / 10;
		*rit = a % 10 + 48;
		if (!carry)
			break;
	}
	if (carry)
		s.insert(s.begin(), 49);
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

StringIntegration operator-(const StringIntegration & str1, const StringIntegration & str2)
{
	String ret;//返回值是局部变量，故不能用返回引用
	bool str1Substr2 = str1.s.size() > str2.s.size() ? true : false;//哪个数大哪个数当被减数
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
		for (auto rit = str.crbegin() + index; rit != str.crend(); ++rit)
		{
			a = *rit - 38 - carry;
			carry = (a / 10) ^ 1;
			ret.push_back(a % 10 + 48);
		}
		return carry;
	};
	bool isminus = false;
	if (str1.s.size() == str2.s.size())
	{
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
			subone(str1.s, str2.s.size(), ret, equalsub(str1.s, str2.s, ret));
		else
		{
			subone(str2.s, str1.s.size(), ret, equalsub(str2.s, str1.s, ret));
			isminus = true;
		}
	}
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

StringIntegration & StringIntegration::operator--()
{
	char a, carry = 1;
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

StringIntegration operator*(const StringIntegration & str1, const StringIntegration & str2)
{
	bool isminus = (str1.s[0] == '-' && str2.s[0] != '-' || (str1.s[0] != '-' && str2.s[0] == '-')) ? true : false;//符号判断
	String s1 = String(str1.s); String s2 = String(str2.s);
	if (s1[0] == '-')
		s1.erase(0, 1);
	if (s2[0] == '-')
		s2.erase(0, 1);
	auto bitmultiply = [](const String &s, const char &c, int index)->String {
		String ret;
		char cbit = c - 48, carry = 0, a;
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
	StringIntegration ret("0");
	for (int i = s2.size(), j = 0; i > 0; i--, j++)
		ret += bitmultiply(s1, s2[i - 1], j);
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
		while (dividend >= tempdivisor)
		{
			dividend = dividend - tempdivisor;
			n++;
		}
		ret.push_back(n);
	}

	if (ret[0] == 48)
		ret.erase(0, 1);
	if (isminus)
		ret.insert(0, 1, '-');
	return StringIntegration(ret);
}

StringIntegration operator/(const StringIntegration & str1, const String & str2)
{
	return str1 / StringIntegration(str2);
}

StringIntegration operator/(const String & str1, const StringIntegration & str2)
{
	return StringIntegration(str1) / str2;
}

bool operator>(const StringIntegration & str1, const StringIntegration & str2)
{
	if (str1.s[0] == '-' && str2.s[0] != '-')//str1为负，str2为正
		return false;
	if (str1.s[0] != '-' && str2.s[0] == '-') //str1为正，str2为负
		return true;
	if (str1.s[0] != '-' && str2.s[0] != '-')//都为正
	{
		String s1 = str1.s, s2 = str2.s;
		while (s1[0] == 48)
			s1.erase(0, 1);
		while (s2[0] == 48)
			s2.erase(0, 1);
		if (s1.size() > s2.size())//str1更长
			return true;
		else if (s1.size() < s2.size())
			return false;
		else//一样长
		{
			for (auto it1 = s1.cbegin(), it2 = s2.cbegin(); it1 != s1.cend(); ++it1, ++it2)
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
		while (s1[0] == 48)
			s1.erase(0, 1);
		while (s2[0] == 48)
			s2.erase(0, 1);
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

bool operator > (const String & str1, const StringIntegration & str2)
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
	String s1 = str1.s, s2 = str2.s;
	if (s1[0] == '-')//去除高位的0
	{
		while (s1[1] == 48)
			s1.erase(1, 1);
	}
	else
	{
		while (s1[0] == 48)
			s1.erase(0, 1);
	}
	if (s2[0] == '-')
	{
		while (s2[1] == 48)
			s2.erase(1, 1);
	}
	else
	{
		while (s2[0] == 48)
			s2.erase(0, 1);
	}

	if (s1.size() != s2.size())
		return false;
	else
	{
		for (auto it1 = s1.cbegin(), it2 = s2.cbegin(); it1 != s1.cend(); ++it1, ++it2)
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

bool operator>=(const StringIntegration & str1, const StringIntegration & str2)
{
	return str1 > str2 || (str1 == str2);
}

bool operator>=(const String & str1, const StringIntegration & str2)
{
	return StringIntegration(str1) >= str2;
}

bool operator>=(const StringIntegration & str1, const String & str2)
{
	return str1 >= String(str2);
}

bool operator<=(const StringIntegration & str1, const StringIntegration & str2)
{
	return str1 < str2 || (str1 == str2);
}

bool operator<=(const String & str1, const StringIntegration & str2)
{
	return StringIntegration(str1) <= str2;
}

bool operator<=(const StringIntegration & str1, const String & str2)
{
	return str1 <= StringIntegration(str2);
}

const String & StringIntegration::string()
{
	return s;
}

void StringOperation::split(std::string &str, std::vector<std::string>&strs, char c)
{
	bool flag = false;
	if (str[str.size() - 1] != c)
	{
		str.push_back(c);
		flag = true;
	}		
	std::string tmp;
	for (auto it = str.begin(); it != str.end(); it++)
	{
		if (*it == c)
		{
			strs.push_back(tmp);
			tmp.clear();
		}
		else
			tmp.push_back(*it);
	}
	if(flag)
		str.pop_back();
}

BOOL APIENTRY DllMain(HANDLE hModule,DWORD  ul_reason_for_call,	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		printf("\nprocess attach of dll\n");
		break;
	case DLL_THREAD_ATTACH:
		printf("\nthread attach of dll\n");
		break;
	case DLL_THREAD_DETACH:
		printf("\nthread detach of dll\n");
		break;
	case DLL_PROCESS_DETACH:
		printf("\nprocess detach of dll\n");
		break;
	}
	return TRUE;
}