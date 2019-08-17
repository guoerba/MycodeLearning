#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

typedef unsigned int uint;

int main()
{
	int n;
	std::cin >> n;
	std::vector<int>man(n + 2);
	for (int i = 1; i <= n; i++)
		std::cin >> man[i];
	man[0] = 0;
	man[man.size() - 1] = 0;
	std::vector<int>manc = man;
	manc.erase(manc.begin());
	manc.resize(manc.size() - 1);

	std::sort(manc.begin(), manc.end());
	int min = manc[0];
	
	int index;
	for (int i = 0; i < man.size(); i++)
	{
		if (man[i] == min)
		{
			index = i;
			break;
		}
	}
	
	int sum = 100,price = 100;
	for (int i = index; i < n; i++)
	{
		if (man[i + 1] > man[i])
			price += 100;
		else
			price -= 100;
		if (price < 100)
			price = 100;
		sum += price;
	}
	price = 100;
	for (int i = index; i > 1; i--)
	{
		if (man[i - 1] > man[i])
			price += 100;
		else
			price -= 100;
		if (price < 100)
			price = 100;
		sum += price;
	}
	std::cout << sum << std::endl;

	while (1);
}