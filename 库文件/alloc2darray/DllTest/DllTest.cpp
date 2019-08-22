// DllTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "../alloc2darray/alloc2darray.h"
#include "../alloc2darray/StringIntegration.h"
#include "../alloc2darray/stringoperation.h"
#include "../alloc2darray/MSort.h"
#include <iostream>

#pragma comment(lib,"..\\..\\alloc2darray\\Debug\\alloc2darray.lib")
int a[] = { 4,7,2,3,9,11,1,5,8,30,59,29,10,6,7,34 };
//int a[] = { 1,4,6,8,9,2,3,5,7 };
int main()
{
   /* std::cout << "Hello World!\n"; 
	StringIntegration s("125");
	std::cout << (s + String("150")).string() << std::endl;

	std::vector<int>v;
	v.push_back(1);
	v.push_back(2);
	Array2d<std::vector<int>>*b = new Array2d<std::vector<int>>(5, 5, std::vector<int>());
	Array2d<std::vector<int>>&a = *b;
	a[0][0] = v;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::cout << "[" << i << "][" << j << "]: ";
			for (auto it = a[i][j].begin(); it != a[i][j].end(); it++)
			{
				std::cout << *it << " ";
			}
			std::cout << std::endl;
		}
	}
	delete b;

	std::vector<int>vv;
	v.swap(vv);*/

/*	std::string s("1;2;3;4");
	StringBuffer sb;
	StringOperation::split(s, sb, ';');
	std::cout << s << std::endl;
	for (auto i : sb)
		std::cout << i << std::endl;*/
	for (int i = 0; i < 16; i++)
		std::cout << a[i] << " ";
	std::cout << std::endl;
	MSort<int>s(a, 16, MSort<int>::count, [](int a, int b) {
		if (a < b)
			return true;
		else
			return false;
	});
	int *b = s.data();
	for (int i = 0; i < 16; i++)
		std::cout << b[i] << " ";
	std::cout << std::endl;
	s.free();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
