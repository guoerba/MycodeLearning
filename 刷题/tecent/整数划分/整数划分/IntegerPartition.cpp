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
	/*int **dp = CreateArray2D<int>(n + 1, k + 1,0);//dp[n][k]表示整数n的划分中，每个数不大于k的划分数
	for (int j = 1; j <= k; j++)
	{
		//dp[0][j] = 1;
		dp[1][j] = 1;//1的不大于j的划分数（1）
		dp[j][1] = 1;//j的不大于1的划分数（1+1+1+...+1(j个1)）
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
	return ret;
}

int IntegerPartition::Partition_K(int n, int k)
{ //设dp[n][k]为将n划分为k个整数的划分个数。
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
				dp[i][j] = dp[i - j][j] + dp[i - 1][j - 1];/*方法可以分为两类：
   　　第一类: n 份中不包含 1 的分法，为保证每份都 >= 2，可以先拿出 k 个 1 分。到每一份，然后再把剩下的 n- k 分成 k 份即可，分法有: dp[n-k][k]
  　　 第二类: n 份中至少有一份为 1 的分法，可以先那出一个 1 作为单独的1份，剩下的 n- 1 再分成 k- 1 份即可，分法有：dp[n-1][k-1]
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
	std::cout << "最后的答案是：" << dp[n][k] << std::endl;
	return ret;
}
