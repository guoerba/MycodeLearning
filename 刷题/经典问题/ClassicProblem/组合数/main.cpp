#include "../include/alloc2darray.h"
#include "../include/StringIntegration.h"
#include "../include/stringoperation.h"
#pragma comment(lib,"..//lib//alloc2darray.lib")

typedef unsigned int	uint;

uint Combination(uint m, uint n)
{
	Array2d<uint>c(m + 1, m + 1, 
		[](uint row, uint col)->int 
	{
		if (!col)
			return 1;
		else if (row == col)
			return 1;
		else
			return 0;
	});

	for (uint i = 1; i <= m; i++)
	{
		for (uint j = 1; j < i; j++)
		{
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
		}
	}

	return c[m][n];
}
	/*for (uint i = 0; i <= m; i++)
	{
		for (uint j = 0; j <= m; j++)
		{
			std::cout << c[i][j] << " ";
		}
		std::cout << std::endl;
	}
*/
int main()
{
	std::cout << Combination(10, 9) << std::endl;
	while (1);
	return 0;
}