#include "IntegerPartition.h"



IntegerPartition::IntegerPartition(int i,Type type)
	: type(type)
{
	switch (type)
	{
	case IntegerPartition::k1:
		PartitionK1(i);
		break;		
	case IntegerPartition::k2:
		PartitionK2(i);
		break;
	case IntegerPartition::k3:
		PartitionK3(i);
		break;
	case IntegerPartition::k4:
		PartitionK4(i);
		break;
	case IntegerPartition::k5:

		break;
	default:
		break;
	}
}

IntegerPartition::IntegerPartition(int i, int k, Type type)
{
	Partition_K(i, k);
}


IntegerPartition::~IntegerPartition()
{
	if (dp)
	{
		DeleteArray2D(dp);
		dp = 0;
	}
}

int IntegerPartition::PartitionK1(int i)
{
	return Partition(i,i);
}
int IntegerPartition::PartitionK2(int i)
{
	return 0;
}
int IntegerPartition::PartitionK3(int i)
{
	return 0;
}
int IntegerPartition::PartitionK4(int i)
{
	return 0;
}

int IntegerPartition::PartitionK5(int i, int k)
{
	Partition(i, k);
	return 0;
}

int IntegerPartition::Partition(int n, int k)
{
	/*int **dp = CreateArray2D<int>(n + 1, k + 1,0);//dp[n][k]��ʾ����n�Ļ����У�ÿ����������k�Ļ�����
	for (int j = 1; j <= k; j++)
	{
		//dp[0][j] = 1;
		dp[1][j] = 1;//1�Ĳ�����j�Ļ�������1��
		dp[j][1] = 1;//j�Ĳ�����1�Ļ�������1+1+1+...+1(j��1)��
	}*/
	dp = CreateArray2D<int>(n + 1, k + 1, [](int row, int col)->int{
		if (row == 1 && col)
			return 1;
		else if (col == 1 && row)
			return 1;
		else
			return 0;
	});
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < k + 1; j++)
		{
			std::cout << dp[i][j] << " ";
		}
		std::cout << std::endl;
	}
		
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= k; j++)
		{
			if (i < j)
				dp[i][j] = dp[i][i];
			else if (i > j)//������ÿ������С�� j���൱��ÿ���������� j- 1, �ʻ�����Ϊ dp[i][j-1].
			{//��������һ����Ϊ j. �Ǿ��� i�м�ȥ j ,ʣ�µľ��൱�ڰ� i-j ���л��֣� �ʻ�����Ϊ dp[i-j][j];
				dp[i][j] = dp[i - j][j] + dp[i][j - 1];
			}
			else if(i == j)
				dp[i][j] = dp[i][j - 1] + 1;
		}
	}
	int ret = dp[n][k];
	std::cout << "n: " << n << " k: " << k << std::endl;
	for (int i = 0; i < n+1; i++)
	{
		for (int j = 0; j < k+1; j++)
		{
			std::cout << dp[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "���Ĵ��ǣ�" << dp[n][k] << std::endl;
	return ret;
}

int IntegerPartition::Partition_K(int n, int k)
{ //��dp[n][k]Ϊ��n����Ϊk�������Ļ��ָ�����
	dp = CreateArray2D<int>(n + 1, k + 1, [](int row, int col)->int {
		if (row == col)
			return 1;
		else if (row < col)
			return 0;
		else if (col == 1)
			return 1;
		else
			return 0;
	});
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < k + 1; j++)
		{
			std::cout << dp[i][j] << " ";
		}
		std::cout << std::endl;
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= k; j++)
		{
			if(i > j)
				dp[i][j] = dp[i - j][j] + dp[i - 1][j - 1];/*�������Է�Ϊ���ࣺ
   ������һ��: n ���в����� 1 �ķַ���Ϊ��֤ÿ�ݶ� >= 2���������ó� k �� 1 �֡���ÿһ�ݣ�Ȼ���ٰ�ʣ�µ� n- k �ֳ� k �ݼ��ɣ��ַ���: dp[n-k][k]
  ���� �ڶ���: n ����������һ��Ϊ 1 �ķַ����������ǳ�һ�� 1 ��Ϊ������1�ݣ�ʣ�µ� n- 1 �ٷֳ� k- 1 �ݼ��ɣ��ַ��У�dp[n-1][k-1]
*/
		}
	}
	int ret = dp[n][k];
	std::cout << "n: " << n << " k: " << k << std::endl;
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < k + 1; j++)
		{
			std::cout << dp[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "���Ĵ��ǣ�" << dp[n][k] << std::endl;
	return ret;
}
