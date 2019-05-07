#include <iostream>
#include "StringIntegration.h"


int main()
{
	StringIntegration s("25");
	//String r = (s + );
	//s *= String("-24");
	StringIntegration ss("5");
	std::cout << (s - ss).string() << std::endl;
	std::cout << (StringIntegration("10001") - StringIntegration("2")).string() << std::endl;
	//std::cout << s.string() << std::endl;
	//std::cout << (StringIntegration("20") + String("39")).string() << std::endl;
	//std::cout << (--ss).string() << std::endl;
	std::cout << (StringIntegration("300") / StringIntegration("7")).string() << std::endl;
	//std::cout << (s > ss) << std::endl;
	while (1);
	return 0;
}