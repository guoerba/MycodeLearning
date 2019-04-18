#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include "MapAlgorithm.h"
//
int TestMap[][5] = { {0,1,0,0,0},{0,2,3,0,0},{0,0,4,0,0},{0,0,5,6,7},{0,0,0,9,8} };
int Test[][2] = { {1,0},{2,3} };

int main()
{
	int **p = CreateArray2D<int>(5,5,0);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			p[i][j] = TestMap[i][j];
	}
	AdjacentMatrix am(p,5, 5);
	AdjacentList al(p, 5, 5);
	/*for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			p[i][j] = TestMap[i][j];
	}
	AdjacentMatrix am(p,2, 2);*/

	while (1);
	delete(p);
	return 0;
}
