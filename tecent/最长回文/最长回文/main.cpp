#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::string>	StringBuffer;
typedef std::string					String;

template<class T>
T **CreateArray2D(int row, int col, T initialize);
template<class T>
void DeleteArray2D(T **p);

int LonggestSymmetricString(String &s);

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
	void append(const Array &b)
	{
		T *n = new T[this->len + b.len];
		for (int i = 0; i < this->len; i++)
		{
			n[i] = this->a[i];
		}
		for (int i = 0; i < b.len; i++)
		{
			n[i + this->len] = b.a[i];
		}
		delete[] this->a;
		a = n;
		this->len = this->len + b.len;
	}
};

int main()
{
	String str;
	StringBuffer strbuf;
	while (std::cin >> str)
	{
		strbuf.push_back(str);
	}
	//std::cin >> str;
	for (int i = 0, size = strbuf.size(); i < size; i++)
	{
		std::cout << strbuf[i].length() - LonggestSymmetricString(strbuf[i]) << std::endl;
	}
	/*String str("zgtklhfzomzjckwmluvivvcmhjrwkuvcjrxojobpdedpamdshcwwsetfbacvonecrdvugeibglvhxuymjvoryqjwullvzglqazxrdmczyvbgakjagttrezmvrlptiwoqkrtxuroeqmryzsgokopxxdpbejmtwvpnaqrgqladdszhdwxfckmewhdvihgvacueqhvwvjxoitlpfrckxkuksaqzjpwgoldyhugsacflcdqhifldoaphgdbhaciixouavqxwlghadmfortqacbffqzocinvuqpjthgekunjsstukeiffjipzzabkuiueqnjgkuiojwbjzfynafnlcaryygqjfixaoeowhkxkbsnpsvnbxuywfxbnuoemxynbtgkqtjvzqikbafjnpbeirxxrohhnjqrbqqzercqcrcswojyylunuevtdhamlkzqnjrzibwckbkiygysuaxpjrgjmurrohkhvjpmwmmtpcszpihcntyivrjplhyrqftghglkvqeidyhtmrlcljngeyaefxnywpfsualufjwnffyqnpitgkkyrbwccqggycrvoocbwsdbftkigrkcbojuwwctknzzmvhbhbfzrqwzllulbabztqnznkqdyoqnrxhwavqhzyzvmmmphzxbikpharseywpfsqyybkynwbdrgfsaxduxojcdqcjuaywzbvdjgjqtoffasiuhvxcaockebkuxpiomqmtvsqhnyxfjceqevqvnapbk");
	std::cout << str.length() - LonggestSymmetricString(str);*/
	while (1);
}
/*A[i,j] = A[i+1,j-1] + 2   		if s[i] == s[j]
A[i,j] = max( A[i,j-1],A[i+1,j])	if s[i] != s[j]			
*/
int LonggestSymmetricString(String &s)
{
	if (s.empty())
		return 0;
	if (s.length() == 1)
		return 1;
	int len = s.length();
	int **dp = CreateArray2D<int>(len, len,1);
	for (int i = 1; i < len; i++)
	{
		for (int j = 0; j < i; j++)
		{
			dp[i][j] = 0;
		}
	}
	/*for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			printf("%d ", dp[i][j]);
		}
		printf("\n");
	}*/
	for (int l = 2; l <= len; l++)
	{		
		for (int i = 0, isize = len - l; i <= isize; i++)
		{
			int j = i + l - 1;
			if (s[i] == s[j])
			{
				dp[i][j] = dp[i + 1][j - 1] + 2;
			}
			else
			{
				//dp[i][j] = dp[i + 1][j - 1];
				int a = dp[i][j - 1], b = dp[i + 1][j];
				a > b ? dp[i][j] = a : dp[i][j] = b;
			}
		}
	}
	int ret = dp[0][len - 1];
	DeleteArray2D(dp);
	return ret;
}

template<class T>
T **CreateArray2D(int row, int col,T initialize = 0)
{
	T **p = new T*[row];
	*p = new T[row*col];
	for (int i = 0; i < row; i++)
		p[i] = *p + i * col;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			p[i][j] = initialize;
	return p;
}


template<class T>
void DeleteArray2D(T **p)
{
	delete[] * p;
	delete[] p;
	p = NULL;
}