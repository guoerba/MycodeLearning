#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

typedef	std::vector<std::string> strbuf;

void split(std::string &str, std::vector<int>&strs, char c)
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
			strs.push_back(std::atoi(tmp.c_str()));
			tmp.clear();
		}
		else
			tmp.push_back(*it);
	}
	if (flag)
		str.pop_back();
}

bool isLoop(const std::vector<int>&a)
{
	std::vector<int>b;
	b.push_back(a[a.size() - 1]);
	for (int i = 0; i < a.size(); i++)
		b.push_back(a[i]);
	b.push_back(a[0]);

	for (int i = 1; i <= a.size(); i++)
	{
		if (b[i] >= b[i - 1] + b[i + 1])
			return false;
	}
	return true;
}

int main()
{
	int group;
	std::cin >> group;
	std::vector<int>n(group);
	std::vector<std::vector<int>>d(group);
	std::vector<bool>res(group);
	std::string tmp;
	for (int i = 0; i < group; i++)
	{

		std::cin >> n[i] >> tmp;
		tmp.push_back(' ');
		split(tmp, d[i], ' ');
	}

	for (int i = 0; i < n.size(); i++)
		res[i] = isLoop(d[i]);

	for (int i = 0; i < res.size(); i++)
		std::cout << (res[i] ? "YES" : "NO") << std::endl;

	while (1);

	return 0;
}
/*
void getleftstring(const std::string&s, const std::vector<int>&sub, std::vector<int>&o)
{
	for (int i = 0; i < s.size(); i++)
	{
		int flag = false;
		for (int j = 0; j < sub.size(); j++)
		{
			if (s[i] - 48 == s[j])
			{
				flag = true;
				break;
			}
		}
		if (!flag)
			o.push_back(s[i] - 48);
	}
}

int findindex(const std::vector<int>&v, int n)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == n)
			return i;
	}
	return -1;
}

int getindex(const std::string&s, int n)
{
	int index = 0;
	std::vector<int>list(n);
	for (int i = 1; i <= n; i++)
		list[i] = i;
	std::vector<int>tmp,left;
	for (int i = 0; i < s.size(); i++)
	{
		tmp.push_back(s[i] - 48);
		getleftstring(s, tmp, left);
		std::sort(left.begin(), left.end());
		int in = findindex(left, s[i] - 48);
		index += (n - i - 1) * (in);
	}
		
	return index;
}

int main()
{
	int n;
	std::cin >> n;
	std::string s;
	for (int i = 0; i < n; i++)
	{
		int tmp;
		std::cin >> tmp;
		s.push_back(tmp + 48);
	}
	std::cout << getindex(s, n) << std::endl;
}*/

