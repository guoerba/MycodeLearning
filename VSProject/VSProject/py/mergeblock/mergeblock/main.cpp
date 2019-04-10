#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
typedef std::vector<std::string>    StringBuffer;
typedef unsigned int				uint;

struct Section {
	uint lower;
	uint upper;
	//Section(uint l, uint u) :lower(l), upper(u) {};
};

StringBuffer split(const char *str, int len, char splitter = ' ')
{
	std::string temp;
	StringBuffer vs;
	for (int i = 0; i < len; i++)
	{
		if (str[i] != splitter)
		{
			temp.push_back(str[i]);
		}
		else
		{
			vs.push_back(temp);
			temp.clear();
		}
	}
	vs.push_back(temp);
	temp.clear();
	return vs;
}

std::vector<Section> caclsections(const std::vector<Section> &sections)
{
	 
}


int main()
{
	char s[256] = { 0 };
	std::cin.getline(s, 256);
	StringBuffer spaces = split(s, strlen(s), ' ');
	size_t size = spaces.size();
	//Section *sections = (Section*)malloc(size);
	std::vector<Section> sections(size);

	for (uint i = 0; i < size; i++)
	{
		StringBuffer element = split(spaces[i].c_str(), spaces[i].size(), ',');
		sections[i].lower = std::stoul(element[0]);
		sections[i].upper = std::stoul(element[1]);
	}

	for (int i = 0; i < size; i++)
	{
		std::cout << sections[i].lower << " " << sections[i].upper << std::endl;
	}

	//free(sections);
	exit(0);
	std::cout << "done" << std::endl;
	return 0;
}