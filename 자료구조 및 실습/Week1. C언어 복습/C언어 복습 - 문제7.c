#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>

int main()
{
	int N, i;
	int *p, *q, *z;

	scanf("%d", &N);
	p = (int *)malloc(N * sizeof(int));
	if (p == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	q = (int *)malloc(N * sizeof(int));
	if (q == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	z = (int *)malloc(N * sizeof(int));
	if (z == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	for (i = 0; i < N; i++)
		scanf("%d", &p[i]);

	for (i = 0; i < N; i++)
		scanf("%d", &q[i]);

	for (i = 0; i < N; i++)
	{
		z[i] = p[i] + q[N - i - 1];
		printf(" %d", z[i]);
	}

	free(p);
	free(q);
	free(z);

	return 0;
}