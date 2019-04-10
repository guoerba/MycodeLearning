/*小Q今天在上厕所时想到了这个问题：有n个数，两两组成二元组，相差最小的有多少对呢？相差最大呢？

输入描述:

 输入包含多组测试数据。
 对于每组测试数据：
 N - 本组测试数据有n个数
 a1,a2...an - 需要计算的数据
 保证:
 1<=N<=100000,0<=ai<=INT_MAX.



输出描述:

对于每组数据，输出两个数，第一个数表示差最小的对数，第二个数表示差最大的对数。*/

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <stdlib.h>

typedef unsigned int					uint;
typedef std::vector<uint>				VectorUint;

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

template <class T>
int CountNumber(T *a, int len, T num);
int MaxDifferentNumber(uint *a, int len);
int MinDifferentNumber(uint *a, int &len);
int MinDifferentNumber(VectorUint a);

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
};

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

int main()
{
	//srand(0);

	uint N;
	
	std::vector< std::vector<uint> >va;
	while (std::cin >> N)
	{
		std::vector<uint>a(N);
		for (uint i = 0; i < N; i++)
		{
			std::cin >> a[i];
		}
		va.push_back(a);
	}
	
	/*std::cin >> N;
	Array<uint>a(N);
	for (uint i = 0; i < N; i++)
	{
		a.a[i] = rand();
	}*/
	for (int i = 0, size = va.size(); i < size; i++)
	{
		int maxdiffnum = MaxDifferentNumber(va[i].data(), va[i].size());
		int mindiffnum = MinDifferentNumber(va[i]);
		std::cout << mindiffnum << " " << maxdiffnum << std::endl;
	}
	
	//std::cout << "maxdiff: " << maxdiff << std::endl;
	//std::cout << "mindiff: " << mindiff << std::endl;
	while (1);
}

int MaxDifferentNumber(uint *a, int len)
{
	QuickSortNoRecursion(a, len);
	uint maxdiff = a[len - 1] - a[0];
	int minnum = CountNumber(a, len, a[0]);
	int maxnum = CountNumber(a, len, a[len - 1]);
	return maxnum * minnum;
}

int MinDifferentNumber(uint *a, int &len)
{
	//QuickSortNoRecursion(a, len);
	bool hasequal = false;
	int min = 0, n = 1;
	for (int i = 1; i < len; i++)
	{
		if (a[i - 1] == a[i])
		{
			hasequal = true;
			n++;
		}
		else
		{
			min += n * (n - 1) / 2;
			n = 1;
		}
	}
	if (hasequal)
	{
		min += n * (n - 1) / 2;
		return min;
	}


	len--;
	for (uint i = 0; i < len; i++)
	{
		a[i] = a[i + 1] - a[i];
	}
	QuickSortNoRecursion(a, len);
	uint mindiff = a[0];
	return CountNumber(a, len, a[0]);
}

int MinDifferentNumber(VectorUint a)
{
	//QuickSortNoRecursion(a, len);
	bool hasequal = false;
	int min = 0, n = 1;
	for (int i = 1,size = a.size(); i < size; i++)
	{
		if (a[i - 1] == a[i])
		{
			hasequal = true;
			n++;
		}
		else
		{
			min += n * (n - 1) / 2;
			n = 1;
		}
	}
	if (hasequal)
	{
		min += n * (n - 1) / 2;
		return min;
	}


	a.resize(a.size() - 1);
	for (uint i = 0,size = a.size(); i < size; i++)
	{
		a[i] = a[i + 1] - a[i];
	}
	QuickSortNoRecursion(a.data(), a.size());
	uint mindiff = a[0];
	return CountNumber(a.data(), a.size(), a[0]);
}

template <class T>
int CountNumber(T *a, int len, T num)
{
	int count = 0;
	for (int i = 0; i < len; i++)
	{
		if (a[i] == num)
			count++;
	}
	return count;
}

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
/*uint N;
	std::cin >> N;
	Array<uint>a(N);
	for (uint i = 0; i < N; i++)
	{
		std::cin >> a.a[i];
	}
	QuickSortNoRecursion(a.a, a.len);
	uint maxdiff = a.a[a.len - 1] - a.a[0];
	int minnum = 0;
	for (int i = 0; i < a.len; i++)
	{
		if (a.a[i] != a.a[0])
		{
			minnum = i;
			break;
		}
	}
	int maxnum = 0;
	for (int i = a.len - 1; i > 0; i--)
	{
		if (a.a[i - 1] != a.a[a.len - 1])
		{
			maxnum = a.len - i;
			break;
		}
	}
	std::cout << "maxnum: " << maxnum << " minnum: " << minnum << std::endl;
	int maxdiffnum = maxnum * minnum;
	for (uint i = 0; i < a.len; i++)
		std::cout << a.a[i] << " ";
	std::cout << std::endl;


N--;
for (uint i = 0; i < N; i++)
{
	a.a[i] = a.a[i + 1] - a.a[i];
}
a.len = N;
QuickSortNoRecursion(a.a, a.len);
uint mindiff = a.a[0];
int mindiffnum = 0;
for (int i = 0; i < a.len; i++)
{
	if (a.a[i] != a.a[0])
	{
		mindiffnum = i;
		break;
	}
}
std::cout << mindiffnum << " " << maxdiffnum << std::endl;
std::cout << "maxdiff: " << maxdiff << std::endl;
std::cout << "mindiff: " << mindiff << std::endl;
while (1); */