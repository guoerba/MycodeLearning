/*���ӣ�https://www.nowcoder.com/questionTerminal/2f45f0ef94724e06a4173c91ef60781c
��Դ��ţ����

��Ϸ�����кܶ��ʽ����������������һ���������ֻ����һ�Σ���������һ����1024��������ID��Χ[1,1024]������32��unsigned int��������¼��1024�������Ƿ��Ѿ���ɡ���ʼ״̬����δ��ɡ� ����������������������ID����Ҫ���õ�һ��ID������Ϊ�Ѿ���ɣ������ڶ���ID�������Ƿ��Ѿ���ɡ� ���һ������������ڶ���ID�������Ѿ�������1�����δ������0�������һ��ڶ���ID����[1,1024]��Χ�������-1��

��������:

�������һ��,����������ʾ����ID.



�������:

����Ƿ����

ʾ��1
����

1024 1024

���

1*/
#include <iostream>
#include <vector>
#include <string>

typedef unsigned int				uint;
uint task[4] = { 0,0,0,0 };

void SetBit(uint *t, uint id);
int SearchBit(uint *t, uint id);

int main()
{
	uint a, b;
	std::cin >> a >> b;
	SetBit(task, a);
	std::cout << SearchBit(task, b) << std::endl;
	while (1);
	return 0;
}

void SetBit(uint *t, uint id)
{
	uint index = id - 1;
	t[index / 32] |= 1 << (index % 32);
}

int SearchBit(uint *t, uint id)
{
	if (id < 1 || id > 1024)
		return -1;
	uint index = id - 1;
	uint shift = index % 32;
	return (t[(index) / 32] & (1 << shift)) >> shift;
}