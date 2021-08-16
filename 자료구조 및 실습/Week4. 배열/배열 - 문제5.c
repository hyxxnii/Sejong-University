#pragma warning(disable:4996)
#include <stdio.h>

int main()
{
	int N, M, i, j, r;
	int cnt = 0, num = 1, n = 0;
	int **p = NULL;

	scanf("%d %d", &N, &M);

	p = (int **)malloc(N * sizeof(int *));
	if (p == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	for (i = 0; i < N; i++)
	{
		p[i] = (int *)malloc(M * sizeof(int));
		if (p[i] == NULL)
		{
			printf("Not enough memory!");
			return -1;
		}
	}

	for (r = 0; r < M; r++)
	{
		i = 0, j = cnt;
		cnt = 0;

		while (1)
		{
			if ((cnt > n) || (i == N))
				break;

			p[i][j] = num;
			num++;
			cnt++;
			i++;
			j--;
		}
		if (cnt <= n)
			cnt = n + 1;

		n++;
	}

	cnt = N - 1;

	for (r = 0; r < N - 1; r++)
	{
		i = N - cnt, j = M - 1;
		n = 0;

		while (1)
		{
			if ((cnt <= n) || (i == N) || (j < 0))
				break;

			p[i][j] = num;
			num++;
			i++;
			j--;
			n++;
		}
		cnt--;
	}

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
			printf(" %d", p[i][j]);

		printf("\n");
	}

	for (i = 0; i < N; i++)
		free(p[i]);
	free(p);

	return 0;
}