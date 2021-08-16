#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>

typedef struct TIME{
	int time[3], num;
}T;

int main()
{
	T clock[2] = { {0}, 0 };
	int result[3] = { 0 }, num=0;

	scanf("%d %d %d", &clock[0].time[0], &clock[0].time[1], &clock[0].time[2]);
	scanf("%d %d %d", &clock[1].time[0], &clock[1].time[1], &clock[1].time[2]);

	clock[0].num = clock[0].time[0] * 3600 + clock[0].time[1] * 60 + clock[0].time[2];
	clock[1].num = clock[1].time[0] * 3600 + clock[1].time[1] * 60 + clock[1].time[2];
	num = clock[1].num - clock[0].num;

	result[0] = num / 3600;
	num %= 3600;
	result[1] = num / 60;
	num %= 60;
	result[2] = num;
	
	printf("%d %d %d", result[0], result[1], result[2]);

	return 0;
}