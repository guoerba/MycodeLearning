// clock.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include "pch.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <string.h>

#define MAXHOUR 23
#define MINHOUR 0
#define MAXMIN	59
#define MINMIN	0
#define MAXSEC	59
#define MINSEC	0

std::fstream openfile(const std::string &filename,std::string &s)
{
	char data[256] = {0};
	std::fstream f(filename, std::ios::in);
	if (f.is_open())
	{
		while (!f.eof())
		{
			f.getline(data, 256);
			s.append(data);
			s.push_back(' ');
		}

	}
	else
		std::cout << "file is not opening" << std::endl;
	return f;
}

std::string input_data()
{

	int num;
	std::cin >> num;
	std::string s;
	s.append(std::to_string(num) + ' ');
	for (int i = 0; i < num; i++)
	{	
		char buf[256] = { 0 };
		std::cin >> buf;
		s.append(buf);
		s.push_back(' ');
	}
	return s;
}

//typedef std::vector<std::string>	StringBuffer;
std::vector<std::string> split(const char *str,int len,char splitter = ' ')
{
	std::string temp;
	std::vector<std::string> vs;
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

std::string MinimizeAlter(const std::vector<std::string> vs)
{
	std::string tstr;
	for (int i = 0, size = vs.size(); i < size; i++)
	{
		int judge = std::stoi(vs[i]);
		if (i == 0)
		{
			if (judge > MAXHOUR || judge < MINHOUR)
			{
				tstr.push_back('0');
				tstr.push_back(vs[i][1]);
			}
			else
			{
				tstr.append(vs[i]);
			}
			tstr.push_back(':');
		}
		else
		{
			if (judge > MAXMIN || judge < MINMIN)
			{
				tstr.push_back('0');
				tstr.push_back(vs[i][1]);
			}
			else
			{
				tstr.append(vs[i]);
			}
			tstr.push_back(':');
		}
	}
	tstr.resize(tstr.size() - 1);
	return tstr;
}



int main()
{
	/*std::string str;
	std::fstream f = openfile("./data.txt",str);

	
	std::vector<std::string> vs = split(str.c_str(), str.size(),' ');*/
	std::string s = input_data();
	std::vector<std::string> vs = split(s.c_str(), s.size(), ' ');
	int size = std::stoi(vs[0]);
	for (int i = 1; i <= size; i++)
	{
		std::cout << MinimizeAlter( split(vs[i].c_str(), vs[i].size(), ':') ) << std::endl;
	}
	//f.close();
	
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
