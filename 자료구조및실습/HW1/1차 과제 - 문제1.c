#pragma warning(disable:4996)
#include <stdio.h>

int Factorial(int n);
int main()
{
	int N, ans=0;

	scanf("%d", &N);

	ans = Factorial(N);

	printf("%d", ans);

	return 0;
}
int Factorial(int n)
{
	if (n == 0)
		return 1;

	else if (n == 1)
		return n;

	else
		return (n*Factorial(n - 1));
}