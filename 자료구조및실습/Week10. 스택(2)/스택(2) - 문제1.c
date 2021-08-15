#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(char stack[101], char op, int N, int *t);
char pop(char stack[101], int *t);
void convert(char str[101]);
int Rank(char op);
int Rank_single(char op);
int main()
{
	int N;
	char str[101] = "";

	scanf("%d", &N);

	while (N > 0)
	{
		getchar();
		scanf("%s", str);
		convert(str);
		N--;
	}

	return 0;
}
void push(char stack[101], char op, int N, int *t)
{
	if ((*t + 1) == N)
		printf("Stack FULL\n");

	else
	{
		stack[*t + 1] = op;
		(*t)++;
	}
}
char pop(char stack[101], int *t)
{
	int ret = 0;

	if (*t == -1)
	{
		printf("Stack Empty\n");
		return;
	}

	ret = stack[*t];
	(*t)--;

	return ret;
}
void convert(char str[101])
{
	int i = 0, len = 0, t = -1;
	char str_op[101] = "";

	len = strlen(str);

	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			printf("%c", str[i]);

		else if ()
		{

		}
	
		else
		{
			while ((t != -1) && (Rank(str[i]) <= Rank(t)))
			{

			}
		}

		i++;
	}
}

int Rank(char op)
{
	switch (op)
	{
	case '@':
	case '#':
	case '$':
		return 1;

	case '*':
	case '/':
		return 2;

	case '+':
	case '-':
		return 3;

	case '>':
	case '<':
		return 4;

	case '&':
		return 5;

	case '|':
		return 6;
	}
}