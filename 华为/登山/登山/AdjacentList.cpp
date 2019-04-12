#include "MapAlgorithm.h"





AdjacentList::AdjacentList()
{
}

AdjacentList::AdjacentList(int ** array, int row, int col)
	: drow(row),dcolumn(col)
{
	size = (row + 2) * (col + 2);
	int **p = CreateArray2D<int>(row + 2, col + 2,
		[&](int i, int j)->int {
		if (i == 0 || i == row + 1)
			return -1;
		if (j == 0 || j == col + 1)
			return -1;
		return array[i - 1][j - 1];
	});
	
	data = CreateArray2D<node*>(row, col,
		[&](int i, int j)->node* {
		node *head = NULL,*now = NULL;
		if (p[i][j] < p[i][j - 1])		//вС	
		{
			head = new node(i, j-1, 0);
			now = head;
			//data[CoordinatetoPointID(i, j - 1)][CoordinatetoPointID(i, j)] = 1;
		}
		if (p[i][j] < p[i][j + 1])//ср
		{
			if (head)
			{
				now->next = new node(i, j+1, 0);
				now = now->next;
			}
			else
			{
				head = new node(i, j+1, 0);
				now = head;
			}
			//data[CoordinatetoPointID(i, j + 1)][CoordinatetoPointID(i, j)] = 1;
		}
		if (p[i][j] < p[i - 1][j])//ио
		{
			if (head)
			{
				now->next = new node(i-1, j, 0);
				now = now->next;
			}
			else
			{
				head = new node(i-1, j, 0);
				now = head;
			}
		}
		if (p[i][j] < p[i + 1][j])//об
		{
			if (head)
			{
				now->next = new node(i+1,j, 0);
				now = now->next;
			}
			else
			{
				head = new node(i+1,j, 0);
				now = head;
			}
		}
		return head;
	});
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
	for (int i = 0; i < drow; i++)
	{
		for (int j = 0; j < dcolumn; j++)
		{
			if (data[i][j])
			{
				node *head = data[i][j];
				node *next = head;
				while (next)
				{
					node *now = next;
					next = next->next;
					delete now;
					now = NULL;
				}
			}
		}		
	}
	delete[] data;
	data = NULL;
}
