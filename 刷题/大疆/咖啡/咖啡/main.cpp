#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

struct data {
	int N;
	int A;
	int X;
	int *min;
	data() {};
	data(int n, int a, int x)
	{
		N = n, A = a, X = x;
		min = new int[N];
	}
};

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
			strs.push_back(std::stoi(tmp));
			tmp.clear();
		}
		else
			tmp.push_back(*it);
	}
	if (flag)
		str.pop_back();
}

int getres(int a, int x, std::vector<int>&d)
{
	float totala = x * 60;
	float total = 8 * 60;
	int res = 0;
	float tmpres = 0.0;
	for (int i = 0; i < d.size(); i++)
	{
		if (total < 0)
			return 0;
		float tmp = d[i] / a ;
		if (tmp - totala <= 1e-7)
		{
			totala -= tmp;
			tmpres += tmp;
		}
		else
		{
			total -= x * 60;
			tmpres += d[i];
		}
	}
	
	res = ceil(tmpres);
	return res;
}

int main()
{
	std::vector<data>d;
	std::vector<int>N, A, X;
	std::vector<std::vector<int>>dat;
	int n, a, x;
	while (std::cin >> n >> a >> x)
	{
		N.push_back(n);
		A.push_back(a);
		X.push_back(x);
		std::vector<int>v(n);
		for (int i = 0; i < n; i++)
			std::cin >> v[i];
		dat.push_back(v);
	}

	for (int i = 0; i < dat.size(); i++)
		std::sort(dat[i].begin(), dat[i].end(), [](int a, int b) {return a > b; });

	int size = N.size();  
	std::vector<int>result(size);
	for (int i = 0; i < size; i++)
	{
		result[i] = getres(A[i], X[i], dat[i]);
	}
	for (auto r : result)
		std::cout << r << std::endl;
	while (1);
	return 0;
}