/*�ٶ�һ�ֱ���ı��뷶Χ��a ~ y��25����ĸ����1λ��4λ�ı��룬������ǰѸñ��밴�ֵ��������γ�һ���������£� a, aa, aaa, aaaa, aaab, aaac, �� ��, b, ba, baa, baaa, baab, baac �� ��, yyyw, yyyx, yyyy ����a��IndexΪ0��aa��IndexΪ1��aaa��IndexΪ2���Դ����ơ� ��дһ������������������һ�����룬�����������Ӧ��Index.

��������:

����һ����������ַ���,�ַ�������С�ڵ���100.


�������:

�����������index


��������1:

baca


�������1:

16331

*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
//�ֽ���a aa aaa aaaa aaab...aaay aab aaba...aaby...aay aaya...aayy ab aba abaa...abay abb abba...abby...aby abya...abyy ac aca acaa...ay aya ayaa...ayay ayb ayba...aybay...ayyy b...yyyy
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

