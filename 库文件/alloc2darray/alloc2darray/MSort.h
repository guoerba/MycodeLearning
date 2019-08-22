#pragma once
#include <functional>
#include <stack>
#include <iostream>


typedef unsigned int uint;

template<typename T>class Heap;
template<typename T>class MSort;


template <typename T>
class __declspec(dllexport) MSort
{
	typedef std::function<bool(T, T)> Compare;
public:
	typedef enum SortFunction {
		choose,
		bubble,
		insert,
		shell,
		quick,
		heap,
		merges,
		count,
		radix,
		bucket,
	};
	MSort();
	MSort(T *array, uint n, SortFunction sf,Compare f);
	~MSort();
	void free(T *array);
	void free();
	uint data(T *array);
	T *data();
private:
	void ChooseSort();
	void BubbleSort();
	void InsertSort();
	void ShellSort();
	void QuickSort();
	void HeapSort();
	void MergeSort();
	void CountSort();

	void swap(T &a,T &b);
	uint partition(uint mid,uint l,uint r);
	void merge(uint l,uint m,uint r);
	void merge(T *b, T *c, uint l, uint m, uint r);

	T *a;
	uint len;

	Compare comp;
};

template<typename T>
class __declspec(dllexport) Heap
{
	typedef std::function<bool(T, T)> Compare;
public:
	Heap();
	Heap(T*array, uint len, Compare func);
	~Heap();
	const T *heap();
private:
	void CreateHeap(T *array, uint len, Compare func);
	void KeepHeap(uint i);//维护一个元素及其两个子元素（有的话）的堆性质
	void Sort();

	uint parent(uint i);
	uint leftchild(uint i);
	uint rightchild(uint i);

	void swap(T &a, T &b);

	Compare comp;
	T *a;
	uint heapsize;
};


