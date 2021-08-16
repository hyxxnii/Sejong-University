#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int findMax(int num[], int n);
int main()
{
	int N, num[20] = { 0 }, i, max = 0;

	scanf("%d", &N);

	for (i = 0; i< N; i++)
		scanf("%d", &num[i]);
	
	max = findMax(num, N - 1);

	printf("%d", max);

	return 0;
}

int findMax(int num[], int n)
{
	if (n == 0)
		return num[0];

	else
	{
		if (findMax(num, n - 1) > num[n])
			return findMax(num, n - 1);

		else
			return num[n];
	}

}