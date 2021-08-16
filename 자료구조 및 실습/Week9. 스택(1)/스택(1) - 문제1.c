#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(char *stack, char ch, int N, int *t);
char pop(char *stack, int *t);
void peek(char *stack, int *t);
void duplicate(char *stack, int N, int *t);
void upRotate(char *stack, int N, int n, int *t);
void downRotate(char *stack, int N, int n, int *t);
void print(char *stack, int *t);
int main()
{
	char *stack, str[6] = "", ch = '\0';
	int N, num, t = 0, n;

	scanf("%d", &N);
	scanf("%d", &num);
	stack = (char *)malloc(N * sizeof(char));
	if (stack == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	while (num > 0)
	{
		getchar();
		scanf("%s", str);

		if (strcmp(str, "PUSH") == 0)
		{
			getchar();
			scanf("%c", &ch);
			push(stack, ch, N, &t);
		}

		if (strcmp(str, "POP") == 0)
			pop(stack, &t);

		if (strcmp(str, "PEEK") == 0)
			peek(stack, &t);

		if (strcmp(str, "DUP") == 0)
			duplicate(stack, N, &t);

		if (strcmp(str, "UpR") == 0)
		{
			scanf("%d", &n);
			upRotate(stack, N, n, &t);
		}

		if (strcmp(str, "DownR") == 0)
		{
			scanf("%d", &n);
			downRotate(stack, N, n, &t);
		}

		if (strcmp(str, "PRINT") == 0)
			print(stack, &t);

		num--;
	}

	return 0;
}
void push(char *stack, char ch, int N, int *t)
{
	if (*t == N)
		printf("Stack FULL\n");

	else
	{
		stack[*t] = ch;
		(*t)++;
	}
}
char pop(char *stack, int *t)
{
	char ret = '\0';

	if (*t == 0)
	{
		printf("Stack Empty\n");
		return;
	}

	(*t)--;
	ret = stack[*t];

	return ret;
}
void peek(char *stack, int *t)
{
	printf("%c\n", stack[(*t) - 1]);
}
void duplicate(char *stack, int N, int *t)
{
	char res = '\0';

	res = pop(stack, t);
	push(stack, res, N, t);
	push(stack, res, N, t);
}
void upRotate(char *stack, int N, int n, int *t)
{
	char tmp = '\0';
	int i, q = *t - 1;

	if (n <= *t)
	{
		tmp = stack[q];

		for (i = 0; i < n - 1; i++)
		{
			stack[q] = stack[q - 1];
			q--;
		}

		stack[q] = tmp;
	}

}
void downRotate(char *stack, int N, int n, int *t)
{
	char tmp = '\0';
	int i, q = *t - n;
	if (n <= *t)
	{
		tmp = stack[q];

		for (i = 0; i < n - 1; i++)
		{
			stack[q] = stack[q + 1];
			q++;
		}

		stack[*t - 1] = tmp;
	}
}
void print(char *stack, int *t)
{
	int i;

	for (i = *t - 1; i >= 0; i--)
		printf("%c", stack[i]);

	printf("\n");
}