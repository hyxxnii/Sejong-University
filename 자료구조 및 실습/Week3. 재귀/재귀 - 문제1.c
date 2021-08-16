#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum_n(int n);
int main()
{
	int n, sum = 0;

	scanf("%d", &n);
	
	sum = sum_n(n);

	printf("%d", sum);

	return 0;
}

int sum_n(int n)
{
	if (n == 1)
		return 1;
	else
		return (n + sum_n(n - 1));
}