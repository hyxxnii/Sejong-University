#pragma warning(disable:4996)
#include <stdio.h>

int main()
{
	int N, M, i, j, r;
	int cnt = 1, num = 1, x, y, even = 0, odd = 0;
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

	i = 0;
	j = 0;
	x = M;
	y = N - 1;

	while (1)
	{
		if (num == (N*M) + 1)
			break;

		if (cnt % 2 != 0)
		{
			if (odd == 0)
			{
				for (r = 0; r < x; r++)
				{
					p[i][j] = num;
					num++;
					j++;
				}
				x--;
				odd++;
				cnt++;
				i++;
				j--;
			}

			else
			{
				for (r = 0; r < x; r++)
				{
					p[i][j] = num;
					num++;
					j--;
				}
				x--;
				odd--;
				cnt++;
				i--;
				j++;
			}
		}

		if (cnt % 2 == 0)
		{
			if (even == 0)
			{
				for (r = 0; r < y; r++)
				{
					p[i][j] = num;
					num++;
					i++;
				}
				y--;
				even++;
				cnt++;
				j--;
				i--;
			}

			else
			{
				for (r = 0; r < y; r++)
				{
					p[i][j] = num;
					num++;
					i--;
				}
				y--;
				even--;
				cnt++;
				j++;
				i++;
			}
		}
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