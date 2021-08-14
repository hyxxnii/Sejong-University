#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int elem;
	struct node *next;
}NODE;

typedef struct list {
	struct node *header;
	struct node *p;
}Dlist;

void initLIST(Dlist *list)
{
	list->header = (NODE *)malloc(sizeof(NODE));
	list->header->next = NULL;

}
int isEmpty(Dlist *A)
{
	return A->header->next == NULL;
}

int Get(Dlist *list)
{
	int ret = 0;
	
	if (isEmpty(list))
	{
		printf("List is empty!");
		return -1;
	}

	ret = list->header->next->elem;

	return ret;
}

void removefirst(Dlist *list)
{
	list->header->next = list-> header->next->next;
}

void addLast(Dlist *list, int elem)
{
	NODE *new_node;

	new_node = (NODE *)malloc(sizeof(NODE));
	new_node->elem = elem;
	new_node->next = NULL;

	if (list->header->next == NULL)
	{
		list->header->next = new_node;
		list->p = list->header->next;
	}

	else
	{
		list->p->next = new_node;
		list->p = list->p->next;
	}
}

Dlist Union(Dlist *A, Dlist *B)
{
	Dlist C;

	int a = 0, b = 0;

	initLIST(&C);

	A->p = A->header->next;
	B->p = B->header->next;

	while (!isEmpty(A) && !isEmpty(B))
	{
		a = Get(A);
		b = Get(B);

		if (a < b)
		{
			addLast(&C, a);
			removefirst(A);
		}

		else if (a > b)
		{
			addLast(&C, b);
			removefirst(B);
		}

		else
		{
			addLast(&C, a);
			removefirst(A);
			removefirst(B);
		}
	}

	while (!isEmpty(A))
	{
		a = Get(A);
		addLast(&C, a);
		removefirst(A);
	}

	while (!isEmpty(B))
	{
		b = Get(B);
		addLast(&C, b);
		removefirst(B);
	}

	return C;
}

Dlist Intersect(Dlist *A, Dlist *B)
{
	Dlist C;
	int a = 0, b = 0;

	initLIST(&C);

	while (!isEmpty(A) && !isEmpty(B))
	{
		a = Get(A);
		b = Get(B);

		if (a < b)
			removefirst(A);

		else if (a > b)
			removefirst(B);

		else
		{
			addLast(&C, a);
			removefirst(A);
			removefirst(B);
		}
	}

	while (!isEmpty(A))
	{
		removefirst(A);
	}

	while (!isEmpty(B))
	{
		removefirst(B);
	}

	return C;
}

void Print(Dlist *list)
{
	list->p = list->header->next;

	while (list->p != NULL)
	{
		printf(" %d", list->p->elem);
		list->p = list->p->next;
	}

	printf("\n");
}

int main()
{
	Dlist list_A, list_B, list_union, list_intersect;
	Dlist list_A_copy, list_B_copy;
	int i, A, B, elem;

	initLIST(&list_A);
	initLIST(&list_B);
	initLIST(&list_union);
	initLIST(&list_intersect);
	initLIST(&list_A_copy);
	initLIST(&list_B_copy);

	scanf("%d", &A);

	if (A != 0)
	{
		for (i = 0; i < A; i++)
		{
			scanf("%d", &elem);
			addLast(&list_A, elem);
			addLast(&list_A_copy, elem);
		}
	}

	scanf("%d", &B);

	if (B != 0)
	{
		for (i = 0; i < B; i++)
		{
			scanf("%d", &elem);
			addLast(&list_B, elem);
			addLast(&list_B_copy, elem);
		}
	}
	if (A == 0)
	{
		if (B != 0)
		{
			list_union=Union(&list_A, &list_B);
			Print(&list_union);
			printf(" 0");
		}

		else
		{
			printf(" 0\n");
			printf(" 0");
		}
	}

	else
	{
		list_union=Union(&list_A, &list_B);
		list_intersect=Intersect(&list_A_copy, &list_B_copy);
		Print(&list_union);
		Print(&list_intersect);
	}

	return 0;
}