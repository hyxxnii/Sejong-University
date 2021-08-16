#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int elem;
	struct node *next;
}NODE;

typedef struct list {
	struct node *first;
	struct node *p;
}Dlist;

void addElem(Dlist *list, int elem)
{
	NODE *new_node;

	new_node = (NODE *)malloc(sizeof(NODE));
	new_node->elem = elem;
	new_node->next = NULL;

	if (list->first == NULL)
	{
		list->first = new_node;
		list->p = list->first;
	}

	else
	{
		list->p->next = new_node;
		list->p = list->p->next;
	}
}

int IsMember(Dlist *list_B, int elem)
{
	NODE *q;

	q = list_B->first;

	while (1)
	{
		if (q == NULL)
			return 0;

		if (elem == q->elem)
			return 1;

		else
			q = q->next;
	}
}

int Subset(Dlist *list_A, Dlist *list_B)
{
	NODE *q;
	int i, num = 0;

	q = list_A->first;
	num = q->elem;

	while (1)
	{
		if (IsMember(list_B, q->elem))
		{
			if (q->next == NULL)
				return 0;

			else
				q = q->next;
		}

		else
		{
			q = list_A->first;

			while (q->next != NULL)
			{
				if (num >= q->elem)
				{
					if (IsMember(list_B, q->elem))
						num = q->next->elem;
					else
						num = q->elem;
				}
				q = q->next;
			}

			return num;
		}
	}
}

int main()
{
	Dlist list_A, list_B;

	int i, A, B, elem, ret = 0;

	list_A.first = NULL;
	list_B.first = NULL;

	scanf("%d", &A);

	if (A != 0)
	{
		for (i = 0; i < A; i++)
		{
			scanf("%d", &elem);
			addElem(&list_A, elem);
		}
	}

	scanf("%d", &B);

	if (B != 0)
	{
		for (i = 0; i < B; i++)
		{
			scanf("%d", &elem);
			addElem(&list_B, elem);
		}
	}

	if (A == 0 || (A == 0 && B == 0))
		printf("0");

	else
	{
		ret = Subset(&list_A, &list_B);
		printf("%d", ret);
	}

	return 0;
}