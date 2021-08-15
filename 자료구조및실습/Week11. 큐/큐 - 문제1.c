#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void initQueue(int *Q, int q);
void Enqueue(int *Q, int num, int *r, int *f, int q);
void Dequeue(int *Q, int *r, int *f, int q);
void Print(int *Q, int q);
int isEmpty(int r, int f, int q);
int main()
{
	int q, n, num, f = 0, r = 0;
	int *Q;
	char cal = '\0';

	scanf("%d", &q);
	Q = (int *)malloc(q * sizeof(int));
	if (Q == NULL)
	{
		printf("Not enough memory!");
		return -1;
	}

	scanf("%d", &n);

	initQueue(Q, q);

	while (n > 0)
	{
		getchar();
		scanf("%c", &cal);
		switch (cal)
		{
		case 'I':
			scanf("%d", &num);
			if (isFull(r, f, q))
			{
				printf("overflow");
				Print(Q, q);
				return -1;
			}
			Enqueue(Q, num, &r, &f, q);
			break;

		case 'D':
			if (isEmpty(r, f, q))
			{
				printf("underflow");
				return -1;
			}
			Dequeue(Q, &r, &f, q);
			break;

		case 'P':
			Print(Q, q);
			break;
		}
		n--;
	}

	free(Q);

	return 0;
}
int isEmpty(int r, int f, int q)
{
	return (r%q == f);
}

int isFull(int r, int f, int q)
{
	return ((r + 1) % q == f);
}

void initQueue(int *Q, int q)
{
	int i = 0;

	while (i != q)
	{
		Q[i] = 0;
		i++;
	}
}

void Enqueue(int *Q, int num ,int *r, int *f, int q)
{
	*r = (*r + 1) % q;
	Q[*r] = num;
}

void Dequeue(int *Q, int *r, int *f, int q)
{
	*f = (*f + 1) % q;
	Q[*f] = 0;
}

void Print(int *Q, int q)
{
	int i = 0;

	while (i != q)
	{
		printf(" %d", Q[i]);
		i++;
	}
	printf("\n");
}