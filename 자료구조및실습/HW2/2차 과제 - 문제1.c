#pragma warning(disable:4996)
#include <stdio.h>

int main()
{
	int N, i, j, array2[4][4] = { 0 };

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
			scanf("%d", &array2[i][j]);
	}

	for (i = 0; i <4; i++)
	{
		for (j = 3; j >= 0; j--)
			printf("%d ", array2[j][i]);
	}
	
	return 0;
}