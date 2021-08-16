#pragma warning(disable:4996)
#include <stdio.h>

int main()
{
	int N, i, j, cnt = 1;
	int **p = NULL;

	scanf("%d", &N);


	p = (int **)malloc(N * sizeof(int *));
	if (p == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	for (i = 0; i < N; i++)
	{
		p[i] = (int *)malloc(N * sizeof(int));
		if (p[i] == NULL)
		{
			printf("Not enough memory!");
			return -1;
		}

		for (j = 0; j < N; j++)
		{
			if (i % 2 == 0)
			{
				p[i][j] = cnt;
				cnt++;
			}
			else
			{
				p[i][N - j - 1] = cnt;
				cnt++;
			}

		}
	}

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			printf(" %d", p[i][j]);
		
		printf("\n");
	}

	for (i = 0; i < N; i++)
		free(p[i]);
	free(p);

	return 0;
}