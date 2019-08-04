#include "IntegrateDivde.h"


IntegrateDivde::IntegrateDivde()
{
}

IntegrateDivde::IntegrateDivde(int num, Type t)
{
	new (this)IntegrateDivde(num, num, t);
}

IntegrateDivde::IntegrateDivde(int num, int n, Type t)
	: integrate(num)
	, divide(n)
	, res(0)
	, temp(std::string())
	, ares(std::string())
{
	switch (t)
	{
	case	CompleteResult:findcomplete(n, num, temp, ares);
	case	Complete:res = findcompletenumber(n, num);					//将n划分成不大于m的划分法
		break;
	case	DifferentResult:finddifferent(n, num, temp, ares);
	case	Different:res = finddifferentnumber(n, num);				//划分多个不同的整数
		break;
	case	FixedCountResult://findfixedcount(n, num);
	case	FixedCount:res = findfixedcountnumber(n, num);			//n划分成k个数的划分法
		//break;
	case	OddResult:
	case	Odd:						//n划分成若干奇数的划分法
		//break;
	default:
		break;
	}
	//std::cout << all_res << std::endl;
}

IntegrateDivde::~IntegrateDivde()
{
	//all_res.clear();
}

int IntegrateDivde::result()
{
	return res;
}

std::string IntegrateDivde::results()
{
	return ares;
}

int IntegrateDivde::findcompletenumber(int n, int m)
{
	Array2d<int>dp(m + 1, n + 1, [](int row, int col)->int {
		if (row == 1 && col)
			return 1;
		else if (col == 1 && row)
			return 1;
		else
			return 0; });

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i < j)
				dp[i][j] = dp[i][i];
			else if (i > j)//划分中每个数都小于 j，相当于每个数不大于 j- 1, 故划分数为 dp[i][j-1].
			{//划分中有一个数为 j. 那就在 i中减去 j ,剩下的就相当于把 i-j 进行划分， 故划分数为 dp[i-j][j];
				dp[i][j] = dp[i - j][j] + dp[i][j - 1];
			}
			else if (i == j)
				dp[i][j] = dp[i][j - 1] + 1;
		}
	}
	int ret = dp[m][n];
	return ret;
}

void IntegrateDivde::findcomplete(int n, int m, std::string & temp, std::string & res)
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
		findcomplete(m, m, temp, res);
	else
	{
		//temp.push_back(n + 48);
		std::string s = std::to_string(n) + " ";
		temp.append(s);
		findcomplete(n, m - n, temp, res);//当n是m的划分数的情况，则需要记录n，并查找m-n的n划分
		//temp.pop_back();
		temp.resize(temp.size() - s.size());
		findcomplete(n - 1, m, temp, res);//当n不是m的划分数的情况，则不需要记录n，并查找m的n-1划分
	}
}

int IntegrateDivde::finddifferentnumber(int n, int m)
{
	Array2d<int>dp(m + 1, n + 1, [](int row, int col)->int {
		if (row == 1 && col)
			return 1;
		else if (col == 1 && row)
			return 1;
		else
			return 0; });

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i < j)
				dp[i][j] = dp[i][i];
			else if (i > j)//划分中每个数都小于 j，相当于每个数不大于 j-1, 故划分数为 dp[i][j-1].
			{//划分中有一个数为 j. 那就在 i中减去 j ,剩下的就相当于把 i-j 进行j-1划分， 故划分数为 dp[i-j][j-1];
				dp[i][j] = dp[i - j][j - 1] + dp[i][j - 1];
			}
			else if (i == j)
				dp[i][j] = dp[i][j - 1] + 1;
		}
	}
	int ret = dp[m][n];
	return ret;
}

void IntegrateDivde::finddifferent(int n, int m, std::string & temp, std::string & res)
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
	finddifferent(n - 1, m - n, temp, res);
	temp.resize(temp.size() - s.size());
	finddifferent(n - 1, m, temp, res);
}

int IntegrateDivde::findfixedcountnumber(int n, int m)
{
	Array2d<int>dp(m + 1, n + 1, [](int row, int col)->int {
		if (row == col)//i可以划分为i个1之和
			return 1;
		else if (row < col)//不可能出现的情况
			return 0;
		else if (col == 1)
			return 1;
		else
			return 0;
	});

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i > j)
				dp[i][j] = dp[i - j][j] + dp[i - 1][j - 1];/*方法可以分为两类：
   　　第一类: n 份中不包含 1 的分法，为保证每份都 >= 2，可以先拿出 k 个 1 分。到每一份，然后再把剩下的 n- k 分成 k 份即可，分法有: dp[n-k][k]
  　　 第二类: n 份中至少有一份为 1 的分法，可以先那出一个 1 作为单独的1份，剩下的 n- 1 再分成 k- 1 份即可，分法有：dp[n-1][k-1]
*/
		}
	}
	int ret = dp[m][n];
	return ret;
}

void IntegrateDivde::findfixedcount(int n, int m)
{
	std::vector<int>tmp(n);
	for (int i = 0; i < n; i++)
		tmp[i] = 0;
	findfixedcount(n, m, tmp, ares);
}

void IntegrateDivde::findfixedcount(int n, int m, std::vector<int> & temp, std::string & res)
{
	if (n <= 0)
	{
		for (auto it = temp.begin(); it != temp.end(); it++)
			*it = 0;
		return;
	}
	if (m <= 0)
	{
		std::string rs;
		for (auto it = temp.begin(); it != temp.end(); it++)
			rs.append(std::to_string(*it) + " ");
		res.append(rs + ";");
		for (auto it = temp.begin(); it != temp.end(); it++)
			*it = 0;
		return;
	}
	
	temp[n - 1] = 1;
	findfixedcount(n - 1, m - 1, temp, res);//有一份为1
	for (int i = 0; i < n; i++)
		temp[i] += 1;
	findfixedcount(n , m - n, temp, res);//不包含1
}


