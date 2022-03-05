#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>

typedef std::vector<int>			VectorInt;
typedef std::vector<std::string>	StringBuffer;
typedef std::string					String;
template<class T>
struct vector_typedef{
	typedef std::vector<T> Vector;
};
typedef std::vector<std::stack<int> >	StackBufferInt;
typedef std::stack<int>					StackInt;

String input_data();
std::fstream openfile(const String &filename, String &s);
StringBuffer split(const char *str, int len, char splitter);
StringBuffer split(const String &str, char splitter);
StackBufferInt MeasureSession(const String &str);
StackInt Session(const StringBuffer &strbuf);
template<class T>
bool HasElement(const std::vector<T> &vector, T element);
template<class T>
std::stack<T> MoveElementToStackTop(std::stack<T> &stack, T element);

String input_data()
{

	int num;
	std::cin >> num;
	String s;
	s.append(std::to_string(num));
	num *= 2;
	for (int i = 0; i < num + 1; i++)
	{
		char buf[256] = { 0 };
		std::cin.getline(buf,256);
		s.append(buf);
		s.push_back('\n');
	}
	std::cout << s << std::endl;
	return s;
}

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

StringBuffer split(const String &str, char splitter = ' ')
{
	return split(str.c_str(), str.size(), splitter);
}

StackBufferInt MeasureSession(const String &str) 
{
	StackBufferInt stbuf;
	StringBuffer vs = split(str, '\n');
	
	
	for (int i = 1, size = atoi(vs[0].c_str()); i <= size; i++)
	{
		//std::cout << "第" << i << "个会话测试案例: " << vs[i * 2] << std::endl;
		/*for (int j = 0, size = std::stoi(vs[i * 2 - 1]); j < size; j++)
		{	
			StackInt st = Session(split(vs[i * 2], ' '));
			stbuf.push_back(st);
		}*/
		StackInt st = Session(split(vs[i * 2], ' '));
		stbuf.push_back(st);
	}

	return stbuf;
}

//Session测试代码
/*String s("1 6 3 3 1 8 1");
	StringBuffer sbuf = split(s,' ');
	StackInt st = Session(sbuf);
	while (!st.empty())
	{
		std::cout << st.top() << " ";
		st.pop();
	}
	std::cout << std::endl;*/
StackInt Session(const StringBuffer &strbuf)
{
	StackInt stack;
	VectorInt record;
	for (int i = 0, size = strbuf.size(); i < size; i++)
	{
		int element = atoi(strbuf[i].c_str());
		if (HasElement(record, element))
		{
			MoveElementToStackTop(stack, element);
		}
		else
		{
			stack.push(element);
			record.push_back(element);
		}
	}
	return stack;
}

int main()
{
	//String s = input_data();
	String s;
	std::fstream f = openfile("./data.txt", s);
	//std::cout << s << std::endl;
	StackBufferInt stbuf = MeasureSession(s);
	for (auto st : stbuf)
	{
		while (!st.empty())
		{
			std::cout << st.top() << " ";
			st.pop();
		}
		std::cout << std::endl;
	}
	//f.close();
	

	while (1);
	return 0;
}

template<class T>
std::stack<T> MoveElementToStackTop(std::stack<T> &stack, T element)
{
	if (stack.empty())
		return stack;
	if (stack.size() == 1)
		return stack;
	std::stack<T> tempstack;
	T temp, target;
	while ((temp = stack.top()) != element)
	{
		stack.pop();
		tempstack.push(temp);
	}
	target = temp;
	stack.pop();
	while (!tempstack.empty())
	{
		temp = tempstack.top();
		stack.push(temp);
		tempstack.pop();
	}
	stack.push(target);
	return stack;
}
//MoveElementToStackTop测试代码
/*std::stack<int> s,st;
	for (int i = 0; i < 10; i++)
		s.push(i);
	st = s;
	while (!st.empty())
	{
		std::cout << st.top() << " ";
		st.pop();
	}
	std::cout << std::endl;

	MoveElementToStackTop(s, 5);
	st = s;
	while (!st.empty())
	{
		std::cout << st.top() << " ";
		st.pop();
	}
	std::cout << std::endl;*/

template<class T>
bool HasElement(const std::vector<T> &vector, T element)
{
	if (vector.empty())
		return false;
	for (auto i : vector)
	{
		if (i == element)
		{
			return true;
		}
	}
	return false;
}