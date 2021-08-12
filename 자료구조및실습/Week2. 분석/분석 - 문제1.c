#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int modulo(int a, int b);
int main()
{
	int a, b, num = 0;

	scanf("%d %d", &a, &b);

	num = modulo(a, b);

	printf("%d", num);

	return 0;
}

int modulo(int a, int b)
{
	if (a == 0)
		return a;

	else if (a < b)
		return a;

	else
	{
		while (a >= b)
		{
			a = a - b;
		}
		 
		return a;
	}
}