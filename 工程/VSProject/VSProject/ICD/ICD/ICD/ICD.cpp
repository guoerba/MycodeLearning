// ICD.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

#define FILENAME	"./res/Section111ValidICD10-2018.csv"

int main()
{
	char filename[65535] = {0};
	std::cout << "please input ICD file name(which suffix is like \".csv\" ): ";
	std::cin >> filename;
	std::cout << filename;
	std::cout << std::endl;

	ICDHandler icd(filename, std::ios::in);	

	int cmd = 0;
	char ss[20];
	while(1)
	{
		std::cout << "0 end\n1 search for ICD code(s) (e.g.G4453)\n2 search for diagnosis(s) (e.g. angina, Ebola, horse, Malaria, wheelchair)\n>> ";
		std::cin >> cmd;
		if (cmd != 1 && cmd != 2 && cmd != 0)
		{
			std::cout << "command is wrong!" << std::endl;
			continue;
		}

		std::cout << std::endl;
		std::cout << "to search for diagnosis: ";
		std::cin >> ss;
		
	    const char *s = ss;
		if (cmd == 1)
			icd.Search(s);
		else if (cmd == 2)
			icd.Search(s, ICDHandler::description);
		else if (cmd == 0)
			break;
		
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
