#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//과제 HW3,4 3번 -> 합동큐 이용//

typedef struct node {
	struct node *elem;
	struct node *next;
}NODE;

typedef struct queue {
	struct node *front;
	struct node *rear;
}Q;

typedef struct stack {
	struct queue *q1;
	struct queue *q2;
}S;

void Print(Q *queue)
{
	while (queue->front != NULL)
	{
		printf("%c", queue->front->elem);
		queue->front = queue->front->next;
	}
}

void initQueue(Q *queue)
{
	queue->front = NULL;
	queue->rear = NULL;
}

int isEmpty(Q *queue)
{
	return (queue->front == NULL);
}

void Putnode(NODE *node)
{
	free(node);
}

void Enqueue(Q *queue, char elem)
{
	NODE *new_node;

	new_node = (NODE *)malloc(sizeof(NODE));
	new_node->elem = elem;
	new_node->next = NULL;

	if (isEmpty(queue))
	{
		queue->front = new_node;
		queue->rear = new_node;
	}

	else
	{
		queue->rear->next = new_node;
		queue->rear = new_node;
	}
}

char Dequeue(Q *queue)
{
	NODE *p;
	char elem = '\0';

	if (isEmpty(queue))
	{
		printf("Empty Queue!");
		return -1;
	}

	p = queue->front;
	elem = p->elem;
	queue->front = queue->front->next;

	if (queue->front == NULL)
		queue->rear = NULL;

	Putnode(p);

	return elem;
}

void Push(S *stack, char ch)
{
	Enqueue(stack->q1, ch);
}

char Pop(S *stack)
{
	char ch = '\0', re_ch = '\0';

	while (1)	//Pop하기 위해 p1에 있는 elem를 p2에 Enqueue
	{
		ch = Dequeue(stack->q1);

		if (stack->q1->front == NULL)
			break;

		Enqueue(stack->q2, ch);
	}

	while (stack->q2->front != NULL)	//q2에 있는 elem 다시 q1에 Enqueue해서 q2 비우기
	{
		re_ch = Dequeue(stack->q2);
		Enqueue(stack->q1, re_ch);
	}

	return ch;
}

void Align(S *stack, int len)
{
	S aid_stack;	//보조스택 
	NODE *check_node;
	char tmp_ch = '\0';

	aid_stack.q1 = (Q *)malloc(sizeof(Q));
	aid_stack.q2 = (Q *)malloc(sizeof(Q));

	initQueue(aid_stack.q1);
	initQueue(aid_stack.q2);

	while (!isEmpty(stack->q1))
	{
		tmp_ch = Pop(stack);

		while (!isEmpty(aid_stack.q1) && (aid_stack.q1->rear->elem < tmp_ch))
		{
			Push(stack, Pop(&aid_stack));
		}

		Push(&aid_stack, tmp_ch);
	}

	while (!isEmpty(aid_stack.q1))
	{
		Push(stack, Pop(&aid_stack));
	}

	Print(stack->q1);
}

int main()
{
	S stack;
	char str[1001] = "";
	int i, len = 0;

	stack.q1 = (Q *)malloc(sizeof(Q));
	stack.q2 = (Q *)malloc(sizeof(Q));

	initQueue(stack.q1);
	initQueue(stack.q2);

	scanf("%s", str);
	len = strlen(str);

	for (i = 0; i < len; i++)
		Push(&stack, str[i]);

	Align(&stack, len);

	return 0;
}