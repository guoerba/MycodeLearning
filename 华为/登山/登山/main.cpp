#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

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
void DeleteArray2D(T **p)
{
	delete[] * p;
	delete[] p;
	p = NULL;
}

struct Coordinate {
	int X;
	int Y;
	Coordinate(int x,int y):X(x),Y(y){}
	Coordinate():X(0),Y(0){}
};

int main()
{
	int N, M;
	std::cin >> N >> M;
	int **a = CreateArray2D<int>(N, M,0);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			std::cin >> a[i][j];
		}
	}
	int X,Y,Z,W;
	std::cin >> X >> Y >> Z >> W;

	/*for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			std::cout << a[i][j] << " ";
		}
		std::cout << std::endl;
	}*/


	while (1);
	delete(a);
	return 0;
}

void DFS(int **a, Coordinate s, Coordinate e)
{
	
}