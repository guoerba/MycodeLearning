#include "MapAlgorithm.h"

AdjacentList::AdjacentList()
{
}

AdjacentList::AdjacentList(int ** array, int row
	
	
	
	
	
	
	
	
	
	
	\
	
	
	
	
	
	, int col)
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
	/*std::cout << "------------------------------------------------------" << std::endl;
	for (int i = 0; i < row + 2; i++)
	{
		for (int j = 0; j < col + 2; j++)
		{
			std::cout << p[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << "------------------------------------------------------" << std::endl;*/
	data = CreateArray2D<node*>(row, col,
		[&](int r, int c)->node* {
		node *head = NULL,*now = NULL;
		int i = r + 1, j = c + 1;
		if (p[i][j] < p[i][j - 1])		//左	
		{
			head = new node(r, c-1, 0);
			now = head;
			//data[CoordinatetoPointID(i, j - 1)][CoordinatetoPointID(i, j)] = 1;
		}
		if (p[i][j] < p[i][j + 1])//右
		{
			if (head)
			{
				now->next = new node(r, c+1, 0);
				now = now->next;
			}
			else
			{
				head = new node(r, c+1, 0);
				now = head;
			}
			//data[CoordinatetoPointID(i, j + 1)][CoordinatetoPointID(i, j)] = 1;
		}
		if (p[i][j] < p[i - 1][j])//上
		{
			if (head)
			{
				now->next = new node(r-1, c, 0);
				now = now->next;
			}
			else
			{
				head = new node(r-1, c, 0);
				now = head;
			}
		}
		if (p[i][j] < p[i + 1][j])//下
		{
			if (head)
			{
				now->next = new node(r+1,c, 0);
				now = now->next;
			}
			else
			{
				head = new node(r+1,c, 0);
				now = head;
			}
		}
		return head;
	});
	/*for (int i = 0; i < drow; i++)
	{
		for (int j = 0; j < dcolumn; j++)
		{
			if (data[i][j])
			{
				node *head = data[i][j];
				node *next = head;
				printf("点(%d,%d)的邻接点是: ",i,j);
				while (next)
				{
					printf("(%d,%d) ", next->x, next->y);
					next = next->next;					
				}
				printf("\n");
			}
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
