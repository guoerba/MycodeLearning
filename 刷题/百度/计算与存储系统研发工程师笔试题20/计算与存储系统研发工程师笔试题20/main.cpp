/*题目描述
求出用1,2,5这三个数不同个数组合的和为100的组合个数。如：100个1是一个组合，5个1加19个5是一个组合。请用C语言写出相应程序（写出主程序即可）。（10分）*/
#include <iostream>
#include <vector>
#include <stdio.h>

#define	SUM				100

struct para{
	int i;
	int j;
	int k;
	para(int i,int j,int k):i(i),j(j),k(k){}
	para():i(0),j(0),k(0){}
};


std::vector<para> solution(int a, int b, int c,int sum)
{
	std::vector<para>s;
	for (int i = 0; i <= sum; i++)
	{
		for (int j = 0; j <= sum; j++)
		{
			for (int z = 0; z <= sum; z++)
			{
				if (a*i + b * j + c * z == sum)
					s.push_back(para(i, j, z));
			}
		}
	}
	return s;
}

int main()
{
	std::vector<para> s = solution(1, 2, 5, 100);
	std::cout << "size: " << s.size() << std::endl;
	while (1);
	return 0;
}