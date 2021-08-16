#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int n, int m);
void hanoi(int n, char from, char aux, char to);
int main()
{
	int n, m, num = 0;

	scanf("%d %d", &n, &m);

	num = gcd(n, m);

	printf("%d", num);

	return 0;
}

int gcd(int n, int m)
{
	if (m == 0)
		return n;

	else
		return gcd(m, n%m);
}