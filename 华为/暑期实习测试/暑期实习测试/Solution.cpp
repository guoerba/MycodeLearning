#include "Solution.h"

void swap_with_zero(int* array, int len, int n)
{
	int index_zero, index_n;
	for (int i = 0; i < len; i++)
	{
		if (*(array + i) == 0)
			index_zero = i;
		if (*(array + i) == n)
			index_n = i;
	}
	//swap(*(array + index_zero), *(array + index_n));
	int temp = *(array + index_n);
	*(array + index_n) = *(array + index_zero);
	*(array + index_zero) = temp;
}
/*swap_with_zero(tarray, 10, 1);
	for (int i = 0; i < 10; i++)
		std::cout << tarray[i] << ' ';
	std::cout << std::endl;*/

void swap(int &a, int &b)
{
	int temp = b;
	b = a;
	a = temp;
}


Solution::Solution()
{
}


Solution::~Solution()
{
}

