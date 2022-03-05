/*假定一种编码的编码范围是a ~ y的25个字母，从1位到4位的编码，如果我们把该编码按字典序排序，形成一个数组如下： a, aa, aaa, aaaa, aaab, aaac, … …, b, ba, baa, baaa, baab, baac … …, yyyw, yyyx, yyyy 其中a的Index为0，aa的Index为1，aaa的Index为2，以此类推。 编写一个函数，输入是任意一个编码，输出这个编码对应的Index.

输入描述:

输入一个待编码的字符串,字符串长度小于等于100.


输出描述:

输出这个编码的index


输入例子1:

baca


输出例子1:

16331

*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
//字节序a aa aaa aaaa aaab...aaay aab aaba...aaby...aay aaya...aayy ab aba abaa...abay abb abba...abby...aby abya...abyy ac aca acaa...ay aya ayaa...ayay ayb ayba...aybay...ayyy b...yyyy
int main()
{
	std::string s;
	std::cin >> s;
	//int index = (s[0] - 97) * (pow(25, 3) + pow(25, 2) + pow(25, 1) + 1) + (s[1] - 97) *(pow(25, 2) + pow(25, 1) + 1) + (s[2] - 97) *(pow(25, 1) + 1) + s[3] - 97;
	int index = 0;
	for (int i = 0; i < s.size(); i++)
	{
		int c = 0;
		for (int j = 0; j < 4 - i; j++)
			c += pow(25, j);
		index++;
		index += c * (s[i] - 97) ;
	}
	std::cout << index - 1 << std::endl;
	while (1);
	return 0;
}

