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
	std::vector<int> DFS(int x,int y);//��Ҫ��x,y��1
	std::vector<int> BFS(int x, int y);
private:
	int **data;
	int size;
	int column;
	int CoordinatetoPointID(int x, int y);
	int PointIDtoCoordinateX(int id);
	int PointIDtoCoordinateY(int id);

};

struct node {//�ڽ��������ݽṹ
	int x;
	int y;
	node *next;
	node():x(0),y(0),next(0){}
	node(int x,int y,node *next):x(x),y(y),next(next){}
};

class AdjacentList {
public:
	AdjacentList();
	AdjacentList(int **array,int row,int col);
	~AdjacentList();
	void BFS(int sx, int sy);
	void DFS(int sx, int sy);
private:
	node ***data;
	int size;
	int drow, dcolumn;
};

class MapAlgorithm
{
public:
	MapAlgorithm();
	~MapAlgorithm();
};

