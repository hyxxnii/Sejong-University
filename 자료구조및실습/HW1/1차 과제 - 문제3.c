#pragma warning(disable:4996)
#include <stdio.h>

int Involution(int a, int b);
int main()
{
	int a, b, ans=0;

	scanf("%d %d", &a, &b);

	ans = Involution(a, b);

	printf("%d", ans);

	return 0;
}

int Involution(int a, int b)
{
	if (b == 0)
		return 1;

	else if (b % 2 == 0)
		return Involution(a*a, b / 2);

	else
		return a * Involution(a*a, (b - 1) / 2);
}