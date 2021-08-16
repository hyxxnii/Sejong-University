#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	int elem;
	struct node *prev;
	struct node *next;
}NODE;

typedef struct deque {
	struct node *front;
	struct node *rear;
}DEQUE;

void initQueue(DEQUE *deque);
int isEmpty(DEQUE *deque);
NODE *getnode();
void *putnode(NODE *p);
void add_front(DEQUE *depue, int num);
void add_rear(DEQUE *deque, int num);
int delete_front(DEQUE *deque);
int delete_rear(DEQUE *deque);
void print(DEQUE *deque);

int main()
{
	DEQUE deque;
	int n, num;
	char cal[30] = "";

	initQueue(&deque);

	scanf("%d", &n);
	
	while (n > 0)
	{
		getchar();
		scanf("%s", cal);

		if (strcmp(cal, "AF") == 0)
		{
			scanf("%d", &num);
			add_front(&deque, num);
		}

		else if (strcmp(cal, "AR") == 0)
		{
			scanf("%d", &num);
			add_rear(&deque, num);
		}

		else if (strcmp(cal, "DF") == 0)
		{
			if (isEmpty(&deque))
			{
				printf("underflow");
				return -1;
			}

			delete_front(&deque);
		}
			

		else if (strcmp(cal, "DR") == 0)
		{
			if (isEmpty(&deque))
			{
				printf("underflow");
				return -1;
			}

			delete_rear(&deque);
		}

		else
			print(&deque);

		n--;
	}

	return 0;
}
void initQueue(DEQUE *deque)
{
	deque->front = NULL;
	deque->rear = NULL;
}

int isEmpty(DEQUE *deque)
{
	return (deque->front == NULL);
}

NODE *getnode()
{
	NODE *p;

	p = (NODE *)malloc(sizeof(NODE));

	return p;
}

void *putnode(NODE *p)
{
	free(p);
}

void add_front(DEQUE *deque, int num)
{
	NODE *p;

	p = getnode();
	p->elem = num;
	p->prev = NULL;
	p->next = deque->front;

	if (isEmpty(deque))
	{
		deque->front = p;
		deque->rear = p;
	}
	else
	{
		deque->front->prev = p;
		deque->front = p;
	}
}

void add_rear(DEQUE *deque, int num)
{
	NODE *p;

	p = getnode();
	p->elem = num;
	p->next = NULL;
	p->prev = deque->rear;

	if (isEmpty(deque))
	{
		deque->front = p;
		deque->rear = p;
	}
	else
	{
		deque->rear->next = p;
		deque->rear = p;
	}
}

int delete_front(DEQUE *deque)
{
	NODE *p;

	p = deque->front;
	deque->front = deque->front->next;
	
	if (deque->front == NULL)
		deque->rear = NULL;

	else
		deque->front->prev = NULL;

	putnode(p);
}

int delete_rear(DEQUE *deque)
{
	NODE *p;

	p = deque->rear;
	deque->rear = deque->rear->prev;

	if (deque->rear==NULL)
		deque->front = NULL;

	else
		deque->rear->next = NULL;

	putnode(p);
}

void print(DEQUE *deque)
{
	NODE *p;

	p = deque->front;

	while (p != NULL)
	{
		printf(" %d", p->elem);
		p = p->next;
	}

	printf("\n");
}
