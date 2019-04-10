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
	default:
		break;
	}
}


IntegerPartition::~IntegerPartition()
{
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

int IntegerPartition::Partition(int n, int k)
{
	int **dp = CreateArray2D<int>(n + 1, k + 1,0);//dp[n][k]表示整数n的划分中，每个数不大于k的划分数
	std::vector<int> **s = CreateArray2D<int>(n + 1, k + 1);
	for (int j = 1; j <= k; j++)
	{
		//dp[0][j] = 1;
		dp[1][j] = 1;//1的不大于j的划分数（1）
		dp[j][1] = 1;//j的不大于1的划分数（1+1+1+...+1(j个1)）
	}
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
			else if (i > j)//划分中每个数都小于 j，相当于每个数不大于 j- 1, 故划分数为 dp[i][j-1].
			{//划分中有一个数为 j. 那就在 i中减去 j ,剩下的就相当于把 i-j 进行划分， 故划分数为 dp[i-j][j];
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
	std::cout << "最后的答案是：" << dp[n][k] << std::endl;
	DeleteArray2D(dp);
	return ret;
}