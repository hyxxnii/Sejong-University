#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

void ABC(int x[], int k);
int main()
{
	int n[10] = { 0 }, i;

	for (i = 0; i < 10; i++)
		scanf("%d", &n[i]);

	for (i = 0; i < 10; i++)
		ABC(n, i);

	for (i = 0; i < 10; i++)
		printf(" %d", n[i]);

	return 0;
}

void ABC(int x[], int k)
{
	int i, j, max = x[k], idx = k;
	int *tmp;

	for (i = k; i < 10; i++)
	{
		if (max < x[i])
		{
			max = x[i];
			idx = i;
		}
	}

	tmp = *(x+k);
	*(x+k) = *(x+idx);
	*(x+idx) = tmp;
}