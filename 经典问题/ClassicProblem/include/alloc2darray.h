#pragma once
#include <Windows.h>
#include <vector>
#include <functional>
#include <typeinfo>
#include <iostream>

/*#ifdef   TEMPLATEDLL_EXPORT
#define  TEMPLATEDLL_API __declspec(dllexport)
#else
#define  TEMPLATEDLL_API __declspec(dllimport)
#endif*/
#define  TEMPLATEDLL_API __declspec(dllexport)

/*
template<class T> T **CreateArray2D(int row, int col, T initialize)
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
template TEMPLATEDLL_API int **CreateArray2D(int row, int col, int initialize);
template TEMPLATEDLL_API unsigned int **CreateArray2D(int row, int col, unsigned int initialize);
template TEMPLATEDLL_API long **CreateArray2D(int row, int col, long initialize);
template TEMPLATEDLL_API unsigned long **CreateArray2D(int row, int col, unsigned long initialize);

template<class T> std::vector<T> **CreateArray2D(int row, int col)
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
template TEMPLATEDLL_API std::vector<int> **CreateArray2D(int row, int col);
template TEMPLATEDLL_API std::vector<unsigned int> **CreateArray2D(int row, int col);
template TEMPLATEDLL_API std::vector<long> **CreateArray2D(int row, int col);
template TEMPLATEDLL_API std::vector<unsigned long> **CreateArray2D(int row, int col);

template<class T> T **CreateArray2D(int row, int col, std::function<T(int, int)> f)
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
template TEMPLATEDLL_API int **CreateArray2D(int row, int col, std::function<int(int, int)> f);
template TEMPLATEDLL_API unsigned int **CreateArray2D(int row, int col, std::function<unsigned int(int, int)> f);
template TEMPLATEDLL_API long **CreateArray2D(int row, int col, std::function<long(int, int)> f);
template TEMPLATEDLL_API unsigned long **CreateArray2D(int row, int col, std::function<unsigned long(int, int)> f);

template<class T> T **CreateArray2D(int row, int col, T **a, std::function<T(int, int, T**)> f)
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
template TEMPLATEDLL_API int **CreateArray2D(int row, int col, int **a, std::function<int(int, int, int**)> f);
template TEMPLATEDLL_API long **CreateArray2D(int row, int col, long **a, std::function<long(int, int, long**)> f);
template TEMPLATEDLL_API unsigned int **CreateArray2D(int row, int col, unsigned int **a, std::function<unsigned int(int, int, unsigned int**)> f);
template TEMPLATEDLL_API unsigned long **CreateArray2D(int row, int col, unsigned long **a, std::function<unsigned long(int, int, unsigned long**)> f);

template<class T> void DeleteArray2D(T **p)
{
	delete[] * p;
	delete[] p;
	p = NULL;
}
template TEMPLATEDLL_API void DeleteArray2D(int **p);
template TEMPLATEDLL_API void DeleteArray2D(long **p);
template TEMPLATEDLL_API void DeleteArray2D(unsigned int **p);
template TEMPLATEDLL_API void DeleteArray2D(unsigned long **p);*/

/*class TEMPLATEDLL_API TestClass
{
public:
	TestClass(int _a, int _b) { a = _a; b = _b; }
	int getSum();
private:
	int a;
	int b;
};*/

template <typename T>
class __declspec(dllexport) Array2d {
public:
	Array2d(int row, int col);
	Array2d(int row, int col, T init);
	Array2d(int row, int col, std::function<T(int, int)>f);
	Array2d(int row, int col, T **a, std::function<T(int, int, T**)>f);
	~Array2d();
	const T getItem(int row,int col);
	void setItem(int row, int col, T val);

	T &operator () (int , int ) const;
	T *operator [] (int);
	//Array2d &operator [] (int index);

	//T operator [] (int index);
private:
	T **CreateArray2D(int row, int col, T initialize);
	//std::vector<T> **CreateArray2D(int row, int col);
	T **CreateArray2D(int row, int col, std::function<T(int, int)> f);
	T **CreateArray2D(int row, int col, T **a, std::function<T(int, int, T**)> f);
	void DeleteArray2D(T **p);

	T **ptr;
	int m_row, m_col;
};