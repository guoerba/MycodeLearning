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
	case	Complete:res = findcompletenumber(n, num);					//��n���ֳɲ�����m�Ļ��ַ�
		break;
	case	DifferentResult:finddifferent(n, num, temp, ares);
	case	Different:res = finddifferentnumber(n, num);				//���ֶ����ͬ������
		break;
	case	FixedCountResult://findfixedcount(n, num);
	case	FixedCount:res = findfixedcountnumber(n, num);			//n���ֳ�k�����Ļ��ַ�
		//break;
	case	OddResult:
	case	Odd:						//n���ֳ����������Ļ��ַ�
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
			else if (i > j)//������ÿ������С�� j���൱��ÿ���������� j- 1, �ʻ�����Ϊ dp[i][j-1].
			{//��������һ����Ϊ j. �Ǿ��� i�м�ȥ j ,ʣ�µľ��൱�ڰ� i-j ���л��֣� �ʻ�����Ϊ dp[i-j][j];
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
	if (n <= 0)//����������Ϊ�������ȷ�˵m��0����������������Ǿ�ֱ�ӷ���
		return;
	if (m <= 0)//����������0��ʱ��ͷ��ؽ�������ݵݹ�
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
		findcomplete(n, m - n, temp, res);//��n��m�Ļ����������������Ҫ��¼n��������m-n��n����
		//temp.pop_back();
		temp.resize(temp.size() - s.size());
		findcomplete(n - 1, m, temp, res);//��n����m�Ļ����������������Ҫ��¼n��������m��n-1����
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
			else if (i > j)//������ÿ������С�� j���൱��ÿ���������� j-1, �ʻ�����Ϊ dp[i][j-1].
			{//��������һ����Ϊ j. �Ǿ��� i�м�ȥ j ,ʣ�µľ��൱�ڰ� i-j ����j-1���֣� �ʻ�����Ϊ dp[i-j][j-1];
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
		if (row == col)//i���Ի���Ϊi��1֮��
			return 1;
		else if (row < col)//�����ܳ��ֵ����
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
				dp[i][j] = dp[i - j][j] + dp[i - 1][j - 1];/*�������Է�Ϊ���ࣺ
   ������һ��: n ���в����� 1 �ķַ���Ϊ��֤ÿ�ݶ� >= 2���������ó� k �� 1 �֡���ÿһ�ݣ�Ȼ���ٰ�ʣ�µ� n- k �ֳ� k �ݼ��ɣ��ַ���: dp[n-k][k]
  ���� �ڶ���: n ����������һ��Ϊ 1 �ķַ����������ǳ�һ�� 1 ��Ϊ������1�ݣ�ʣ�µ� n- 1 �ٷֳ� k- 1 �ݼ��ɣ��ַ��У�dp[n-1][k-1]
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
	findfixedcount(n - 1, m - 1, temp, res);//��һ��Ϊ1
	for (int i = 0; i < n; i++)
		temp[i] += 1;
	findfixedcount(n , m - n, temp, res);//������1
}


