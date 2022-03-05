#include <stdio.h>
#include <iostream>

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

struct Bracelet {
	Array<int> colors;
	Bracelet *next;
	Bracelet() :colors(Array<int>()),next(NULL) {};
	Bracelet(Array<int> c) :colors(c), next(NULL) {};
};



void get()
{
	int n = 0,m = 0,c = 0;
	scanf_s("%d %d %d", &n,&m,&c);
	//Array<int> *fancy = new Array<int>(usrnum);
	for (int i = 0; i < usrnum; i++)
	{
		scanf_s("%d", &(fancy->a[i]));
	}
	/*int arraynum = 0;
	scanf_s("%d", &arraynum);
	Array<InvestigationData> *idata = new Array<InvestigationData>(arraynum);
	for (int i = 0; i < arraynum; i++)
	{
		scanf_s("%d %d %d", &(idata->a[i].signal_1), &(idata->a[i].signal_2), &(idata->a[i].fancy));
	}*/
}

int main()
{
	return 0;
}