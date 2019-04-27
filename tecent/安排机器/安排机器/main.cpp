#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
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
		
	std::sort(tasks.begin(), tasks.end(), [](Task a, Task b)->bool {
		return a.time > b.time;
	});
	printf("size of task %d\n", tasks.size());
	for (auto i : tasks)
	{
		
	}

	
	while (1);
	return 0;
}