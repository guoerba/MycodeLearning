#include <iostream>
#include "StringIntegration.h"
#include "StringIntOperationTest.h"

int main()
{
	StringIntOperationTest st(1,100000);
	std::cout << st.RunTest() << std::endl;
	
	//std::cout << (StringIntegration("0960") > StringIntegration("960")) << std::endl;
	//std::cout << (StringIntegration("13802") / StringIntegration("2")).string() << std::endl;
	//std::cout << (s > ss) << std::endl;
	while (1);
	return 0;
}