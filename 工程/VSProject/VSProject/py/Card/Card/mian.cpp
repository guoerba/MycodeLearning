/*

牛牛和羊羊正在玩一个纸牌游戏。这个游戏一共有n张纸牌, 第i张纸牌上写着数字ai。
牛牛和羊羊轮流抽牌, 牛牛先抽, 每次抽牌他们可以从纸牌堆中任意选择一张抽出, 直到纸牌被抽完。
他们的得分等于他们抽到的纸牌数字总和。
现在假设牛牛和羊羊都采用最优策略, 请你计算出游戏结束后牛牛得分减去羊羊得分等于多少。

输入描述:

输入包括两行。
第一行包括一个正整数n(1 <= n <= 105),表示纸牌的数量。
第二行包括n个正整数ai(1 <= ai <= 109),表示每张纸牌上的数字。


输出描述:

输出一个整数, 表示游戏结束后牛牛得分减去羊羊得分等于多少。


输入例子1:

3
2 7 4


输出例子1:

5

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <time.h>
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
	QSortStack() :left(0), middle(0), right(0),state(0) {};
	QSortStack(int l, int mid, int r,int s) :left(l), middle(mid), right(r), state(s) {};
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

long long reverse(long long a)
{
	return ~a + 1;
}


int main()
{
	int cardnum = 0;
	std::cin >> cardnum;
	//long long cardid = 0;
	Array<long long>cardid(cardnum);
	for (int i = 0; i < cardnum; i++)
	{
		std::cin >> cardid.a[i];
	}

	/*clock_t start, end;
	start = clock();

	srand(0);
	int cardnum = 0;
	std::cin >> cardnum;
	Array<long long>cardid(cardnum);
	for (int i = 0; i < cardnum; i++)
	{
		cardid.a[i] = rand() % RAND_MAX;
		std::cout << cardid.a[i] << " ";
	}*/
	/*long long a[] = { 3,2,6,8,1,9,10,4,7,5 };
	int cardnum = 10;
	Array<long long>cardid(cardnum);
	for (int i = 0; i < cardnum; i++)
	{
		cardid.a[i] = a[i];
		std::cout << cardid.a[i] << " ";
	}
	std::cout << "-------------------------------------------------------------------"  <<std::endl;
	std::cout << std::endl;*/
	//QuickSort(cardid.a, cardid.len);
	QuickSortNoRecursion(cardid.a, cardid.len);
	for (int i = 0; i < cardnum; i++)
	{
		std::cout << cardid.a[i] << " ";
	}
	/*std::cout << "-------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;*/
	long long sum = 0;
	bool flag = false;
	for (int i = cardid.len, j = 0; i > 0 ; i--,j++)
	{
		if (1 == j)
		{
			j = 0;
			if (flag)
				flag = false;
			else
				flag = true;
		}
		if (!flag)
		{
			//printf("%lld\n", reverse(i));
			sum += cardid.a[i - 1];
		}
		else
		{
			//printf("%lld\n", i);
			sum += reverse(cardid.a[i - 1]);
		}
	}
	std::cout << sum << std::endl;
	/*end = clock();
	std::cout << "程序运行时间： " << (double)(end - start)/100000 << std::endl;
	while (1);*/
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