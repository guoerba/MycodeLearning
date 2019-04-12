#include "MapAlgorithm.h"

AdjacentMatrix::AdjacentMatrix()
{

}

AdjacentMatrix::AdjacentMatrix(int ** array, int row, int col, std::function<bool(int, int)> const & f)
{
	
}

AdjacentMatrix::AdjacentMatrix(int **array, int row, int col)
{
	column = col + 2;
	size = (row + 2) * (col + 2);
	data = CreateArray2D<int>(size, size,0);
	int **p = CreateArray2D<int>(row + 2, col + 2, 
		[&](int i, int j)->int{
		if (i == 0 || i == row + 1)
			return -1;
		if (j == 0 || j == col + 1)
			return -1;
		return array[i - 1][j - 1];
	});

	/*int **p = CreateArray2D<int>(row + 2, col + 2, -1);//辅助矩阵,简化运算
	for (int i = 0; i < row; i++)//只考虑相邻点之间形成最短路径
	{
		for (int j = 0; j < col; j++)
		{
			p[i + 1][j + 1] = array[i][j];
		}
	}*/
	for (int i = 0; i < row ; i++)
	{
		for (int j = 0; j < col; j++)
		{
			std::cout << array[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << "------------------------------------------------------" << std::endl;
	for (int i = 0; i < row + 2; i++)
	{
		for (int j = 0; j < col + 2; j++)
		{
			std::cout << p[i][j] << '\t';
		}
		std::cout << std::endl;
	}

	for (int i = 1; i <= row; i++)
	{
		for (int j = 1; j <= col; j++)
		{
			if (p[i][j] < p[i][j-1])		//左	
			{
				data[CoordinatetoPointID(i, j)][CoordinatetoPointID(i, j - 1)] = 1;
				//data[CoordinatetoPointID(i, j - 1)][CoordinatetoPointID(i, j)] = 1;
			}
			if (p[i][j] < p[i][j + 1])//右
			{
				data[CoordinatetoPointID(i, j)][CoordinatetoPointID(i, j + 1)] = 1;
				//data[CoordinatetoPointID(i, j + 1)][CoordinatetoPointID(i, j)] = 1;
			}
			if (p[i][j] < p[i - 1][j])//上
			{
				data[CoordinatetoPointID(i, j)][CoordinatetoPointID(i - 1, j)] = 1;
				//data[CoordinatetoPointID(i - 1, j)][CoordinatetoPointID(i, j)] = 1;
			}
			if (p[i][j] < p[i + 1][j])//下
			{
				data[CoordinatetoPointID(i, j)][CoordinatetoPointID(i + 1, j)] = 1;
				//data[CoordinatetoPointID(i + 1, j)][CoordinatetoPointID(i, j)] = 1;
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (data[i][j] == 1)
				printf("The data index is : [%d,%d];The actual index is [%d,%d] adjacent [%d,%d]\n", i, j, 
					PointIDtoCoordinateX(i), PointIDtoCoordinateY(i), PointIDtoCoordinateX(j), PointIDtoCoordinateY(j));
		}
	}
	DeleteArray2D(p);
}

AdjacentMatrix::~AdjacentMatrix()
{
	DeleteArray2D(data);
}

std::vector<int> AdjacentMatrix::DFS(int x, int y)
{
	
	return std::vector<int>();
}

std::vector<int> AdjacentMatrix::BFS(int x, int y)
{

	return std::vector<int>();
}

int AdjacentMatrix::CoordinatetoPointID(int x, int y)
{
	return x*column+y;
}

int AdjacentMatrix::PointIDtoCoordinateX(int id)
{
	return id/column - 1;
}

int AdjacentMatrix::PointIDtoCoordinateY(int id)
{
	return id%column - 1;
}
