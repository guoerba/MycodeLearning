#pragma once
#include <algorithm>
#include <stack>

template<class T>
void Swap(T &a, T &b);
template<class T>
void QuickSort(T *A, int len);
template<class T>
void QuickSort(T *A, int s, int e);
template<class T>
void QuickSortNoRecursion(T *A, int len);
template<class T>
int Partition(T *A, int s, int e);

struct QSortStack {
	int left;
	int middle;
	int right;
	int state;//堆栈状态
	QSortStack() :left(0), middle(0), right(0), state(0) {};
	QSortStack(int l, int mid, int r, int s) :left(l), middle(mid), right(r), state(s) {};
	QSortStack(const QSortStack &b)
	{
		this->left = b.left;
		this->middle = b.middle;
		this->right = b.right;
		this->state = b.state;
	}
	QSortStack & operator = (const QSortStack &b)
	{
		this->left = b.left;
		this->middle = b.middle;
		this->right = b.right;
		this->state = b.state;
		return *this;
	}
};


template<class T>
void Swap(T &a, T &b)
{
	if (a == b)
		return;
	T temp = a;
	a = b;
	b = temp;
}


template<class T>
void QuickSort(T *A, int len)
{
	QuickSort(A, 0, len - 1);
}

template<class T>
void QuickSort(T *A, int s, int e)
{
	if (s < e)
	{
		int r = Partition(A, s, e);
		QuickSort(A, s, r - 1);
		QuickSort(A, r, e);
	}
}

template<class T>
void QuickSortNoRecursion(T *A, int len)
{
	if (len <= 1)
		return;
	std::stack<QSortStack> s;
	s.push(QSortStack());
	QSortStack cur(0, 0, len - 1, 0);
	int mid = 0;
	//s.push(QSortStack(0, 0, 0, 2));
	//s.push(QSortStack(left,mid,right,0));//root state:0没遍历过；1：遍历了左子树；2：遍历了右子树
	while (!s.empty())
	{
		if (cur.left < cur.right)
		{
			switch (cur.state)
			{
			case 0:
				mid = Partition(A, cur.left, cur.right);
				s.push(QSortStack(mid + 1, 0, cur.right, 1));//记录右子树
				cur.right = mid - 1;
				break;
			case 1:
				s.push(QSortStack(cur.left, cur.middle, cur.right, 2));//更新右子树
				cur.state = 0;
				break;
			case 2:
				if (s.empty())
					break;
				cur = s.top();
				s.pop();
			}
		}
		else
		{
			if (s.empty())
				break;
			cur = s.top();
			s.pop();//删除右子树记录
		}
	}

}

template<class T>
int Partition(T *A, int s, int e)
{
	//Swap(A[r], A[e]);
	int i = s, j = s;
	while (i < e)
	{
		if (A[i] < A[e])
		{
			Swap(A[i++], A[j++]);
		}
		else
		{
			i++;
		}
	}
	Swap(A[j], A[e]);
	return j;
}


class Solution
{
public:
	Solution();
	~Solution();
	int singleNumber(int A[], int n) {
		QuickSortNoRecursion(A, n);
			for (int i = 0; i < n - 1; i += 2)
			{
				if (A[i] != A[i + 1])
					return A[i];
			}
		return A[n - 1];
	}
};

