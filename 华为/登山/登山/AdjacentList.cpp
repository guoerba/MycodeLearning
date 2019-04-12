#include "MapAlgorithm.h"





AdjacentList::AdjacentList()
{
}

AdjacentList::AdjacentList(int ** array, int row, int col)
{
	size = row * col;
	data = CreateArray2D<node*>(row, col, 0);
	/*for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if(array[])
		}
	}*/
}

AdjacentList::~AdjacentList()
{
	delete[] data;
}
