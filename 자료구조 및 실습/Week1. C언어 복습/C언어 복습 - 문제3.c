#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

void swap(int *p, int *q);
int main()
{
	int N, i, a, b;
	int *p;

	scanf("%d", &N);

	p = (int *)malloc(N * sizeof(int));
	if (p == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	for (i = 0; i < N; i++)
		scanf("%d", &p[i]);

	scanf("%d %d", &a, &b);

	swap(p + a, p + b);

	for (i = 0; i < N; i++)
		printf(" %d", p[i]);

	return 0;
}
void swap(int *p, int *q)
{
	int tmp;

	tmp = *p;
	*p = *q;
	*q = tmp;
}