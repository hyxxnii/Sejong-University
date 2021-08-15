#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
}NODE;

typedef struct q_node {
	struct node *tree_node;
	struct q_node *next;
}Q_NODE;

typedef struct q {
	struct q_node *front;
	struct q_node *rear;
}Q;

NODE *getnode(NODE *left, int data, NODE *right)
{
	NODE *new_node;

	new_node = (NODE *)malloc(sizeof(NODE));
	new_node->left = left;
	new_node->right = right;
	new_node->data = data;

	return new_node;
}

int isEmpty(Q *q)
{
	return q->front == NULL;
}

void Enqueue(Q *q, NODE *node)
{
	Q_NODE *new_node = (Q_NODE *)malloc(sizeof(Q_NODE));

	new_node->tree_node = node;
	new_node->next = NULL;

	if (isEmpty(q))
	{
		q->front = new_node;
		q->rear = new_node;
	}


	else
	{
		q->rear->next = new_node;
		q->rear = new_node;
	}
}

NODE *Dequeue(Q *q)
{
	NODE *p;

	if (isEmpty(q))
		printf("Queue is Empty!");

	else
	{
		p = q->front->tree_node;
		q->front = q->front->next;

		if (q->front == NULL)
			q->rear = NULL;

		return p;
	}
}

void leverOrder(NODE *tree)
{
	Q q;
	NODE *tmp;
	int i;

	q.front = NULL;
	q.rear = NULL;

	Enqueue(&q, tree);

	for (i = 0; i < 15; i++)
	{
		tmp = Dequeue(&q);

		if (tmp == NULL)
		{
			printf("# ");
			tmp = getnode(NULL, 1, NULL);
		}

		else
			printf("%d ", tmp->data);

		Enqueue(&q, tmp->left);
		Enqueue(&q, tmp->right);
	}
}

int main()
{
	NODE *t8 = getnode(NULL, 80, NULL);
	NODE *t7 = getnode(NULL, 130, NULL);
	NODE *t6 = getnode(t7, 120, t8);
	NODE *t5 = getnode(NULL, 90, NULL);
	NODE *t4 = getnode(NULL, 70, NULL);
	NODE *t3 = getnode(NULL, 50, t6);
	NODE *t2 = getnode(t4, 30, t5);
	NODE *t1 = getnode(t2, 20, t3);
	NODE *tree = t1;

	leverOrder(tree);

	return 0;
}