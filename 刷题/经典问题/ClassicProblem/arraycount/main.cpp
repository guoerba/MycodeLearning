/*��Ŀ����
��֪һ��������n��(3 <= n <= 15)��������n�ĳ˷����Լ�����n�ĳ˷��ݣ����޸��һ�����ȣ�֮�����һ���������С����磬��nΪ4ʱ��������Ϊ��
1, 4, 5, 16, 17, 20, 21����
(4^0, 4^1, 4^0+4^1, 4^2, 4^0+4^2, 4^1+4^2, 4^0+4^1+4^2����)
����������еĵ�K��(10����)��
��������:

����ֻ��1�У�Ϊ2��������������֮����һ���ո������
n K
(n, K�ĺ�������������һ��, ��3<=n<=15, 10<=K<=1000)��

�������:

���Ϊ��������Ϊһ����������ע�������в��������У���������ᳬ��2.1*10^9��������ǰ��Ҫ�пո�������κη��š�

ʾ��1
����
����

3 100

���
����

981

*/
#include "../include/alloc2darray.h"
#include "../include/StringIntegration.h"
#include "../include/stringoperation.h"
#pragma comment(lib,"..//lib//alloc2darray.lib")


//��������ֵ��������ִ���ٶȱ�������Ϊ��������Ҫ���Ķࡣ

//���Կ������������ĺ��������Ƶ���Ĵ������١�

//������Ϊ������������Ŀ�г������������ٿ�����������������
void findpartition(int n, int m, std::string&temp, std::string&res)//�ҵ�m��n����
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
		findpartition(m, m, temp, res);
	else
	{
		//temp.push_back(n + 48);
		std::string s = std::to_string(n) + " ";
		temp.append(s);
		findpartition(n, m - n, temp, res);//��n��m�Ļ����������������Ҫ��¼n��������m-n��n����
		//temp.pop_back();
		temp.resize(temp.size() - s.size());
		findpartition(n - 1, m, temp, res);//��n����m�Ļ����������������Ҫ��¼n��������m��n-1����
	}
}

//��������Ļ��֣�Ҫ�󻮷���������ͬ
//item:��ʱ���飻res:������飻n:m��n���� m:Ҫ�������
void findcomb(std::string&item, int n, int m, std::string&res)
{
	if (n <= 0 || m <= 0)//�ݹ�ֹͣ������������n������mС���㣬˵���˴�ѡ���Ǵ���ģ�ֱ�ӻ���
		return;
	if (n == m)//������n��������ʱ��˵���˴�ѡ������ȷ�ģ���n��֮ǰ�Ĳ���ͨ�������뵽�������
	{
		res.append(item);
		res.push_back(n + 48);
		res.push_back(';');
	}
	item.push_back(n + 48);
	findcomb(item, n - 1, m - n, res);//���鵱n�Ǻ�Ϊm������������
	item.pop_back();//������� ����n
	findcomb(item, n - 1, m, res);//���鵱n����m������������
}
void findcombn(int n, int m, std::string&temp, std::string&res)//֧��m����9�İ汾
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