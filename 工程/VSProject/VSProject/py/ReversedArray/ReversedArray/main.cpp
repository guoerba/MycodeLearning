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

 long long reverse( long long a)
{
	return ~a + 1;
}

 void old()
 {
	 long long m, n;
	 scanf_s("%lld %lld", &n, &m);
	 bool flag = false;
	 long long sum = 0;
	 for (long long i = 1, j = 0; i <= n; i++, j++)
	 {
		 if (m == j)
		 {
			 j = 0;
			 if (flag)
				 flag = false;
			 else
				 flag = true;
		 }
		 if (!flag)
		 {
			 //printf("%lld\n", reverse(i));
			 sum += reverse(i);
		 }
		 else
		 {
			 //printf("%lld\n", i);
			 sum += i;
		 }
	 }
	 printf("%lld", sum);
	 while (1);
 }//��ʱ

int main()
{
	long long n, m;
	scanf_s("%lld %lld", &n, &m);
	bool flag = false;
	long long sum = 0;
	for (long long i = 1; i <= n; i += m)
	{
		for (long long j = 0; j < m; j++)
		{
			flag ? sum += i + j : sum += reverse(i+j);		
		}
		flag ? flag = false : flag = true;
	}
	printf("%lld", sum);
	while (1);
}