/*计算a+b的和
每行包含两个整数a和b

对于每行输入对应输出一行a和b的和

输入

1 5

输出

6*/
#include <iostream>
#include <vector>
#include <string>
#include "Solution.h"

int tarray[] = { 3,5,2,8,6,0,9,4,7,1 };

struct input {
	int a;
	int b;
};

void TestInput()
{
	int a, b;
	std::vector<input>InputData;
	while (std::cin >> a >> b)
	{
		input i;
		i.a = a, i.b = b;
		InputData.push_back(i);
	}
	for (auto i : InputData)
	{
		std::cout << i.a + i.b << std::endl;
	}
}

int main()
{
	/*int s;
	int flag = false;
	while (!(flag = (std::cin >> s).eof()))
	{
		std::cout << flag << std::endl;
	}
	std::cout << flag << std::endl;
	std::cout << "out" << std::endl;*/
	std::string str;
	char s[256] = { 0 };
	while (!std::cin.getline(s, 256).eof())
	{
		str.append(s);
		for (int i = 0; i < 256; i++)
			s[i] = 0;
	}
	std::cout << str << std::endl;
	while (1);
	return 0;
}