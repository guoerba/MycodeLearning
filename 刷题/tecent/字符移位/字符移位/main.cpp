#include <iostream>
#include <string>
#include <vector>

typedef std::string				String;
typedef std::vector<String>		StringBuffer;
void StringAlter(String&);
template<class T>
void Swap(T &, T&);

int main()
{
	//String str("AkleBiCeilD");
	//std::cin >> str;
	/*std::cout << str << std::endl;
	StringAlter(str);
	std::cout << str << std::endl;*/
	StringBuffer strbuf;
	String str;
	while (std::cin >> str)
	{
		strbuf.push_back(str);
	}

	for (int i = 0, size = strbuf.size(); i < size; i++)
	{
		StringAlter(strbuf[i]);
		std::cout << (strbuf[i]) << std::endl;
	}
	
	while(1);
}

void StringAlter(String &s)
{
	int originalsize = s.length();
	for (int i = 0, size = s.length(); i < size;)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			for (int j = i; j < originalsize - 1; j++)
			{
				Swap(s[j], s[j + 1]);
			}
			size--;
		}
		else
		{
			i++;
		}
	}
}

template<class	T>
void Swap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}