#include <iostream>
#include <stdio.h>
#include <vector>

typedef std::vector<std::vector<int>> VVInt;

template<class T>
T **CreateArray2D(int row, int col);
template<class T>
void DeleteArray2D(T **p);

template<class T>
struct Array {
	int len;
	T *a;
	Array() :len(0), a(NULL) {  };
	Array(int l) :len(l) { a = new T[len]; };
	~Array() { if (!a) { return; }delete[] a; a = NULL; };
	Array &operator = (const Array &b)
	{
		this->len = b.len;
		this->a = new T(b.len);
		for (int i = 0; i < b.len; i++)
		{
			this->a[i] = b.a[i];
		}
		return *this;
	}
	Array(const Array &b)
	{
		this->len = b.len;
		this->a = new T(b.len);
		for (int i = 0; i < b.len; i++)
		{
			this->a[i] = b.a[i];
		}
	}
	void append(const Array &b)
	{
		T *n = new T[this->len + b.len];
		for (int i = 0; i < this->len; i++)
		{
			n[i] = this->a[i];
		}
		for (int i = 0; i < b.len; i++)
		{
			n[i + this->len] = b.a[i];
		}
		delete[] this->a;
		a = n;
		this->len = this->len + b.len;
	}
};

void IntergerPartition(int n,int k)
{
	int **dp = CreateArray2D<int>(n + 1,k + 1);
	VVInt **s = CreateArray2D<VVInt>(n + 1,k + 1);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= k; j++)
		{
			if (i < j)
			{
				dp[i][j] = 0;				
			}
			else if (i == j)
			{
				dp[i][j] = 1;					
				std::vector<int>temp;
				temp.push_back(i);
				VVInt ss;
				ss.push_back(temp);
				s[i][j] = ss;
			}
			else
			{
				dp[i][j] = dp[i - 1][j - 1] + dp[i - j][j];
				if (dp[i - 1][j - 1])//至少一个为一
				{
					s[i][j] = s[i-1][j-1];									
					for (int k = 0,size = s[i][j].size();k < size;k++)
					{						
						s[i][j][k].push_back(1);
					}
					//s[i][j].push_back(ss);				
				}
				if (dp[i - j][j])
				{
					VVInt ss = s[i - j][j];
					for (int k = 0, size = ss.size(); k < size; k++)
					{
						for (int l = 0, lsize = ss[k].size(); l < size; l++)
						{
							ss[k][l] += 1;
						}
					}
					s[i][j].insert(s[i][j].end(),ss.begin(),ss.end());
				}
			}
		}
	}
	
	for (int i = 1; i <=n; i++)
	{
		for (int j = 1; j <=k; j++)
		{
			printf("最优解dp[%d][%d] = %d\n", i, j, dp[i][j]);		
			for (auto k : s[i][j])
			{
				for (auto l : k)
				{
					printf("%d,", l);
				}
				printf("\n");
			}
		}
	}
	DeleteArray2D(s);
	DeleteArray2D(dp);
}

int main()
{
	//int N, K;
	//std::cin >> N >> K;
	IntergerPartition(7, 3);
	
	while (1);
}

template<class T>
T **CreateArray2D(int row,int col)
{
	T **p = new T*[row];
	*p = new T[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = 0;
	return p;
}
template<typename std::vector<int> >



template<class T>
void DeleteArray2D(T **p)
{
	delete[] * p;
	delete[] p;
	p = NULL;
}