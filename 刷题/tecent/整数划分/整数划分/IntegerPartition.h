#pragma once
#include "MemAlloc.h"
#include <iostream>
class IntegerPartition
{
public:
	enum Type {
		k1,//求将n划分为若干正整数之和的划分数 (划分的多个整数可以相同)
		k2,//求将n划分为若干正整数之和的划分数 (划分的正整数必须不同)
		k3,//将n划分为k个整数的划分数
		k4,//将n划分为若干正奇数之和的划分数
		k5,//将n划分为不大于k的划分数
	}type;
	IntegerPartition(int i, Type type);
	IntegerPartition(int i, int k, Type type);
	~IntegerPartition();
	int PartitionK1(int i);
	int PartitionK2(int i);
	int PartitionK3(int i);
	int PartitionK4(int i);
	int PartitionK5(int i, int k);
private:
	int Partition(int i, int k);
	int Partition_K(int i, int k); //将n划分为k个整数的划分数
	int **dp;
};
