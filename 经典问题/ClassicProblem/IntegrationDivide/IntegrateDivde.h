#pragma once
#include "../include/alloc2darray.h"
#include "../include/StringIntegration.h"
#include "../include/stringoperation.h"
#pragma comment(lib,"..//lib//alloc2darray.lib")


class IntegrateDivde
{
public:
	enum Type {
		CompleteResult,				//所有结果
		Complete,					//将n划分成不大于m的划分法
		DifferentResult,
		Different,					//划分多个不同的整数
		FixedCountResult,
		FixedCount,					//n划分成k个数的划分法
		OddResult,
		Odd,						//n划分成若干奇数的划分法
	};
	IntegrateDivde();
	IntegrateDivde(int num,Type t = Complete);
	IntegrateDivde(int num,int n, Type t = Complete);
	~IntegrateDivde();

	int result();
	std::string results();
private:
	int findcompletenumber(int n, int m);
	void findcomplete(int n, int m, std::string&temp, std::string&res);//找到m的n划分
	//求出整数的划分，要求划分数各不相同
	int finddifferentnumber(int n, int m);
//item:临时数组；res:结果数组；n:m的n划分 m:要求的整数
	void finddifferent(int n, int m, std::string&temp, std::string&res);//支持m大于9的版本

	int findfixedcountnumber(int n, int m);
	void findfixedcount(int n, int m);
	void findfixedcount(int n, int m, std::vector<int>&temp, std::string&res);

	

	int integrate,divide;
	int res;
	
	std::string temp;
	std::string ares;
};

