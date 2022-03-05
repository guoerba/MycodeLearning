#pragma once
#include <string>
#include <vector>
namespace StringOperation {
	__declspec(dllexport) void split(std::string &str, std::vector<std::string>&strs, char c);
}

/*
class __declspec(dllexport) StrOp 
{
public:
	StrOp();
	StrOp(const std::string &s);
	StrOp(const char *s,unsigned int length);
	~StrOp();

	char ** split(char c) const;
private:
	char *m_str;
	unsigned int len;
};

StrOp::StrOp()
{
	m_str = NULL;
	len = 0;
}

StrOp::StrOp(const std::string &s)
{
	len = s.size() + 1;
	m_str = new char[len];
	int i = 0;
	for (auto it = s.cbegin(); it != s.cend(); it++)
		*(m_str + i++) = *it;
	*(m_str + len - 1) = '\0';
}

StrOp::StrOp(const char *s,unsigned int length)
	: len(length)
{
	m_str = new char[len];
	for (unsigned int i = 0; i < len; i++)
		*(m_str + i) = *(s + i);
}

StrOp::~StrOp()
{
	delete[] m_str;
}

char ** StrOp::split(char c) const
{
	
}*/