#include <iostream>
#include <string>
#include <vector>


struct pooldata {
	int m;
	int t;
	int m1;
	int t1;
	int m2;
	int t2;
	int m_now;
	pooldata() : m(0), t(0), m1(0), t1(0), m2(0), t2(0), m_now(0) {};
	pooldata(int m, int t, int m1, int t1, int m2, int t2)
		: m(m), t(t), m1(m1), t1(t1), m2(m2), t2(t2), m_now(0)
	{};
};

void process(const std::vector<pooldata>&d, std::vector<int>&res)
{
	for (int it = 0; it < d.size(); it++)
	{
		bool isopen1 = true,isopen2 = true;
		for (int time = 0,time1 = 0,time2 = 0; time < d[it].t; time++,time1++,time2++)
		{
			if (time1 == d[it].t1)
			{
				isopen1 ? isopen1 = false : isopen1 = true;
				time1 = 0;
			}
			if (time2 == d[it].t2)
			{
				isopen2 ? isopen2 = false : isopen2 = true;
				time2 = 0;
			}

			if (isopen1 && (!isopen2))
				res[it] += d[it].m1;
			else if ((!isopen1) && isopen2)
			{
				res[it] -= d[it].m2;
			}
			else if (isopen1 && isopen2)
			{
				res[it] += d[it].m1 - d[it].m2;
			}
			
			if (res[it] < 0)
				res[it] = 0;
			else if (res[it] > d[it].m)
				res[it] = d[it].m;
		}
	}
}

int main()
{
	int group;
	std::cin >> group;
	std::vector<pooldata>d(group);
	std::vector<int>res(group);
	for (int i = 0; i < group; i++)
		std::cin >> d[i].m >> d[i].t >> d[i].m1 >> d[i].t1 >> d[i].m2 >> d[i].t2;
	process(d, res);
	for (auto i : res)
		std::cout << i << std::endl;
	/*for (auto i : d)
		std::cout << i.m << " " << i.t << " " << i.m1 << " " << i.t1 << " " << i.m2 << " " << i.t2 << std::endl;*/
	while (1);
	return 0;
}