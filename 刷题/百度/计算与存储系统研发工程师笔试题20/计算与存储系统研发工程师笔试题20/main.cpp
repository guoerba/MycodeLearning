/*��Ŀ����
�����1,2,5����������ͬ������ϵĺ�Ϊ100����ϸ������磺100��1��һ����ϣ�5��1��19��5��һ����ϡ�����C����д����Ӧ����д�������򼴿ɣ�����10�֣�*/
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