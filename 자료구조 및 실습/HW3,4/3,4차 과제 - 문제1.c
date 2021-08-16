#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Push(int *p, int num, int *t);
int Pop(int *p, int *t);
int Malloc_Stack(int len);
void Trans_num(char stack[], int *p, int flag, int *t);
void Sub_stack(int p1[], int p2[], int p3[], int flag_1, int flag_2, int *t1, int *t2, int *t3);
void Add_stack(int p1[], int p2[], int p3[], int flag_1, int flag_2, int *t1, int *t2, int *t3);
char Print(int p3[], int *t3, int flag_3);
int main()
{
	char stack_1[500000], stack_2[500000];
	int *p_stack1, *p_stack2, *p_stack3;
	int len1 = 0, len2 = 0, flag_stack1 = 0, flag_stack2 = 0, t1 = -1, t2 = -1, t3 = -1;

	scanf("%s", stack_1);
	getchar();
	scanf("%s", stack_2);

	len1 = strlen(stack_1);
	len2 = strlen(stack_2);

	if (stack_1[0] == '-')
	{
		flag_stack1 = 1;
		len1--;
	}

	if (stack_2[0] == '-')
	{
		flag_stack2 = 1;
		len2--;
	}

	p_stack1 = Malloc_Stack(len1 + 1);	//덧셈할때 자리수 하나 더 넘어가는 경우때매 크기 +1해주기
	p_stack2 = Malloc_Stack(len2 + 1);

	if (len1 > len2)
		p_stack3 = Malloc_Stack(len1 + 1);
	else if (len1 < len2)
		p_stack3 = Malloc_Stack(len2 + 1);
	else
		p_stack3 = Malloc_Stack(len1 + 1);

	Trans_num(stack_1, p_stack1, flag_stack1, &t1);
	Trans_num(stack_2, p_stack2, flag_stack2, &t2);

	if((flag_stack1==0) && (flag_stack2==0) || (flag_stack1==1) && (flag_stack2==1))	//둘다 양수이거나 음수
		Add_stack(p_stack1, p_stack2, p_stack3, flag_stack1, flag_stack2, &t1, &t2, &t3);

	if((flag_stack1==0) && (flag_stack2==1) || (flag_stack1==1) && (flag_stack2==0))	//둘 중에 하나는 양수, 하나는 음수
		Sub_stack(p_stack1, p_stack2, p_stack3, flag_stack1, flag_stack2, &t1, &t2, &t3);

	free(p_stack1);
	free(p_stack2);
	free(p_stack3);

	return 0;
}

int Malloc_Stack(int len)
{
	int *p;

	p = (int *)malloc(len * sizeof(int));
	if (p == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	return p;
}

void Push(int *p, int num, int *t)
{
	(*t)++;
	p[*t] = num;
}

int Pop(int *p, int *t)
{
	int ret = 0;

	if ((*t) == -1)
	{
		printf("Stack Empty!\n");
		return -1;
	}

	ret = p[*t];
	(*t)--;

	return ret;
}

void Trans_num(char stack[], int *p, int flag, int *t)
{
	int i;

	if (flag == 0)		//양수 
	{
		i = 0;

		while (stack[i] != '\0')
		{
			Push(p, stack[i] - '0', t);
			i++;
		}
	}

	else		//음수
	{
		i = 1;

		while (stack[i] != '\0')
		{
			Push(p, stack[i] - '0', t);
			i++;
		}
	}
}

void Add_stack(int p1[], int p2[], int p3[], int flag_1, int flag_2, int *t1, int *t2, int *t3)
{
	int num1 = 0, num2 = 0, num3 = 0, tmp = 0, ans = 0, flag_3 = 0;

	while ((*t1) >= 0 && (*t2) >= 0)
	{
		num1 = Pop(p1, t1);
		num2 = Pop(p2, t2);
		num3 = num1 + num2 + tmp;

		if (num3 < 10)
		{
			Push(p3, num3, t3);
			tmp = 0;
		}

		else
		{
			ans = num3 % 10;
			Push(p3, ans, t3);
			tmp = 1;
		}
	}

	while ((*t1) >= 0)
	{
		num1 = Pop(p1, t1) + tmp;
		Push(p3, num1, t3);
		tmp = 0;
	}

	while ((*t2) >= 0)
	{
		num2 = Pop(p2, t2) + tmp;
		Push(p3, num2, t3);
		tmp = 0;
	}

	if (tmp == 1)
		Push(p3, 1, t3);

	if (flag_1 == 1 && flag_2 == 1)		//둘다 음수이면 flag_3=1 -> '-'표시
		flag_3 = 1;

	Print(p3, t3, flag_3);
}

void Sub_stack(int p1[], int p2[], int p3[], int flag_1, int flag_2, int *t1, int *t2, int *t3)
{
	int num1 = 0, num2 = 0, num3 = 0, tmp = 0, flag_3 = 0, i, compare_num1 = 0, compare_num2 = 0;

	for (i = 0; i <= (*t1); i++)
		compare_num1 = compare_num1 * 10 + p1[i];

	for (i = 0; i <= (*t2); i++)
		compare_num2 = compare_num2 * 10 + p2[i];

	while ((*t1) >= 0 && (*t2) >= 0)
	{
		num1 = Pop(p1, t1);
		num2 = Pop(p2, t2);

		if (compare_num1 >= compare_num2)		//p1 - p2
			num3 = num1 - num2 - tmp;

		else		//p2 - p1
			num3 = num2 - num1 - tmp;

		if (num3 < 0)
		{
			num3 += 10;
			tmp = 1;
		}

		else
			tmp = 0;

		Push(p3, num3, t3);
	}

	if (compare_num1 > compare_num2)
	{
		while ((*t1) >= 0)
		{
			num1 = Pop(p1, t1) - tmp;
			if (num1 < 0)
			{
				num1 += 10;
				tmp = 1;
			}
			else
				tmp = 0;

			if ((*t1) == -1 && num1 <= 0)
				continue;
			else
				Push(p3, num1, t3);
		}
	}

	else
	{
		while ((*t2) >= 0)
		{
			num2 = Pop(p2, t2) - tmp;
			if (num2 < 0)
			{
				num2 += 10;
				tmp = 1;
			}
			else
				tmp = 0;

			if ((*t2) == -1 && num2 <= 0)
				continue;
			else
				Push(p3, num2, t3);
		}
	}

	if ((compare_num1 > compare_num2 && flag_1 == 1) || (compare_num1 < compare_num2 && flag_2 == 1))
		flag_3 = 1;

	Print(p3, t3, flag_3);
}

char Print(int p3[], int *t3, int flag_3)
{
	char *stack_3;
	int i = 0, j = 0;

	stack_3 = (char *)malloc(((*t3) + 1) * sizeof(char));

	if (stack_3 == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	if (p3[*t3] == 0)
	{
		i = *t3;
		while (p3[i] == 0)
		{
			if ((*t3) == 0)
				break;

			(*t3)--;
			i--;
		}
	}

	for (i = *t3; i >= 0; i--)
	{
		stack_3[j] = p3[i] + '0';
		j++;
	}

	stack_3[(*t3) + 1] = '\0';

	if (flag_3 == 1)
		printf("-%s", stack_3);
	else
		printf("%s", stack_3);
}