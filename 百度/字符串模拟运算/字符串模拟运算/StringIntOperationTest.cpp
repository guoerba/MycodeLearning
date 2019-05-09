#include "StringIntOperationTest.h"
#include <stdio.h>


StringIntOperationTest::StringIntOperationTest()
{
}

StringIntOperationTest::StringIntOperationTest(int range)
{
	StringIntOperationTest(1, range);
}

StringIntOperationTest::StringIntOperationTest(int lower, int upper)
{
	// std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
	 auto seed = std::chrono::seconds(std::time(NULL)).count();
	 srand(seed);
	 int size = upper - lower;
	 rdata.resize(size);
	 for (int i = 0; i < size; i++)
	 {
		 int a = emergerand(upper, lower);
		 rdata[i] = ActualRes(a+1, emergerand(a , lower));
	 }
		 		
}

StringIntOperationTest::~StringIntOperationTest()
{
	rdata.clear();
}

String StringIntOperationTest::RunTest()
{
	String ret;
	//ret.append("---------------------------------------------\n");
	std::cout << "处理中..." << std::endl;
	for (int i = 0; i < rdata.size(); i++)
	{
		String a = std::to_string(rdata[i].a),b = std::to_string(rdata[i].b);
		String c = (StringIntegration(a) + StringIntegration(b)).string();
		//printf("正在验证第%d个组合：\t%d + %d = %d,%d\n",i, rdata[i].a, rdata[i].b, rdata[i].sum, std::stoi(c));
 		if (std::stoi(c) != rdata[i].sum)
			ret.append(a + '+' + b + "是错的！计算答案为:" + c + "; 正确答案为:" + std::to_string(rdata[i].sum) + '\n');
		c.clear();
		c = (StringIntegration(a) - StringIntegration(b)).string();
		//printf("正在验证第%d个组合：\t%d - %d = %d,%d\n", i, rdata[i].a, rdata[i].b, rdata[i].difference, std::stoi(c));
		if (std::stoi(c) != rdata[i].difference)
			ret.append(a + '-' + b + "是错的！计算答案为:" + c + "; 正确答案为:" + std::to_string(rdata[i].difference) + '\n');
		c.clear();
		c = (StringIntegration(a) * StringIntegration(b)).string();
		//printf("正在验证第%d个组合：\t%d * %d = %d,%d\n", i, rdata[i].a, rdata[i].b, rdata[i].product, std::stoi(c));
		if (std::stoi(c) != rdata[i].product)
			ret.append(a + '*' + b + "是错的！计算答案为:" + c + "; 正确答案为:" + std::to_string(rdata[i].product) + '\n');
		c.clear();
		c = (StringIntegration(a) / StringIntegration(b)).string();
		//printf("正在验证第%d个组合：\t%d / %d = %d,%d\n", i, rdata[i].a, rdata[i].b, rdata[i].quotient, std::stoi(c));
		if (std::stoi(c) != rdata[i].quotient)
			ret.append(a + '/' + b + "是错的！计算答案为:" + c + "; 正确答案为:" + std::to_string(rdata[i].quotient) + '\n');
		//ret.append("---------------------------------------------\n");
	}
	if (ret.empty())
		ret.append("全部正确\n");
	return ret;
}

int StringIntOperationTest::emergerand(int upper, int lower)
{
	return rand() % (upper - lower + 1) + lower;
}
