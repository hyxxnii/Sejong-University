#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void isBalanced(char str[1001]);
void push(char stack[1001], int *t, char ch);
char pop(char stack[1001], int *t, char ch);
char counterpart(char ch, char res, int *t);
int main()
{
	char str[1000] = "";

	gets(str);
	isBalanced(str);

	return 0;
}

void isBalanced(char str[1001])
{
	int N, i, len = 0, t = 0, cnt = 0, flag = 0;
	char ch = '\0', stack[1001] = "", res = '\0', tf = '\0';

	len = strlen(str);

	for (i = 0; i < len; i++)
	{
		if (str[i] == '(' || str[i] == '{' || str[i] == '[' || str[i] == ')' || str[i] == '}' || str[i] == ']')
			cnt++;
	}

	for (i = 0; i < len; i++)
	{
		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
			push(stack, &t, str[i]);

		else if (str[i] == ')' || str[i] == '}' || str[i] == ']')
		{
			if (t == 0)
			{
				printf("Wrong_%d", cnt);
				flag++;
				break;
			}

			else
			{
				res = pop(stack, &t, str[i]);
				tf = counterpart(str[i], res, &t);
				if (tf == 'F')
				{
					printf("Wrong_%d", cnt);
					flag++;
					break;
				}
			}
			
		}
	}

	if (flag == 0)
	{
		if(t==0)
			printf("OK_%d", cnt);
		else
			printf("Wrong_%d", cnt);
	}
		
}

void push(char stack[1001], int *t, char ch)
{
	stack[*t] = ch;
	(*t)++;
}

char pop(char stack[1001], int *t, char ch)
{
	if (*t == 0)
	{
		printf("Stack Empty\n");
		return;
	}

	(*t)--;
	return stack[*t];
}

char counterpart(char ch, char res, int *t)
{
	if (ch == ')')
	{
		if (res != '(')
			return 'F';
		else
			return 'T';

	}

	if (ch == '}')
	{
		if (res != '{')
			return 'F';
		else
			return 'T';
	}

	if (ch == ']')
	{
		if (res != '[')
			return 'F';
		else
			return 'T';
	}
}