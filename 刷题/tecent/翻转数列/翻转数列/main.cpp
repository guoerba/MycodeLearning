/*СQ������һ�����г�Ϊ��ת����:
��������n��m, ����n�ܱ�2m����������һ������������������1, 2, 3, 4..., ÿ��m�����ŷ�תһ��, �������Ϊ'-';��
����n = 8, m = 2, ���о���: -1, -2, +3, +4, -5, -6, +7, +8.
��n = 4, m = 1, ���о���: -1, +2, -3, + 4.
СQ����ϣ�����ܰ�������ǰn���Ϊ���١�
��������:

���������������n��m(2 <= n <= 109, 1 <= m), ��������n�ܱ�2m������


�������:

���һ������, ��ʾǰn��͡�


��������1:

8 2


�������1:

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
/*����ѧ�������Խ�������ӣ�https://www.nowcoder.com/questionTerminal/cc0a71a1dfdb4c64a3ffe000f71ae12c
��Դ��ţ����

���ȹ۲����У����ǿ��Խ�һ�鸺���������֣��� - 1�� - 2, 3, 4������һ�飬��n����һ����n / (2m)�飬��ÿһ����ͽ��Ϊm*m��

���ǵõ�ǰn��͹�ʽΪSn = n * m*m / 2m = m * n / 2*/