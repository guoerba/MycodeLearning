#include "../include/alloc2darray.h"
#include "../include/StringIntegration.h"
#include "../include/stringoperation.h"
#pragma comment(lib,"..//lib//alloc2darray.lib")

int main()
{
	int n;
	std::cin >> n;
	std::vector<int>a(n);
	for (int i = 0; i < n; i++)
		std::cin >> a[i];

	
	while (1);
	return 0;
}

int childarraysum(const std::vector<int>&a, int l, int r)
{
	if (l < r)
	{
		int mid = (l + r) / 2;
		int lmax = childarraysum(a, l, mid);
		int rmax = childarraysum(a, mid + 1, r);
		int max = lmax > rmax ? lmax: rmax;

	}
	return 0;
}