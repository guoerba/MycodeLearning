#include "MemAlloc.h"
#include "IntegerPartition.h"
#include <iostream>

int main()
{
	//1+1+1+1+1,1+1+1+2,1+1+3,1+4,1+2+2,2+3,5
	//IntegerPartition ip(5, IntegerPartition::k1);
	IntegerPartition ip(5,3 ,IntegerPartition::k1);
	while (1);
	return 0;
}

/*#include <stdio.h>
int mark[256];
int n;
void DFS(int sum, int k, int prio) {
	if (sum > n) {
		return;
	}
	else if (sum == n) {
		int i;
		printf("=");
		for (i = 0; i < k - 1; i++) {
			printf("%d+", mark[i]);
		}
		printf("%d\n", mark[i]);
	}
	else {
		for (int j = prio; j > 0; j--) {
			mark[k] = j;
			sum += j;
			DFS(sum, k + 1, j);
			sum -= j;  //ª÷∏¥œ÷≥°
		}
	}
}
int main() {
	scanf_s("%d", &n);
	DFS(0, 0, n);
	while (1);
	return 0;
}
*/