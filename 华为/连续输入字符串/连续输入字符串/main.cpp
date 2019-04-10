#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

typedef std::vector<std::string>	StringBuffer;
typedef std::string					String;

StringBuffer Split(const String &s, const char splitter);
String work(StringBuffer sbuf, int len);
void StringSort(const String &s);

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

int main()
{
	int N;
	String s,tempstr;
	while (std::cin >> tempstr)
		s.append(tempstr + ' ');

	StringBuffer sbuf = Split(s, ' ');
	int len = std::stoi(sbuf[0]);
	String result = work(sbuf, len);
	//std::cout << result << std::endl;
	StringSort(result);
	/*for (int i = 0, size = sbuf.size(),len = std::stoi(sbuf[0]); i < size; i += len + 1)
	{
		for (int j = 0; j < len; j++)
		{
			std::cout << sbuf[i + j + 1] << std::endl;
		}
	}*/
	while (1);

	return 0;
}

StringBuffer Split(const String &s, const char splitter)
{
	String temp;
	StringBuffer sbuf;
	for (int i = 0, size = s.size(); i < size; i++)
	{
		if (s[i] == splitter)
		{
			sbuf.push_back(temp);
			temp.clear();
		}
		else
		{
			temp.push_back(s[i]);
		}
	}
	sbuf.push_back(temp);
	return sbuf;
}
/*std::cout << s << std::endl;
	StringBuffer sbuf = Split(s, ' ');
	for (auto ss : sbuf)
		std::cout << ss << " ";*/

String work(StringBuffer sbuf,int len)
{
	String s;
	for (int i = 0; i < len; i++)
	{
		String temp = sbuf[i + 1];
		if (temp.size() > 8)
		{
			int size = temp.size() / 8;
			std::string::iterator it = temp.begin();
			for (int j = 0; j < size; j++)
			{
				it += 8 * j;
				s.append(it , it + 8);
				s.push_back(' ');
			}
			int rest = temp.size() % 8;
			it = temp.begin();
			s.append(it + 8*size, temp.end());
			for (int j = 0, size = 8 - rest; j < size; j++)
				s.push_back('0');
			s.push_back(' ');
		}
		else if (temp.size() < 8)
		{
			int rest = temp.size() % 8;
			s.append(temp.begin(), temp.end());
			for (int j = 0, size = 8 - rest; j < size; j++)
				s.push_back('0');
			s.push_back(' ');
		}
		else
		{
			s.append(temp);
			s.push_back(' ');
		}
	}
	s.resize(s.size() - 1);
	return s;
}

void StringSort(const String &s)
{
	StringBuffer sbuf = Split(s, ' ');
	QuickSortNoRecursion(sbuf.data(), sbuf.size());
	for (auto s : sbuf)
		std::cout << s << " ";
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