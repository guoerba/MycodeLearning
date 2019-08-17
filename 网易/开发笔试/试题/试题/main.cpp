#include <iostream>
#include <string>
#include <vector>

typedef unsigned int uint;

int findonenum(uint num)
{
	int onenum = 0;
	while (num)
	{
		if (num % 2)
			++onenum;
		num /= 2;
	}
	return onenum;
}

uint findclassnum( std::vector<uint>&d)
{
	std::vector<uint>classnum;
	for (int it = 0; it < d.size(); ++it)
	{
		uint num = findonenum(d[it]);
		bool flag = false;
		for (int i = 0; i < classnum.size(); i++)
		{
			if (num == classnum[i])
				flag = true;
		}
		if (!flag)
			classnum.push_back(num);
	}
	uint size = classnum.size();
	return size;
}

int main()
{
	uint group;
	std::cin >> group;
	std::vector<uint>length(group);
	std::vector<std::vector<uint>>d(group);
	for (uint i = 0; i < group; i++)
	{
		std::cin >> length[i];
		std::vector<uint>tmp(length[i]);
		for (uint j = 0; j < length[i]; j++)
			std::cin >> tmp[j];
		d[i] = tmp;
	}

	/*for (auto i : d)
	{
		for (auto j : i)
			std::cout << findonenum(j) << " ";
		std::cout << std::endl;
	}*/

	std::vector<uint>classnum;
	for (int i = 0; i < d.size(); i++)
		classnum.push_back(findclassnum(d[i]));

	
	for (int i = 0; i < classnum.size(); i++)
		std::cout << classnum[i] << std::endl;

	while (1);

	return 0;
}