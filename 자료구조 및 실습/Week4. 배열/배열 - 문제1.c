#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_arr(int num[], int x, int y);
int main()
{
	int N, num[100] = { 0 }, i, info = 0, x = 0, y = 0;

	scanf("%d", &N);
	
	for (i = 0; i < N; i++)
		scanf("%d", &num[i]);

	scanf("%d", &info);

	while (info > 0)
	{
		scanf("%d %d", &x, &y);
		reverse_arr(num, x, y);
		info--;
	}

	for (i = 0; i < N; i++)
		printf(" %d", num[i]);

	return 0;
}

void reverse_arr(int num[], int x, int y)
{
	int i, tmp = 0;

	for (i = 0; i <= (y - x) / 2; i++)
	{
		tmp = *(num + x + i);
		*(num + x + i) = *(num + y - i);
		*(num + y - i) = tmp;
	}
}