#include <iostream>
#include <string>
#include <vector>

typedef unsigned int uint;

int test(const std::vector<int>&generator, int floor)
{
	std::vector<std::vector<int>>group;
	std::vector<int>alive;
	for (int i = 0; i < generator.size(); i++)
	{	
		if (generator[i] <= floor)
		{
			if (alive.size())
			{
				group.push_back(alive);
				alive.clear();
			}
		}
		else
		{
			alive.push_back(generator[i]);
		}
	}
	return group.size();
}

int main()
{
	int ng,nf;
	std::vector<int>ngs,nfs;
	std::vector<std::vector<int>>generators,floors;
	while (std::cin >> ng)
	{
		std::vector<int>generator(ng);
		for (int i = 0; i < ng; i++)
			std::cin >> generator[i];
		generator.push_back(-1);
		generators.push_back(generator);
		std::cin >> nf;
		nfs.push_back(nf);
		std::vector<int>floor(nf);
		for (int i = 0; i < nf; i++)
			std::cin >> floor[i];
		floors.push_back(floor);
	}

	for (int j = 0; j < generators.size(); j++)
	{
		for (int i = 0; i < nf; i++)
		{
			std::cout << test(generators[j], floors[j][i]) << std::endl;
		}
	}
	while (1);
	return 0;
}