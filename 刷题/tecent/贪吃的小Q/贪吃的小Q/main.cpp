#include <iostream>

//��̰�ļ��裬ÿһ��ĳԵ�������ǰһ���һ�룬����һ���һ(����ȡ��)������������Mһ��������¿���ʹ��һ��Ե����
int sum(int d,int N)//��һ���d��������ܹ��Զ��ٿ�
{
	int sum = 0,s = d;
	for (int i = 0; i < N; i++)
	{
		sum += s;
		//s >>= 1;
		s = (s + 1) >> 1;//��Ҫ��������d[i]>=0.5*d[i-1]������ȡ����,��s>>1��ʾs/2������ȡ����������Ҫs+1
	}
	return sum;
}

int solution(int N, int M)
{
	int low = 1, high = M;//��һ����ԳԵķ�Χ��[1,M]
	while (low < high)//���ֲ��ң����ϵĳ��Ե���һ��Ե�����Ϊmidʱ���ܹ��Ե����Ƿ����M��
	{
		//int mid = (low + high) >> 1;
		int mid = (low + high + 1) >> 1;//����ȡ��(a+1)>>1
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

/*// ��ͨ���ֲ���
int bsearch(int *A, int l, int r, int val){ // [l, r)
	while(l < r){
		int mid = l + (r - l) / 2;
		if(A[mid] == val) return mid;
		else if(A[mid] > val) r = mid;
		else l = mid + 1;
	}
	return -1;
}
 
// �����½�
// �� x ����ʱ���������ֵĵ�һ��λ�ã����򷵻�����һ���±� i��
// �ڴ˴����� val ��������Ȼ����
int lower_bound(int *A, int l, int r, int val){ // [l, r)
	while(l < r){
		int mid = l + (r - l) / 2;
		if(A[mid] >= val) r = mid;
		else l = mid + 1;
	}
	return l;
}
 
// �����Ͻ�
// �� x ����ʱ���������ֵ����һ��λ�ú���һ��λ�ã����򷵻�����һ���±� i��
// �ڴ˴����� val ��������Ȼ����
int upper_bound(int *A, int l, int r, int val){ // [l, r)
	while(l < r){
		int mid = l + (r - l) / 2;
		if(A[mid] <= val) l = mid + 1;
		else r = mid;
	}
	return l;
}
--------------------- 
���ߣ�o-pqy-o 
��Դ��CSDN 
ԭ�ģ�https://blog.csdn.net/u013351484/article/details/38639949 
��Ȩ����������Ϊ����ԭ�����£�ת���븽�ϲ������ӣ�*/