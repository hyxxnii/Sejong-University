#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int num;
	struct node *next;
}NODE;

typedef struct list {
	struct node *header;
}Dlist;

NODE *getnode();
void add(Dlist *list, int n);
void initList(Dlist *list);
void visit(Dlist *list);
void delete(NODE *p, NODE *q);
void print(Dlist *list);
int main()
{
	Dlist list, res;
	int N, i, num = 0;

	initList(&list);
	
	scanf("%d", &N);

	for (i = 0; i < N; i++)
	{
		scanf("%d", &num);
		add(&list, num);
	}
	
	visit(&list);
	print(&list);

	return 0;
}

NODE *getnode()
{
	NODE *new_node;

	new_node = (NODE *)malloc(sizeof(NODE));
	
	return new_node;
}

void initList(Dlist *list)
{
	list->header = (NODE *)malloc(sizeof(NODE));
	list->header->next = NULL;
}

void add(Dlist *list, int n)
{
	NODE *new_node, *p;

	p = list->header;
	new_node = getnode();
	new_node->num = n;

	while (p->next != NULL)
	{
		p = p->next;
	}

	p->next = new_node;
	new_node->next = NULL;
}

void visit(Dlist *list)
{
	NODE *p, *q;

	p = list->header->next;
	q = p->next;

	while (1)
	{
		while (1)
		{
			if (q == NULL)
			{
				p = p->next;
				break;
			}

			if ((p->num) == (q->num))
			{
				delete(p, q);
				break;
			}

			q = q->next;
		}
		if (p == NULL)
			break;

		q = p->next;
	}
}

void delete(NODE *p, NODE *q)
{
	p->next = q->next;
	free(q);
}

void print(Dlist *list)
{
	NODE *p;

	p = list->header->next;

	while (p != NULL)
	{
		printf("%d ", p->num);
		p = p->next;
	}
}