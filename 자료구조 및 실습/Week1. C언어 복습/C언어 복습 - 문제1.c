#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int sum(int n);
int main()
{
	int x, num = 0;

	scanf("%d", &x);

	num = sum(x);

	printf("%d", num);

	return 0;
}

int sum(int n)
{
	int i, j, sum = 0, res = 0;

	for (i = 1; i <=n; i++)
	{
		for (j = 1; j <= i; j++)
			sum += j;

		res += sum;
		sum = 0;
	}

	return res;
}