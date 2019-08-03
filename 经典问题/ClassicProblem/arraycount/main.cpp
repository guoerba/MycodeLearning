/*题目描述
已知一个正整数n，(3 <= n <= 15)，将所有n的乘方幂以及所有n的乘方幂（有限个且互不相等）之和组成一个递增序列。例如，当n为4时，该序列为：
1, 4, 5, 16, 17, 20, 21……
(4^0, 4^1, 4^0+4^1, 4^2, 4^0+4^2, 4^1+4^2, 4^0+4^1+4^2……)
请求出该序列的第K项(10进制)。
输入描述:

输入只有1行，为2个正整数，两数之间用一个空格隔开：
n K
(n, K的含义与上述描述一致, 且3<=n<=15, 10<=K<=1000)。

输出描述:

输出为计算结果，为一个正整数（注意在所有测试数据中，结果均不会超过2.1*10^9）。整数前不要有空格或其他任何符号。

示例1
输入
复制

3 100

输出
复制

981

*/
#include "../include/alloc2darray.h"
#include "../include/StringIntegration.h"
#include "../include/stringoperation.h"
#pragma comment(lib,"..//lib//alloc2darray.lib")


//函数返回值是容器的执行速度比容器作为参数传递要慢的多。

//可以看到返回容器的函数里，容器频繁的创建销毁。

//容器作为参数传递是项目中常见做法，很少看到函数返回容器。
void findpartition(int n, int m, std::string&temp, std::string&res)//找到m的n划分
{
	if (n <= 0)//划分数必须为正数；比方说m的0划分这种情况，我们就直接返回
		return;
	if (m <= 0)//当总数等于0的时候就返回结果并回溯递归
	{
		res.append(temp);
		res.push_back(';');
		return;
	}
	if (m < n)
		findpartition(m, m, temp, res);
	else
	{
		//temp.push_back(n + 48);
		std::string s = std::to_string(n) + " ";
		temp.append(s);
		findpartition(n, m - n, temp, res);//当n是m的划分数的情况，则需要记录n，并查找m-n的n划分
		//temp.pop_back();
		temp.resize(temp.size() - s.size());
		findpartition(n - 1, m, temp, res);//当n不是m的划分数的情况，则不需要记录n，并查找m的n-1划分
	}
}

//求出整数的划分，要求划分数各不相同
//item:临时数组；res:结果数组；n:m的n划分 m:要求的整数
void findcomb(std::string&item, int n, int m, std::string&res)
{
	if (n <= 0 || m <= 0)//递归停止条件，当划分n或总数m小于零，说明此次选择是错误的，直接回溯
		return;
	if (n == m)//当划分n等于总数时，说明此次选择是正确的，将n和之前的测试通过数加入到结果集中
	{
		res.append(item);
		res.push_back(n + 48);
		res.push_back(';');
	}
	item.push_back(n + 48);
	findcomb(item, n - 1, m - n, res);//试验当n是和为m的组合数的情况
	item.pop_back();//试验完成 弹出n
	findcomb(item, n - 1, m, res);//试验当n不是m的组合数的情况
}
void findcombn(int n, int m, std::string&temp, std::string&res)//支持m大于9的版本
{
	if (n <= 0 || m <= 0)
		return;
	if (n == m)
	{
		res.append(temp);
		res.append(std::to_string(n) + " ;");
	}
	std::string s = std::to_string(n) + " ";
	temp.append(s);
	findcombn(n - 1, m - n, temp, res);
	temp.resize(temp.size() - s.size());
	findcombn(n - 1, m, temp, res);
}
/*std::string item, result;
	findcomb(item, 3, 3, result);
	std::cout << result << std::endl;*/

void generatearray(int num,std::vector<std::string>&sb)
{
	if (!num)
	{
		sb.push_back(std::string("0"));
		return;
	}

	if (num == 1)
	{
		sb.push_back(std::string("1"));
		sb.push_back(std::string("10"));
		return;
	}

	int sum = 0;
	for (int i = 0; i < num; i++)
		sum += i;
	//std::cout << "sum: " << sum << std::endl;
	std::string result;

	for (int i = 1; i <= sum; i++)
	{
		std::string item, res;
		findcomb(item, num - 1, i, res);
		result.append(res);
	}

	//std::cout << result << std::endl;
	std::vector<std::string> sb1;
	StringOperation::split(result, sb, ';');
	for (auto i = sb.begin(); i != sb.end(); i++)
	{
		(*i).insert(0, 1, num + 48);
		std::string tmp(*i);
		tmp.push_back(48);
		sb1.push_back(tmp);
	}
	sb.insert(sb.cend(), sb1.begin(), sb1.end());

	std::string init;
	init += (num + 48);
	sb.push_back(init);
	init += '0';
	sb.push_back(init);

	std::sort(sb.begin(), sb.end());
	/*for (auto i : sb)
		std::cout << i << " ";
	std::cout << std::endl;*/
}

int main()
{
	/*int n, K;
	std::cin >> n >> K;
	int i = -1;
	while (pow(2, ++i) <= K);
	int baseindex = pow(2, --i);
	//std::cout << baseindex << " " << i << std::endl;
	std::vector<std::string> a;
	generatearray(i, a);
	std::string result = a[K - baseindex];
	//std::cout << result << std::endl;
	int sum = 0;
	for (auto it = result.begin(); it != result.end(); it++)
		sum += pow(n, *it - 48);
	std::cout << sum << std::endl;*/

	std::string tmp, res;
	findcombn(10, 10,tmp, res);
	std::cout << res << std::endl;
	/*std::string tmp, res;
	findpartition(15, 15, tmp, res);
	std::cout << res << std::endl;*/
	while (1);
	return 0;
}

/*#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>

void split(std::string &str, std::vector<std::string>&strs, char c)
{
	bool flag = false;
	if (str[str.size() - 1] != c)
	{
		str.push_back(c);
		flag = true;
	}		
	std::string tmp;
	for (auto it = str.begin(); it != str.end(); it++)
	{
		if (*it == c)
		{
			strs.push_back(tmp);
			tmp.clear();
		}
		else
			tmp.push_back(*it);
	}
	if(flag)
		str.pop_back();
}

void findcomb(std::string&item, int n, int m, std::string&res)
{
	if (n <= 0 || m <= 0)
		return;
	if (n == m)
	{
		res.append(item);
		res.push_back(n + 48);
		res.push_back(';');
	}
	item.push_back(n + 48);
	findcomb(item, n - 1, m - n, res);
	item.pop_back();
	findcomb(item, n - 1, m, res);
}

void generatearray(int num, std::vector<std::string>&sb)
{
	if (!num)
	{
		sb.push_back(std::string("0"));
		return;
	}

	if (num == 1)
	{
		sb.push_back(std::string("1"));
		sb.push_back(std::string("10"));
		return;
	}

	int sum = 0;
	for (int i = 0; i < num; i++)
		sum += i;
	std::string result;

	for (int i = 1; i <= sum; i++)
	{
		std::string item, res;
		findcomb(item, num - 1, i, res);
		result.append(res);
	}

	std::vector<std::string> sb1;
	split(result, sb, ';');
	for (auto i = sb.begin(); i != sb.end(); i++)
	{
		(*i).insert(0, 1, num + 48);
		std::string tmp(*i);
		tmp.push_back(48);
		sb1.push_back(tmp);
	}
	sb.insert(sb.cend(), sb1.begin(), sb1.end());

	std::string init;
	init += (num + 48);
	sb.push_back(init);
	init += '0';
	sb.push_back(init);

	std::sort(sb.begin(), sb.end());
}

int main()
{
	int n, K;
	std::cin >> n >> K;
	int i = -1;
	while (pow(2, ++i) <= K);
	int baseindex = pow(2, --i);
	std::vector<std::string> a;
	generatearray(i, a);
	std::string result = a[K - baseindex];
	int sum = 0;
	for (auto it = result.begin(); it != result.end(); it++)
		sum += pow(n, *it - 48);
	std::cout << sum << std::endl;
	return 0;
}*/