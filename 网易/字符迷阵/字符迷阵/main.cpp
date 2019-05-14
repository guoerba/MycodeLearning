#include <iostream>
#include <string>
#include <vector>
#include <functional>

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

struct Data {
	int row;
	int column;
	int matchcount;
	char **p;
	std::string word;
	Data():row(0),column(0),matchcount(0),p(0),word(std::string()){}
	Data(int row,int col,char **p,std::string w):row(row),column(col), matchcount(0),p(p),word(w){}
	~Data() { DeleteArray2D(p); word.clear(); }
};

int MatchRight(const Data &d, int si, int sj, int column);
int MatchDown(const Data &d, int si, int sj, int row);
int MatchDownRight(const Data &d, int si, int sj, int row, int column);

int main()
{
	int group;
	std::cin >> group;
	std::vector<Data>input(group);
	
	for (int i = 0; i < group; i++)
	{
		int row, col;
		std::cin >> row >> col;
		input[i].row = row;
		input[i].column = col;
		input[i].p = CreateArray2D<char>(row, col,0);
		for (int j = 0; j < row; j++)
		{
			std::string temps;
			std::cin >> temps;
			for (int k = 0; k < col; k++)
				input[i].p[j][k] = temps[k];
		}
		std::cin >> input[i].word;
	}

	for (int n = 0; n < group; n++)
	{
		for (int i = 0; i < input[n].row; i++)
		{
			for (int j = 0; j < input[n].column; j++)
			{
				if (input[n].p[i][j] == input[n].word[0])
				{
					input[n].matchcount += MatchRight(input[n], i, j,input[n].column);
					input[n].matchcount += MatchDown(input[n], i, j,input[n].row);
					input[n].matchcount += MatchDownRight(input[n], i, j,input[n].row,input[n].column);
				}
			}
		}
	}

	for (auto it = input.cbegin(); it != input.end(); ++it)
		std::cout << (*it).matchcount << std::endl;
	while (1);
	input.clear();
}

int MatchRight(const Data &d,int si,int sj,int column)
{
	if (d.word.size() > column - sj)
		return 0;
	for (int col = 1; col < d.word.size(); col++)
	{
		if (d.p[si][sj + col] != d.word[col])
			return 0;
	}
	return 1;
}

int MatchDown(const Data &d, int si, int sj,int row)
{
	if (d.word.size() > row - si)
		return 0;
	for (int row = 1; row < d.word.size(); row++)
	{
		if (d.p[si + row][sj] != d.word[row])
			return 0;
	}
	return 1;
}
int MatchDownRight(const Data &d, int si, int sj,int row,int column)
{
	if (d.word.size() > row - si || d.word.size() > column - sj)
		return 0;
	for (int n = 1; n < d.word.size(); n++)
	{
		if (d.p[si + n][sj + n] != d.word[n])
			return 0;
	}
	return 1;
}

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