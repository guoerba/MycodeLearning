#include "Test.h"
#include <iostream>


Test::Test()
{
}

Test::Test(const String & s)
{
	StringBuffer sb = split(s, ' ');
	for (auto i : sb)
	{
		std::cout << i << std::endl;
	}
}


Test::~Test()
{
}

StringBuffer Test::split(const String & s, const char splitter)
{
	StringBuffer sbuf;
	String str;
	for (auto it = s.begin(); it != s.end(); ++it)
	{
		if (*it == splitter)
		{
			sbuf.push_back(str);
			str.clear();
		}
		else
		{
			str.push_back(*it);
		}		
	}
	sbuf.push_back(str);
	return sbuf;
}
