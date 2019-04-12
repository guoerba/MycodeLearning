#pragma once
#include <vector>
#include <string>
#include <functional>

typedef std::vector<std::string>	StringBuffer;
typedef std::string					String;

/*template<class T>
class Array {
	Array() :a(0),b(0),c(0), data(NULL),dtype(dimension_0) {  };
	Array(int len) :a(len),b(0),c(0),dtype(dimension_1)
	{ 
		data = new T[len]; 		
	}
	Array(int row,int col) :a(row), b(col), c(0), dtype(dimension_2)
	{
		T **p = new T*[row];
		*p = new T[row*col];
		for (int i = 0; i < row; i++)
			p[i] = *p + i * col;
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				p[i][j] = initialize;
	}
	~Array() 
	{
		if (!data) 
			return;
		delete[] data; 
		data = NULL; 
	}
	Array &operator = (const Array &b)
	{
		this->len = b.len;
		this->data = new T(b.len);
		for (int i = 0; i < b.len; i++)
		{
			this->data[i] = b.data[i];
		}
		return *this;
	}
	Array(const Array &b)
	{
		this->len = b.len;
		this->data = new T(b.len);
		for (int i = 0; i < b.len; i++)
		{
			this->data[i] = b.data[i];
		}
	}
	void append(const Array &b)
	{
		T *n = new T[this->len + b.len];
		for (int i = 0; i < this->len; i++)
		{
			n[i] = this->data[i];
		}
		for (int i = 0; i < b.len; i++)
		{
			n[i + this->len] = b.data[i];
		}
		delete[] this->data;
		data = n;
		this->len = this->len + b.len;
	}
private:
	int a,b,c;
	T **data;
	enum DType {
		dimension_0,dimension_1, dimension_2, dimension_3
	}dtype;
};*/

template<class T>
struct Coordinate {
	T X;
	T Y;
	Coordinate(T x, T y) :X(x), Y(y) {}
	Coordinate() :X(0), Y(0) {}
};

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
T **CreateArray2D(int row, int col,T **a, std::function<T(int,int,T**)> f)
{
	T **p = new T*[row];
	*p = new T[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = f(i,j,a);
	return p;
}


template<class T>
void DeleteArray2D(T **p)
{
	delete[] * p;
	delete[] p;
	p = NULL;
}

template<class T>
struct Array {
	int len;
	T *a;
	Array() :len(0), a(NULL) {  };
	Array(int l) :len(l) { a = new T[len]; };
	~Array() { if (!a) { return; }delete[] a; a = NULL; };
	Array &operator = (const Array &b)
	{
		this->len = b.len;
		this->a = new T(b.len);
		for (int i = 0; i < b.len; i++)
		{
			this->a[i] = b.a[i];
		}
		return *this;
	}
	Array(const Array &b)
	{
		this->len = b.len;
		this->a = new T(b.len);
		for (int i = 0; i < b.len; i++)
		{
			this->a[i] = b.a[i];
		}
	}
	void append(const Array &b)
	{
		T *n = new T[this->len + b.len];
		for (int i = 0; i < this->len; i++)
		{
			n[i] = this->a[i];
		}
		for (int i = 0; i < b.len; i++)
		{
			n[i + this->len] = b.a[i];
		}
		delete[] this->a;
		a = n;
		this->len = this->len + b.len;
	}
};



int **ProduceMap();
