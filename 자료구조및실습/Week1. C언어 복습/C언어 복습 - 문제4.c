#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>

int main()
{
	char str[101] = "", tmp[101]="";
	char *p;
	int len = 0, i, j, cnt=0;

	scanf("%s", str);
	len = strlen(str);

	p = (char *)malloc((len+1) * sizeof(char));
	if (p == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}
	strcpy(p, str);

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < len; j++)
		{
			tmp[j] = p[(cnt%len)];
			cnt++;
		}
		printf("%s\n", tmp);
		cnt++;
	}

	free(p);

	return 0;
}