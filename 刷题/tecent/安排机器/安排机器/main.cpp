#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <chrono>
#include <ctime>
/*����ʱ��͵ȼ�����������֤ȡ����һ�����������Ľ⣨��Ϊʱ��������ϸ���ڵȼ���
����ʱ����Ϊ��һ�ؼ��֣���������������������Ȼ����ȥ�������͵����񣩣�Ȼ����
�˻����ϣ������й���ʱ����ڵ�������Ļ�������һ���ȼ������У�ȡ���ȼ���ӽ�����ȼ�
�ģ��Ҵ��ڵ�������ȼ��ģ��������ޣ��������Ա�֤��ɵ�����һ�������ģ�������©����
��Ϊ����ͻ���������ʱ����й�������ô�ڵȼ������л�����ʱ��һ���ǿ�����ɺ�������
�ģ������Ǳ�ʱ�����������ѡ������ģ������ڴ˲���Ҫ���ǻ����Ĺ���ʱ���ˣ��ں�������
��ʱ�䲻����������һ���ģ�Ϊ�˷�ֹ������ֵȼ������������ô�϶�Ҫѡ��ȼ��պô�
������Ļ����ˣ�����������̰�������õ��ľ���һ�������Ž��ˣ����ҵڶ���̰�Ŀ��Զ��֣�
���ᳬʱ��
--------------------- 
���ߣ�weixin_33836874 
��Դ��CSDN 
ԭ�ģ�https://blog.csdn.net/weixin_33836874/article/details/87040827 
��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�*/
//˫̰�ģ������ܰ���ʱ�䳤�Ĺ�������Ӧ�ȼ��Ļ���
struct Machine {
	int longgestWorkTime;
	int rank;
	bool isable;
	Machine():longgestWorkTime(0),rank(0){}
	Machine(int lwt,int r):longgestWorkTime(lwt),rank(r){}
};

struct Task {
	int time;
	int rank;
	Task():time(0),rank(0){}
	Task(int t,int r):time(t),rank(r){}
};

void GenerateTest(std::vector<Task> &tasks, int range_time, int range_rank);
int emergerand(int upper, int lower);
void test();

int main()
{
	int n, m;
	std::cin >> n >> m;

	std::vector<Machine>machines(n);
	std::vector<Task>tasks(m);
	for (int i = 0; i < n; i++)
	{
		int lwt, r;
		std::cin >> lwt >> r;
		machines[i] = Machine(lwt, r);
	}
	for (int i = 0; i < m; i++)
	{
		int t, r;
		std::cin >> t >> r;
		tasks[i] = Task(t, r);
	}

	std::sort(tasks.begin(), tasks.end(), [](const Task &a,const Task &b)->bool {
		if (a.time > b.time)
			return true;
		else
			return false;
	});

	std::sort(machines.begin(), machines.end(), [](const Machine &a,const Machine &b)->bool {
		if (a.longgestWorkTime > b.longgestWorkTime)
			return true;
		else
			return false;
	});

	int biggestMachineRank = 0;
	std::map< int, std::vector<Machine> >machineGroups;//�ȼ�����
	for (auto iter = machines.begin(); iter != machines.end(); ++iter)//�ҳ����ĵȼ�
	{
		if ((*iter).rank > biggestMachineRank)
			biggestMachineRank = (*iter).rank;
	}
		
	for (auto iter = machines.begin(); iter != machines.end(); ++iter)//�������ŵ���Ӧ�ĵȼ�������
		machineGroups[(*iter).rank].push_back(*iter);

	for (int i = 0; i <= biggestMachineRank; i++)//��ʼ��û�з��䵽��
	{
		if (machineGroups[i].empty())
		{
			std::vector<Machine>init;
			init.push_back(Machine(-1, -1));
			machineGroups[i] = init;
		}
	}

	/*for (auto iter : machineGroups)
	{
		printf("�ȼ�����%d\n", iter.first);
		for (auto i : iter.second)
		{
			printf("Machine longgestWorkTime = %d,rank = %d\n", i.longgestWorkTime, i.rank);
		}
		printf("\n");
	}*/
		
	int finishedTasks = 0, profits = 0;
	std::vector<int>machineGroupsIndex(biggestMachineRank + 1);//����ָ��ָ���ȼ�����������ʱ�����������ֵ
	for (auto iter = machineGroupsIndex.begin(); iter != machineGroupsIndex.end(); ++iter)
		*iter = 0;
	for (auto iter = tasks.begin(); iter != tasks.end(); ++iter)//��������
	{
		for (int r = (*iter).rank; r <= biggestMachineRank; r++)//�����ȼ����ڵ�������ȼ��Ļ���
		{
			if (machineGroupsIndex[r] < machineGroups[r].size())//���������ȼ��л���
			{
				if (machineGroups[r][machineGroupsIndex[r]].longgestWorkTime >= (*iter).time)//�����������ʤ���������
				{
					profits += 200 * (*iter).time + 3 * (*iter).rank;
					++finishedTasks;
					machineGroupsIndex[r] += 1;
					break;
				}
			}
		}
	}

	std::cout << finishedTasks << " " << profits << std::endl;
	//test();
	
	while (1);
	return 0;
}

void GenerateTest( std::vector<Task> &tasks,int range_time,int range_rank)
{
	for (int i = 0, size = tasks.size(); i < size; i++)
		tasks.push_back(Task(emergerand(range_time, 1), emergerand(range_rank, 1)));
}

int emergerand(int upper, int lower)
{
	return rand() % (upper - lower + 1) + lower;
}

void test()
{
	srand(std::chrono::seconds(std::time(NULL)).count());
	std::vector<Task>tasks(50);
	GenerateTest(tasks, 1000, 3);
	for (auto i : tasks)
	{
		printf("Task time:%d rank:%d\n", i.time, i.rank);
	}

	std::sort(tasks.begin(), tasks.end(), [](const Task &a,const Task &b)->bool {
		if (a.time > b.time)
			return true;
		else
			return false;
	});
	printf("size of task %d\n", tasks.size());
	printf("-----------------\n");
	for (auto i : tasks)
	{
		printf("Task time:%d rank:%d\n", i.time, i.rank);
	}
}
//���Դ���
