/*

ţţ������������һ��ֽ����Ϸ�������Ϸһ����n��ֽ��, ��i��ֽ����д������ai��
ţţ��������������, ţţ�ȳ�, ÿ�γ������ǿ��Դ�ֽ�ƶ�������ѡ��һ�ų��, ֱ��ֽ�Ʊ����ꡣ
���ǵĵ÷ֵ������ǳ鵽��ֽ�������ܺ͡�
���ڼ���ţţ�����򶼲������Ų���, ����������Ϸ������ţţ�÷ּ�ȥ����÷ֵ��ڶ��١�

��������:

����������С�
��һ�а���һ��������n(1 <= n <= 105),��ʾֽ�Ƶ�������
�ڶ��а���n��������ai(1 <= ai <= 109),��ʾÿ��ֽ���ϵ����֡�


�������:

���һ������, ��ʾ��Ϸ������ţţ�÷ּ�ȥ����÷ֵ��ڶ��١�


��������1:

3
2 7 4


�������1:

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
	int state;//��ջ״̬
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
	std::cout << "��������ʱ�䣺 " << (double)(end - start)/100000 << std::endl;
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
	//s.push(QSortStack(left,mid,right,0));//root state:0û��������1����������������2��������������
	while (!s.empty())
	{
		if (cur.left < cur.right)
		{
			switch (cur.state)
			{
			case 0:
				mid = Partition(A, cur.left, cur.right);
				s.push(QSortStack(mid + 1, 0, cur.right, 1));//��¼������
				cur.right = mid - 1;
				break;
			case 1:
				s.push(QSortStack(cur.left, cur.middle, cur.right, 2));//����������
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
			s.pop();//ɾ����������¼
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