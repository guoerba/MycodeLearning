#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <stack>
#include <vector>

#define MAXSTRING	256

struct Point {
	int x;
	int y;
	bool ismax;
	Point() {};
	Point(int x, int y,bool ismax = false) :x(x), y(y),ismax(ismax) {};
	bool operator<(const Point &b)
	{
		if (this->x < b.x)
			return true;
		else
			return false;
	}
	bool operator>(const Point &b)
	{
		if (this->x > b.x)
			return true;
		else
			return false;
	}
	bool operator==(const Point &b)
	{
		if (this->x == b.x)
			return true;
		else
			return false;
	}
	Point &operator=(const Point &b)
	{
		this->x = b.x;
		this->y = b.y;
		return *this;
	}
};
//带卫星数据的快速排序
/*Point a[] = { Point(3,5),Point(4,6),Point(1,7),Point(5,8),Point(9,3),Point(10,4),Point(8,4) };
	for (int i = 0; i < 7; i++)
	{
		std::cout << "(x,y): (" << a[i].x << "," << a[i].y << ")" << std::endl;
	}
	std::cout << "-------------------------------" << std::endl;
	QuickSort(a, 7);
	for (int i = 0; i < 7; i++)
	{
		std::cout << "(x,y): (" << a[i].x << "," << a[i].y << ")" << std::endl;
	}*/

typedef unsigned int				uint;
typedef std::vector<int>			VectorInt;
typedef std::vector<std::string>	StringBuffer;
typedef std::string					String;
template<class T>
struct vector_typedef {
	typedef std::vector<T> Vector;
};
typedef std::vector<std::stack<int> >	StackBufferInt;
typedef std::stack<int>					StackInt;
template<class T>
void Swap(T &a, T &b);
/*template<>
void Swap(Point &a, Point &b);*/
template<class T>
void QuickSort(T *A, int len);
template<class T>
void QuickSort(T *A, int s, int e);
template<class T>
int Partition(T *A, int s, int e);
/*template<>
int Partition(Point *A, int s, int e);*/
std::fstream openfile(const String &filename, String &s);
StringBuffer split(const char *str, int len, char splitter);
String input();

Point *CreatePointSet(String &s)
{
	StringBuffer points = split(s.c_str(), s.size(), '\n');
	//std::cout << "num: " << std::stoi(points[0]) << std::endl;
	int num = std::stoi(points[0]);
	Point *p = new Point[num];
	for (int i = 0; i < num; i++)
	{
		StringBuffer point = split(points[i + 1].c_str(), points[i + 1].size(), ' ');		
		p[i] = Point(std::stoi(point[0]), std::stoi(point[1]),false);
		//std::cout << "(x,y): (" << point[0] << "," << point[1] << ")" << std::endl;
		//std::cout << "(x,y): (" << p[i].x << "," << p[i].y << ") ismax: " << p[i].ismax << std::endl;
	
	}
	return p;
}

void DeletePointSet(Point *p)
{
	if (p == NULL)
		return;
	delete[] p;
	p = NULL;
}

//将点按x排好序，则对点P来说，所有的Q属于点集，若对所有的Q.x > P.x的点来说，其Q.y < P.y，则Q是最大点
int Judge(Point *p,int len)
{
	QuickSort(p, len);
	int maxY = -1;
	for (int i = len; i > 0; i--)//按x的降序方向查找
	{
		bool flag = false;
		if (maxY <= p[i - 1].y)//维护一个最大的y
		{
			p[i - 1].ismax = true;
			maxY = p[i - 1].y;
		}
		if (flag)
		{
			p[i-1].ismax = flag;
		}
	}
	//p[len - 1].ismax = true;

	for (int i = 0; i < len; i++)
	{
		if (p[i].ismax == true)
		{
			//std::cout << "(x,y): (" << p[i].x << "," << p[i].y << ")" << std::endl;
			std::cout << p[i].x << " " << p[i].y << std::endl;
		}
	}
	return 0;
}

/*void output(Point *p, int len, int maxnum)
{
	Point *mp = new Point[maxnum];
	for (int i = 0,j = 0; i < len; i++)
	{
		if (p[i].ismax)
			mp[j++] = p[i];
	}
	QuickSort(mp, maxnum);
	for (int i = 0; i < maxnum; i++)
	{
		std::cout << "(x,y): (" << mp[i].x << "," << mp[i].y << ")" << std::endl;
	}
	delete[] mp;
}*/

int main()
{
	//String s = input();
	String s;
	std::fstream f = openfile("./data.txt", s);
	Point *p = CreatePointSet(s);
	StringBuffer points = split(s.c_str(), s.size(), '\n');
	//std::cout << "num: " << std::stoi(points[0]) << std::endl;
	int num = std::stoi(points[0]);
	int maxnum = Judge(p, num);
	//output(p,num,maxnum);
	DeletePointSet(p);
	while (1);
	//f.close();
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

//快速排序测试代码
/*int a[] = {1,4,3,7,8,5};
	for (int i = 0; i < 6; i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
	QuickSort(a, 6);
	for (int i = 0; i < 6; i++)
	{
		std::cout << a[i] << " ";
	}*/

std::fstream openfile(const String &filename, String &s)
{
	char data[256] = { 0 };
	std::fstream f(filename, std::ios::in);
	if (f.is_open())
	{
		while (!f.eof())
		{
			f.getline(data, 256);
			s.append(data);
			s.push_back('\n');
		}
	}
	else
		std::cout << "file is not opening" << std::endl;
	return f;
}

StringBuffer split(const char *str, int len, char splitter = ' ')
{
	String temp;
	StringBuffer vs;
	for (int i = 0; i < len; i++)
	{
		if (str[i] != splitter)
		{
			temp.push_back(str[i]);
		}
		else
		{
			vs.push_back(temp);
			temp.clear();
		}
	}
	vs.push_back(temp);
	temp.clear();
	return vs;
}

String input()
{
	String str;
	
	char c[MAXSTRING] = { 0 };
	std::cin.getline(c, MAXSTRING);
	int len = std::stoi(str.append(c));
	//std::cout << "num: " << len << std::endl;
	for (int i = 0; i < len; i++)
	{		
		char cc[MAXSTRING] = { 0 };
		str.push_back('\n');
		std::cin.getline(cc, MAXSTRING);
		str.append(cc);
	}
	//std::cout << str << std::endl;
	return str;
}
//正确案例
/*#include <bits/stdc++.h>
 
using namespace std;
 
struct Point
{
    int x, y;
};
 
Point points[500001];
 
int main()
{
    int n;
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        scanf("%d%d", &points[i].x, &points[i].y);
    }
    //按照y升序 x降序排列
    sort(points, points + n,
         [](Point & p1, Point & p2)
    {
        return p1.y == p2.y ? p1.x > p2.x : p1.y < p2.y;
    });
    printf("%d %d\n", points[n - 1].x, points[n - 1].y);
    int maxx = points[n - 1].x;
    for (int i = n - 2; i >= 0; i--)
    {
        if (points[i].x > maxx)
        {
            printf("%d %d\n", points[i].x, points[i].y);
            maxx = points[i].x;
        }
    }
    return 0;
}*/