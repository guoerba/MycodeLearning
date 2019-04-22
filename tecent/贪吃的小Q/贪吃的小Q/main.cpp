#include <iostream>

//做贪心假设，每一天的吃的数量是前一天的一半，或者一半加一(向上取整)，这样在总量M一定的情况下可以使第一天吃的最多
int sum(int d,int N)//第一天吃d个情况下总共吃多少块
{
	int sum = 0,s = d;
	for (int i = 0; i < N; i++)
	{
		sum += s;
		//s >>= 1;
		s = (s + 1) >> 1;//需要满足条件d[i]>=0.5*d[i-1]（向上取整）,而s>>1表示s/2并向下取整，所以需要s+1
	}
	return sum;
}

int solution(int N, int M)
{
	int low = 1, high = M;//第一天可以吃的范围是[1,M]
	while (low < high)//二分查找（不断的尝试当第一天吃的数量为mid时，总共吃的量是否等于M）
	{
		//int mid = (low + high) >> 1;
		int mid = (low + high + 1) >> 1;//向上取整(a+1)>>1
		int s = sum(mid, N);
		if (s == M)		
			return mid;		
		else if (s > M)		
			high = mid - 1;		
		else if (s < M)
			low = mid;
	}
	return (low + high) >> 1;
}

int main()
{
	int N, M;
	std::cin >> N >> M;
	
	std::cout << solution(N, M) << std::endl;

	while (1);
	return 0;
}

/*// 普通二分查找
int bsearch(int *A, int l, int r, int val){ // [l, r)
	while(l < r){
		int mid = l + (r - l) / 2;
		if(A[mid] == val) return mid;
		else if(A[mid] > val) r = mid;
		else l = mid + 1;
	}
	return -1;
}
 
// 查找下界
// 当 x 存在时返回它出现的第一个位置，否则返回这样一个下标 i；
// 在此处插入 val 后序列仍然有序
int lower_bound(int *A, int l, int r, int val){ // [l, r)
	while(l < r){
		int mid = l + (r - l) / 2;
		if(A[mid] >= val) r = mid;
		else l = mid + 1;
	}
	return l;
}
 
// 查找上界
// 当 x 存在时返回它出现的最后一个位置后面一个位置，否则返回这样一个下标 i；
// 在此处插入 val 后序列仍然有序
int upper_bound(int *A, int l, int r, int val){ // [l, r)
	while(l < r){
		int mid = l + (r - l) / 2;
		if(A[mid] <= val) l = mid + 1;
		else r = mid;
	}
	return l;
}
--------------------- 
作者：o-pqy-o 
来源：CSDN 
原文：https://blog.csdn.net/u013351484/article/details/38639949 
版权声明：本文为博主原创文章，转载请附上博文链接！*/