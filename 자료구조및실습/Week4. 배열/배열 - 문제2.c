
#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void loc_change(int *p, int fisrt_num, int tmp);
int main()
{
	int N, i, len = 0, first_num = 0, tmp = 0;
	int *p;

	scanf("%d", &N);

	p = (int *)malloc(N * sizeof(int));
	if (p == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	for (i = 0; i < N; i++)
		scanf("%d", &p[i]);

	scanf("%d", &len);

	scanf("%d", &first_num);

	while (1)
	{
		scanf("%d", &tmp);
		if (tmp == first_num)
			break;
		loc_change(p, first_num, tmp);
	}

	for (i = 0; i < N; i++)
		printf(" %d", p[i]);

	free(p);

	return 0;
}
void loc_change(int *p, int first_num, int tmp)
{
	int tmp2 = 0;

	tmp2 = *(p + first_num);
	*(p + first_num) = *(p + tmp);
	*(p + tmp) = tmp2;
}