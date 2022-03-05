#pragma once
#include "../include/alloc2darray.h"
#include "../include/StringIntegration.h"
#include "../include/stringoperation.h"
#pragma comment(lib,"..//lib//alloc2darray.lib")


class IntegrateDivde
{
public:
	enum Type {
		CompleteResult,				//���н��
		Complete,					//��n���ֳɲ�����m�Ļ��ַ�
		DifferentResult,
		Different,					//���ֶ����ͬ������
		FixedCountResult,
		FixedCount,					//n���ֳ�k�����Ļ��ַ�
		OddResult,
		Odd,						//n���ֳ����������Ļ��ַ�
	};
	IntegrateDivde();
	IntegrateDivde(int num,Type t = Complete);
	IntegrateDivde(int num,int n, Type t = Complete);
	~IntegrateDivde();

	int result();
	std::string results();
private:
	int findcompletenumber(int n, int m);
	void findcomplete(int n, int m, std::string&temp, std::string&res);//�ҵ�m��n����
	//��������Ļ��֣�Ҫ�󻮷���������ͬ
	int finddifferentnumber(int n, int m);
//item:��ʱ���飻res:������飻n:m��n���� m:Ҫ�������
	void finddifferent(int n, int m, std::string&temp, std::string&res);//֧��m����9�İ汾

	int findfixedcountnumber(int n, int m);
	void findfixedcount(int n, int m);
	void findfixedcount(int n, int m, std::vector<int>&temp, std::string&res);

	

	int integrate,divide;
	int res;
	
	std::string temp;
	std::string ares;
};

