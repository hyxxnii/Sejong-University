#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void updigits(int n);
int main()
{
	int N;

	scanf("%d", &N);

	updigits(N);

	return 0;
}

void updigits(int n)
{
	if (n < 10)
		printf("%d\n", n);

	else
	{
		printf("%d\n", n % 10);
		updigits(n / 10);
	}
}