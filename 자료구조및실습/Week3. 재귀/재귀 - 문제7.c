#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countalp(char str[101], char check, int n);
int main()
{
	char str[101] = "", check='\0';
	int cnt = 0;

	scanf("%s", str);
	getchar();
	scanf("%c", &check);

	cnt = countalp(str, check, 0);

	printf("%d", cnt);

	return 0;
}

int countalp(char str[101], char check, int n)
{
	int cnt = 0;

	if (str[n] == '\0')
		return 0;

	else
	{
		if (str[n] == check)
			cnt++;

		return (cnt + countalp(str, check, n + 1));
	}
}