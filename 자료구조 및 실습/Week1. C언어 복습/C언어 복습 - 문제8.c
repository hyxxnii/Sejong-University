#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>

typedef struct STUDENT {
	char name[8];
	int kor, eng, math;
	double avg;
}ST;
int main()
{
	ST *st;
	int N, i;

	scanf("%d", &N);
	st = (ST *)malloc(N * sizeof(ST));
	if (st == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	for (i = 0; i < N; i++)
	{
		scanf("%s %d %d %d", st[i].name, &st[i].kor, &st[i].eng, &st[i].math);
		st[i].avg = (double)(st[i].kor + st[i].eng + st[i].math) / 3;
	}

	for (i = 0; i < N; i++)
	{
		printf("%s %.1f ", st[i].name, st[i].avg);
		if (st[i].kor >= 90 || st[i].eng >= 90 || st[i].math >= 90)
			printf("GREAT ");
		if (st[i].kor < 70 || st[i].eng < 70 || st[i].math < 70)
			printf("BAD");
		printf("\n");
	}

	free(st);

	return 0;
}