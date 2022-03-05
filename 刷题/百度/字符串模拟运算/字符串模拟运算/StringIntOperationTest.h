#pragma once
#include "StringIntegration.h"
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include <iostream>

struct ActualRes {
	int a;
	int b;
	int sum;
	int difference;
	int product;
	int quotient;
	ActualRes() :a(0), b(0), sum(0), difference(0), product(0), quotient(0) {}
	ActualRes(int a, int b) :a(a), b(b), sum(a+b), difference(a-b), product(a*b), quotient(a/b) {}
};

class StringIntOperationTest
{
public:
	StringIntOperationTest();
	StringIntOperationTest(int range);
	StringIntOperationTest(int lower, int upper);
	~StringIntOperationTest();

	String RunTest();//进行综合测试并打印出结果
private:
	int emergerand(int upper, int lower);
	std::vector<ActualRes> rdata;
};

