/*小Q有X首长度为A的不同的歌和Y首长度为B的不同的歌，现在小Q想用这些歌组成一个总长度正好为K的歌单，
每首歌最多只能在歌单中出现一次，在不考虑歌单内歌曲的先后顺序的情况下，请问有多少种组成歌单的方法。 

输入描述:
每个输入包含一个测试用例。
每个测试用例的第一行包含一个整数，表示歌单的总长度K(1<=K<=1000)。
接下来的一行包含四个正整数，分别表示歌的第一种长度A(A<=10)和数量X(X<=100)以及歌的第二种长度B(B<=10)和数量Y(Y<=100)。
保证A不等于B。

输出描述:
输出一个整数,表示组成歌单的方法取模。因为答案可能会很大,输出对1000000007取模的结果。
输入例子1:
5
2 3 3 3

输出例子1:
9*/

#include <iostream>
#include <vector>
#include <stdio.h>
#include <functional>

const int MOD = ((int)1e9 + 7);

typedef std::vector<std::string>	StringBuffer;
typedef std::string					String;


template<class T>
T **CreateArray2D(int row, int col, T initialize);
template<class T>
std::vector<T> **CreateArray2D(int row, int col);
template<class T>
T **CreateArray2D(int row, int col, std::function<T(int, int)> f);
template<class T>
T **CreateArray2D(int row, int col, T **a, std::function<T(int, int, T**)> f);
template<class T>
void DeleteArray2D(T **p);
template<class T>
T Combination_YangHuiTriangle(T **c, int m, int n);

struct Song {
	int numx;
	int numy;
	Song() :numx(0), numy(0) {}
	Song(int nx, int ny) :numx(nx), numy(ny) {}
};

int Permutation(int m, int n);//A(m,n)
int Factorial(int n);//n!
int Combination(int m, int n);//C(m.n)

std::vector<Song> FindCombination(int x, int y, int a, int b, int k)
{
	std::vector<Song>songnum;
	for (int i = 1; i <= x; i++)
	{
		for (int j = 1; j <= y; j++)
		{
			//printf("%d * %d + %d * %d = %d\n", a, i, b, j, a*i + b * j);
			if (a * i + b * j == k)
				songnum.push_back(Song(i, j));
		}
	}
	return songnum;
}



int main()
{
	int K, A, X, B, Y;
	std::cin >> K;
	std::cin >> A >> X >> B >> Y;//长度为A的歌曲有X首；长度为B的歌曲有Y首

	std::vector<Song> songs = FindCombination(X, Y, A, B, K);
	/*int sum = 0;
	for (int i = 0, size = songs.size(); i < size; i++)
	{
		//printf("song[%d] = Song(%d,%d)\n", i, songs[i].numx, songs[i].numy);
		sum += Combination(X, songs[i].numx)*Combination(Y, songs[i].numy);
	}
	printf("sum: %d\n", sum);*/

	auto init = [](int m, int n)->long long {
		if (m < n)
			return 0;
		if (n == 0)
			return 1;
		else
			return 0;
	};
	int len = X > Y ? X + 1 : Y + 1;
	long long **c = CreateArray2D<long long>(len,len,init);
	Combination_YangHuiTriangle(c, len - 1, len - 1);
	long long sum = 0;
	for (int i = 0, size = songs.size(); i < size; i++)
	{
		long long combx = c[X][songs[i].numx],comby = c[Y][songs[i].numy];
		printf("song[%d]=Song(%d,%d) combx:%lld comby:%lld sum[%d]:%lld\n", i, songs[i].numx, songs[i].numy,combx,comby,i,combx*comby);
		sum += combx * comby;
	}
	DeleteArray2D(c);
	printf("sum: %lld\n", sum % MOD);
	
	//std::cout << Permutation(5, 2) << std::endl;
	//std::cout << Factorial(3) << std::endl;
	//std::cout << Combination(5, 2) << std::endl;
	while (1);
}

int Permutation(int m,int n)//A(m,n)
{
	int end = m - n + 1;
	int p = 1;
	for (int i = m; i >= end; i--)
		p *= i;
	return p;
}

int Factorial(int n)//n!
{
	if (n == 0)
		return 1;
	int f = 1;
	for (int i = 1; i <= n; i++)
		f *= i;
	return f;
}
int Combination(int m, int n)//C(m.n)
{
	return Permutation(m, n) / Factorial(n);
}

template<class T>
T Combination_YangHuiTriangle(T **c,int m, int n)
{
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
			c[i][j] %= MOD;
		}
	}
	return c[m][n];
}//测试代码
/*auto init = [](int m, int n)->int {
		if (m < n)
			return 0;
		if (n == 0)
			return 1;
		else
			return 0;
	};

	int **c = CreateArray2D<int>(10+1, 10+1, init);
	Combination_YangHuiTriangle(c, 10, 10);
	for (int i = 0;i<11;i++)
	{
		for (int j = 0; j < 11; j++)
		{
			//printf("C(%d,%d)=%d|", i, j, c[i][j]);
			printf("%d ", c[i][j]);
		}
		printf("\n");
	}*/

template<class T>
T **CreateArray2D(int row, int col, T initialize)
{
	T **p = new T*[row];
	*p = new T[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = initialize;
	return p;
}

template<class T>
std::vector<T> **CreateArray2D(int row, int col)
{
	std::vector<T> **p = new std::vector<T>*[row];
	*p = new std::vector<T>[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = std::vector<T>();
	return p;
}

template<class T>
T **CreateArray2D(int row, int col, std::function<T(int, int)> f)
{
	T **p = new T*[row];
	*p = new T[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = f(i, j);
	return p;
}

template<class T>
T **CreateArray2D(int row, int col, T **a, std::function<T(int, int, T**)> f)
{
	T **p = new T*[row];
	*p = new T[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = f(i, j, a);
	return p;
}


template<class T>
void DeleteArray2D(T **p)
{
	delete[] * p;
	delete[] p;
	p = NULL;
}