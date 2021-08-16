#pragma warning(disable:4996)
#include <stdio.h>

int AddDigits(int n);
int main()
{
	int N, ans=0;

	scanf("%d", &N);

	ans = AddDigits(N);

	printf("%d", ans);

	return 0;
}

int AddDigits(int n)
{
	if (n < 10)
		return n;

	else
		return(n % 10 + (AddDigits(n / 10)));
}