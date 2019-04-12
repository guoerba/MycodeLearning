#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <stdio.h>
#include "MemAlloc.h"


#define Coordinate_PointID(x,y,col)			(x*col+y)
#define PointID_Coordinate_X(id,col)		(id/col)
#define PointID_Coordinate_Y(id,col)		(id%col)

class AdjacentMatrix {
public:
	AdjacentMatrix();
	AdjacentMatrix(int **array,int row,int col);
	AdjacentMatrix(int **array,int row,int col,std::function<bool(int,int)> const &f);
	~AdjacentMatrix();
	std::vector<int> DFS(int x,int y);
	std::vector<int> BFS(int x, int y);
private:
	int **data;
	int size;
	int column;
	int CoordinatetoPointID(int x, int y);
	int PointIDtoCoordinateX(int id);
	int PointIDtoCoordinateY(int id);

};

class AdjacentList {

};

class MapAlgorithm
{
public:
	MapAlgorithm();
	~MapAlgorithm();
};

