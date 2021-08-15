#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//과제 HW3,4 2번 -> 스택이용//

typedef struct node {
	char elem;
	struct node *next;
}NODE;

typedef struct stack{
	struct node *top;
}S;

void initStack(S *stack)
{
	stack->top = NULL;
}

void Putnode(NODE *node)
{
	free(node);
}

int isEmpty(S *stack)
{
	return stack->top == NULL;
}

void Push(S *stack, char elem)
{
	NODE *new_node;

	new_node = (NODE *)malloc(sizeof(NODE));
	new_node->elem = elem;

	if (isEmpty(stack))
	{
		new_node->next = NULL;
		stack->top = new_node;
	}
	
	else
	{
		new_node->next = stack->top;
		stack->top = new_node;
	}
}

char Pop(S *stack)
{
	NODE *p;
	char elem = '\0';

	if (isEmpty(stack))
	{
		printf("Empty Stack!");
		return -1;
	}

	p = stack->top;
	elem = p->elem;
	stack->top = stack->top->next;
	Putnode(p);

	return elem;
}

void Checking_Palindrome(S *stack, int len)
{
	S new_stack;
	int n = 0, flag = 0;
	char ch = '\0', check_stack = '\0', check_new_stack = '\0';
	
	initStack(&new_stack);
	n = len / 2;

	while (n > 0)
	{
		ch = Pop(stack);
		Push(&new_stack, ch);
		n--;
	}

	while (!isEmpty(stack))
	{
		check_stack = Pop(stack);
		check_new_stack = Pop(&new_stack);

		if (check_stack >= 'a' && check_stack <= 'z')
		{
			if (check_new_stack >= 'A' && check_new_stack <= 'Z')
				check_new_stack += ('a' - 'A');

			if (check_stack != check_new_stack)
			{
				flag = 1;
				break;
			}
		}

		else
		{
			if (check_new_stack >= 'a' && check_new_stack <= 'z')
				check_new_stack -= ('a' - 'A');

			if (check_stack != check_new_stack)
			{
				flag = 1;
				break;
			}
		}
	}
	
	if (flag == 0)
		printf("True");
	else
		printf("False");
}

int main() 
{
	S stack;
	char str[10001] = "";
	int i, len = 0;
	
	initStack(&stack);
	
	gets(str);
	
	len = strlen(str);			//strlen()은 '\0'포함 안 함

	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] == ' ')
			len--;
	}

	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] != ' ')
			Push(&stack, str[i]);
	}

	Checking_Palindrome(&stack, len);

	return 0;
}
