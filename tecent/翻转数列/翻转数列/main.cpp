/*小Q定义了一种数列称为翻转数列:
给定整数n和m, 满足n能被2m整除。对于一串连续递增整数数列1, 2, 3, 4..., 每隔m个符号翻转一次, 最初符号为'-';。
例如n = 8, m = 2, 数列就是: -1, -2, +3, +4, -5, -6, +7, +8.
而n = 4, m = 1, 数列就是: -1, +2, -3, + 4.
小Q现在希望你能帮他算算前n项和为多少。
输入描述:

输入包括两个整数n和m(2 <= n <= 109, 1 <= m), 并且满足n能被2m整除。


输出描述:

输出一个整数, 表示前n项和。


输入例子1:

8 2


输出例子1:

8*/
#include <iostream>
#include <stdio.h>

long long reverse(long long a)
{
	return ~a + 1;
}

int main()
{
	long long n, m;
	//scanf_s("%lld %lld", &n, &m);
	std::cin >> n >> m;
	bool flag = false;
	long long sum = 0;
	for (long long i = 1; i <= n; i += m)
	{
		for (long long j = 0; j < m; j++)
		{
			flag ? sum += i + j : sum += reverse(i + j);
		}
		flag ? flag = false : flag = true;
	}
	//printf("%lld", sum);
	std::cout << sum << std::endl;
	while (1);
}
/*用数学方法可以解决，链接：https://www.nowcoder.com/questionTerminal/cc0a71a1dfdb4c64a3ffe000f71ae12c
来源：牛客网

首先观察数列，我们可以将一组负正的数出现（如 - 1， - 2, 3, 4）看做一组，则n个数一共有n / (2m)组，而每一组求和结果为m*m，

于是得到前n项和公式为Sn = n * m*m / 2m = m * n / 2*/