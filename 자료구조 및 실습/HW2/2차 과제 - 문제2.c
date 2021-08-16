#pragma warning(disable:4996)
#include <stdio.h>

int main()
{
	int N, i, j, z, cnt = 0, num[100] = { 0 };

	scanf("%d", &N);

	for (i = 0; i < N; i++)
		scanf("%d", &num[i]);

	for (i = 0; i < N; i++)
	{
		for (j = i + 1; j < N; j++)
		{
			if (num[i] == num[j])
			{
				for (z = j; z < N - 1; z++)
					num[z] = num[z + 1];
				N--;
				i--;
			}
		}
	}

	for (i = 0; i < N; i++)
		printf("%d ", num[i]);
	
	return 0;
}