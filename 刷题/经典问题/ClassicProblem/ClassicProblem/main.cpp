#include "../include/alloc2darray.h"
#include "../include/StringIntegration.h"
#pragma comment(lib,"..//lib//alloc2darray.lib")

void bag01_solution(Array2d<int>&p,int V,int n,const std::vector<int>&w)
{
	std::vector<int>s(n);
	for (int i = 0; i < n; i++)
		s[i] = 0;
	for (int i = n, j = V; i > 0; i--)//�ҵ����Žṹ
	{
		if (p[i][j] != p[i - 1][j])
		{
			s[i - 1] = 1;
			j -= w[i - 1];
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (s[i])
			std::cout << i << " ";
	}
	std::cout << std::endl;
}

void * bag01(int V,int n,const std::vector<int>&w,const std::vector<int>&v)
{
	Array2d<int>*a = new Array2d<int>(n + 1, V + 1, 0);
	Array2d<int>&p = *a;//p[i][j]��ʾ�ڱ�������Ϊjʱ�����ǵ���i����Ʒʱ������ֵ
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= V; j++)
		{
			//int k = j - 1;
			int k = i - 1;
			if (w[k] > j)
			{
				p[i][j] = p[i - 1][j];//��i����Ʒ���������ڱ�������ʱ����ѡ��
			}
			else
			{
				p[i][j] = max(p[i - 1][j - w[k]] + v[k], p[i - 1][j]);//��i����Ʒ������С�ڵ���	����������ʱ��ѡ���ֵ����ѡ��
			}
		}
	}
	std::cout << p[n][V] << std::endl;

	//while (1);
	return a;
}

int main(void)
{
	int V, n;
	std::cin >> V >> n;
	std::vector<int> w(n), v(n);

	for (int i = 0; i < n; i++)
		std::cin >> w[i] >> v[i];
	Array2d<int>*a = (Array2d<int>*)bag01(V, n, w, v);
	bag01_solution(*a, V, n, w);
	while (1);
	delete a;
	/*for (int i = 0; i < n+1; i++)
	{
		for (int j = 0; j < V + 1; j++)
		{
			std::cout << p[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
	

}