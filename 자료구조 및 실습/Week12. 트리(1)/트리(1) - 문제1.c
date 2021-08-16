#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
}NODE;

typedef struct node2 {
	struct node *tree;
	struct node2 *next;
}q_node;

typedef struct q {
	struct node2 *front;
	struct node2 *rear;
}Q;

NODE *getnode(NODE *left, NODE *right, int elem) {
	NODE *node = (NODE *)malloc(sizeof(NODE));

	node->left = left;
	node->right = right;
	node->data = elem;

	return node;
}

void initQueue(Q *q){
	q->front = NULL;
	q->rear = NULL;
}

int isEmpty(Q *q) {
	return q->front == NULL;
}

void enqueue(Q *q, NODE *root) {
	q_node *new_node = (q_node *)malloc(sizeof(q_node));
	new_node->tree = root;
	new_node->next = NULL;

	if (isEmpty(q)) {
		q->front = new_node;
		q->rear = new_node;
	}

	else
	{
		q->rear->next = new_node;
		q->rear = new_node;
	}
}

NODE *dequeue(Q *q) {
	NODE *e;
	q_node *p;

	e = q->front->tree;
	p = q->front;
	q->front = q->front->next;

	if (q->front == NULL)
		q -> rear = NULL;
	
	free(p);

	return e;
 }

void levelOrder(Q *q, NODE *root, int num) {
	NODE *p;
	int cnt = 0;

	enqueue(q, root);

	while (!isEmpty(q)) {
		cnt++;
		p = dequeue(q);

		if (cnt == num) {
			printf("%d ", p->data);

			if (p->left != NULL)
				printf("%d ", p->left->data);

			if (p->right != NULL)
				printf("%d ", p->right->data);

			return -1;
		}

		if (p->left != NULL)
			enqueue(q, p->left);
		if (p->right != NULL)
			enqueue(q, p->right);
	}

	printf("%d", -1);
}

int main()
{
	Q q;
	NODE *F8, *F7, *F6, *F5, *F4, *F3, *F2, *F1, *root, *p;
	int num, cnt = 0;

	initQueue(&q);

	F8 = getnode(NULL, NULL, 80);
	F7 = getnode(NULL, NULL, 130);
	F6 = getnode(F7, F8, 120);
	F5 = getnode(NULL, NULL, 90);
	F4 = getnode(NULL, NULL, 70);
	F3 = getnode(NULL, F6, 50);
	F2 = getnode(F4, F5, 30);
	F1 = getnode(F2, F3, 20);
	root = F1;
	
	scanf("%d", &num);

	levelOrder(&q, root, num);
	
	return 0;
}