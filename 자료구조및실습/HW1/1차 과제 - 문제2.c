#pragma warning(disable:4996)
#include <stdio.h>

int Fibonacci(int n);
int main()
{
	int N, ans=0;

	scanf("%d", &N);

	ans = Fibonacci(N);

	printf("%d", ans);

	return 0;
}

int Fibonacci(int n)
{
	if (n == 0)
		return 0;

	else if (n == 1)
		return 1;

	else
	{
		return (Fibonacci(n - 1) + Fibonacci(n - 2));
	}

}