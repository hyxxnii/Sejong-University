#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	int elem;
	struct node *next;
}NODE;

typedef struct stack {
	struct node *t;
}S;

void initStack(S *stack) {
	stack->t = NULL;
}

int isEmpty(S *stack) {
	return stack->t == NULL;
}

void Push(S *stack, int num) {
	NODE *new_node = (NODE *)malloc(sizeof(NODE));
	new_node->elem = num;

	if (isEmpty(stack)) {
		stack->t = new_node;
	}
	else{
		new_node->next = stack->t;
		stack->t = new_node;
	}
}

int Pop(S *stack) {
	int num = 0;
	NODE *p;

	if (isEmpty(stack)) {
		printf("empty stack!");
		return -1;
	}

	num = stack->t->elem;
	p = stack->t;
	stack->t = stack->t->next;
	free(p);

	return num;
}

int cal(int num1, int num2, char op) {
	int ans = 0;

	switch (op) {
	case '+':
		ans = num1 + num2;
		break;

	case '-':
		ans = num1 - num2;
		break;

	case '*':
		ans = num1 * num2;
		break;

	case '/':
		ans = num1 / num2;
		break;
	}

	return ans;
}

int main()
{
	S stack;
	int n, i = 0, num1 = 0, num2 = 0;
	char str[101] = "";

	initStack(&stack);

	scanf("%d", &n);

	while (n > 0) {
		getchar();
		scanf("%s", str);
		i = 0;
		while (str[i] != '\0') {
			if (str[i]>='0' && str[i]<='9')
				Push(&stack, str[i]-'0');
				

			else{
				num1 = Pop(&stack);
				num2 = Pop(&stack);
				Push(&stack, cal(num2, num1, str[i]));
			}

			i++;
		}

		printf("%d\n", Pop(&stack));
		n--;
	}

	return 0;
}