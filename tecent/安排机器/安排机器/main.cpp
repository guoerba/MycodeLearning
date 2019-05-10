#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <chrono>
#include <ctime>
/*按照时间和等级降序，这样保证取到的一定是收益最大的解（因为时间的收益严格大于等级，
所以时间作为第一关键字，如果能完成收益大的任务，自然不会去完成收益低的任务）；然后在
此基础上，把所有工作时间大于等于任务的机器加入一个等级数组中，取出等级最接近任务等级
的，且大于等于任务等级的，就是下限，这样可以保证完成的任务一定是最多的，不会遗漏。（
因为任务和机器都按照时间进行过排序，那么在等级数组中机器的时间一定是可以完成后续任务
的，它们是被时间更长的任务选择进来的，所以在此不需要考虑机器的工作时间了，在后面他们
的时间不会有区别都是一样的，为了防止后面出现等级更大的任务，那么肯定要选择等级刚好大
于任务的机器了），这样两次贪心下来得到的就是一定是最优解了，而且第二次贪心可以二分，
不会超时。
--------------------- 
作者：weixin_33836874 
来源：CSDN 
原文：https://blog.csdn.net/weixin_33836874/article/details/87040827 
版权声明：本文为博主原创文章，转载请附上博文链接！*/
//双贪心，尽可能安排时间长的工作给相应等级的机器
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
	std::map< int, std::vector<Machine> >machineGroups;//等级数组
	for (auto iter = machines.begin(); iter != machines.end(); ++iter)///找出最大的等级
	{
		if ((*iter).rank > biggestMachineRank)
			biggestMachineRank = (*iter).rank;
	}
		
	for (auto iter = machines.begin(); iter != machines.end(); ++iter)
		machineGroups[(*iter).rank].push_back(*iter);

	for (int i = 0; i <= biggestMachineRank; i++)
	{
		if (machineGroups[i].empty())
		{
			std::vector<Machine>init;
			init.push_back(Machine(0, 0));
			machineGroups[i] = init;
		}
	}

	/*for (auto iter : machineGroups)
	{
		printf("等级数组%d\n", iter.first);
		for (auto i : iter.second)
		{
			printf("Machine longgestWorkTime = %d,rank = %d\n", i.longgestWorkTime, i.rank);
		}
		printf("\n");
	}*/

	int finishedTasks = 0, profits = 0;
	std::vector<int>machineGroupsIndex(biggestMachineRank + 1);//用来指明指定等级数组的最大工作时间机器的索引值
	for (auto iter = machineGroupsIndex.begin(); iter != machineGroupsIndex.end(); ++iter)
		*iter = 0;
	for (auto iter = tasks.begin(); iter != tasks.end(); ++iter)
	{
		for (int r = (*iter).rank; r <= biggestMachineRank; r++)
		{
			if (machineGroupsIndex[r] < machineGroups[r].size())
			{
				if (machineGroups[r][machineGroupsIndex[r]].longgestWorkTime >= (*iter).time)//如果机器可以胜任这个工作
				{
					profits += 200 * (*iter).time + 3 * (*iter).rank;
					++finishedTasks;
					machineGroupsIndex[r] += 1;
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
//测试代码
