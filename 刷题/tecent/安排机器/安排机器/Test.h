#pragma once
#include <vector>
#include <string>

typedef std::string				String;
typedef std::vector<String>		StringBuffer;
class Test
{
public:
	Test();
	Test(const String &s);
	~Test();
private:
	StringBuffer split(const String &s, const char splitter);
};

