#include <iostream>
#include <string>
#include <vector>

#define X			0
#define Y			1
#define B			2
#define G			3

typedef std::string					String;

template<class T>
T **CreateArray2D(int row, int col, T initialize);
template<class T>
void DeleteArray2D(T **p);

struct index {
	int i;
	int j;
	bool ischeck;
	index():i(0),j(0),ischeck(false){}
	index(int i,int j):i(i),j(j),ischeck(false){}
};

int OperationCount(std::vector< index > &a, int n, int gradient);
bool Find(std::vector< index > &a, int i, int j);



int main()
{
	int row, col;
	std::cin >> row >> col;
	char **pattern = CreateArray2D<char>(row, col, 0);
	for (int i = 0; i < row; i++)
	{
		String temps;
		std::cin >> temps;
		for (int j = 0; j < temps.size(); j++)
			pattern[i][j] = temps[j];
	}
	
	std::vector< index > LineY, LineB;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (pattern[i][j] == 'Y')
				LineY.push_back(index(i, j));
			else if (pattern[i][j] == 'B')
				LineB.push_back(index(i, j));
			else if (pattern[i][j] == 'G')
			{
				LineY.push_back(index(i, j));
				LineB.push_back(index(i, j));
			}
		}
	}

	int count = 0;
	count += OperationCount(LineY, row <= col ? row : col, -1);
	count += OperationCount(LineB, row <= col ? row : col, 1);
	std::cout << count << std::endl;
	/*for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			std::cout << pattern[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
	while (1);
	DeleteArray2D(pattern);

	return 0;
}

int OperationCount(std::vector< index > &a,int n,int gradient)//n为图案行和列之间的最小者
{
	int count = 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (!a[i].ischeck)
		{
			a[i].ischeck = true;
			for (int j = 1; j < n; j++)
			{
				if (gradient == -1)
				{
					if (!Find(a, a[i].i + j, a[i].j + j))//
						break;
				}
				else if(gradient == 1)
				{
					if (!Find(a, a[i].i + j, a[i].j - j))
						break;
				}
			}
			++count;
		}
	}
	return count;
}

bool Find(std::vector< index > &a, int i, int j)
{
	for (auto it = a.begin(); it != a.end(); ++it)
	{
		if ((*it).i == i && (*it).j == j)
		{
			(*it).ischeck = true;
			return true;
		}
			
	}
	return false;
}

template<class T>
T **CreateArray2D(int row, int col, T initialize = 0)
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
void DeleteArray2D(T **p)
{
	delete[] * p;
	delete[] p;
	p = NULL;
}