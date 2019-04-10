#include <stdio.h>
#include <iostream>
#include <vector>

struct InvestigationData {
	int signal_1;
	int signal_2;
	int fancy;
	InvestigationData() {};
	InvestigationData(int s1, int s2, int f) :signal_1(s1), signal_2(s2), fancy(f) {};
};

template<class T>
struct Array {
	int len;
	T *a;
	Array() { a = NULL; };
	Array(int l) :len(l) { a = new T[len]; };
	~Array() { if (!a) { return; }delete[] a; a = NULL; };
};

void get()
{
	
	int usrnum = 0;
	scanf_s("%d", &usrnum);
	Array<int> *fancy = new Array<int>(usrnum);
	for (int i = 0; i < usrnum; i++)
	{
		scanf_s("%d", &(fancy->a[i]));
	}
	int arraynum = 0;
	scanf_s("%d", &arraynum);
	Array<InvestigationData> *idata = new Array<InvestigationData>(arraynum);
	for (int i = 0; i < arraynum; i++)
	{
		scanf_s("%d %d %d", &(idata->a[i].signal_1), &(idata->a[i].signal_2), &(idata->a[i].fancy));
	}

	printf("class of fancy is: ");
	for (int i = 0; i < usrnum; i++)
	{
		printf(" %d", fancy->a[i]);
	}
	printf("\n");

	printf("emmm->->->-> \n");
	for (int i = 0; i < arraynum; i++)
	{
		printf("%d %d %d\n", (idata->a[i].signal_1), (idata->a[i].signal_2), (idata->a[i].fancy));
	}
	
}

int fancycount(InvestigationData &group,Array<int> &fancyarray)
{
	/*printf("In fancycount s1:%d s2:%d fancy:%d\n", group.signal_1, group.signal_2, group.fancy);
	printf("fancyarray: \n");
	for (int i = 0; i < fancyarray.len; i++)
	{
		printf("fancyarray[%d] = %d\n", i, fancyarray.a[i]);
	}*/
	int fc = 0;
	for (int i = group.signal_1 - 1; i <= group.signal_2 - 1; i++)
	{
		if (fancyarray.a[i] == group.fancy)
		{
			fc++;
		}
	}
	return fc;
}

int main()
{
	//get();

	int usrnum = 0;
	scanf_s("%d", &usrnum);
	Array<int> *fancy = new Array<int>(usrnum);
	for (int i = 0; i < usrnum; i++)
	{
		scanf_s("%d", &(fancy->a[i]));
	}
	int arraynum = 0;
	scanf_s("%d", &arraynum);
	Array<InvestigationData> *idata = new Array<InvestigationData>(arraynum);
	for (int i = 0; i < arraynum; i++)
	{
		scanf_s("%d %d %d", &(idata->a[i].signal_1), &(idata->a[i].signal_2), &(idata->a[i].fancy));
	}

	/*printf("class of fancy is: ");
	for (int i = 0; i < usrnum; i++)
	{
		printf(" %d", fancy->a[i]);
	}
	printf("\n");

	printf("emmm->->->-> \n");
	for (int i = 0; i < arraynum; i++)
	{
		printf("%d %d %d\n", (idata->a[i].signal_1), (idata->a[i].signal_2), (idata->a[i].fancy));
	}*/

	for (int i = 0; i < idata->len; i++)
	{
		printf("%d\n", fancycount(idata->a[i], *fancy));
	}

	delete fancy;
	delete idata;
	while (1);
	return 0;
}