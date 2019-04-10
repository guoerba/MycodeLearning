#pragma once
extern void swap_with_zero(int* array, int len, int n);
extern void swap(int &a, int &b);
class Solution
{
public:
	Solution();
	~Solution();
	void sort(int* array, int len) {
		for (int i = 0; i < len; i++)
		{
			swap_with_zero(array, len, *(array + i));
			swap_with_zero(array, len, i);
		}
	}
	/*Solution s;
	s.sort(tarray, 10);
	for (int i = 0; i < 10; i++)
		std::cout << tarray[i] << ' ';
	std::cout << std::endl;*/
};

