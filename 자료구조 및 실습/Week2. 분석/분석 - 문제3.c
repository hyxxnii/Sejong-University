#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prefixAverages1(int A[], int n);
int prefixAverages2(int A[], int n);
int main()
{
	int x, i, *p, *q;

	scanf("%d", &x);
	
	p = (int *)malloc(x * sizeof(int));
	if (p == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	q = (int *)malloc(x * sizeof(int));
	if (q == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	for (i = 0; i < x; i++)
		scanf("%d", &p[i]);

	q = prefixAverages1(p, x);
	for (i = 0; i < x; i++)
		printf("%d ", q[i]);

	printf("\n");

	q = prefixAverages2(p, x);
	for (i = 0; i < x; i++)
		printf("%d ", q[i]);

	free(p);
	free(q);

	return 0;
}
int prefixAverages1(int A[], int n)
{
	int i, j;
	int *p;
	double sum = 0.0;

	p = (int *)malloc(n * sizeof(int));
	if (p == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	for(i = 0; i < n; i++)
	{
		sum = 0;

		for (j = 0; j <= i; j++)
			sum += A[j];

		p[i] = (int)(sum / (i + 1) + 0.5);
	}
	
	return p;
}

int prefixAverages2(int A[], int n)
{
	int *p;
	int i = 0;
	double sum = 0.0;

	p = (int *)malloc(n * sizeof(int));
	if (p == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	for (i = 0; i < n; i++)
	{
		sum += A[i];
		p[i] = (int)(sum / (i + 1) + 0.5);
	}

	return p;
}