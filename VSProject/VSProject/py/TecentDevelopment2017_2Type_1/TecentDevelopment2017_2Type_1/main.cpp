#include <iostream>

int main()
{
	char s[256] = { 0 };
	int a[4] = { 0 };
	std::cin >> s;
	int len = 0;
	while (s[len])
	{
		a[len++] = s[len] - 97;
	}
	int index = (a[0] * 15628) + (a[1] + 1) * 625 + (a[2] + 1) *25 + a[3];
	std::cout << index << std::endl;

//	while (1);
	return 0;
}
/*
#include <iostream> 
#include <string> 
#include <math.h> 
using namespace std; 
int main()
{ 
	string s; 
	cin>>s; 
	int len=s.length(); 
	int index=0; 
	for(int i=0;i<len;i++,index++)
	{ 
		int n=s[i]-'a'; 
		for(int j=0;j<4-i;j++)
		{
			index+=n*pow(25,j);
        }
    } 
	cout<<index-1<<endl; return 0;
}*/