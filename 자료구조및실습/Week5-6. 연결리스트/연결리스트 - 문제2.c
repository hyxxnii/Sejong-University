#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	int coef;
	int exp;
	struct node *next;
}NODE;

typedef struct list {
	struct node *header;
}Dlist;

NODE *getnode();
void initList(Dlist *list);
void appendTerm(Dlist *list, int c, int e);
Dlist addPoly(Dlist *list1, Dlist *list2);
void print(Dlist *list);
int main()
{
	Dlist list1, list2, res;
	int n = 0, coef = 0, exp = 0;

	initList(&list1);
	initList(&list2);
	initList(&res);

	scanf("%d", &n);
	
	while (n > 0)
	{
		scanf("%d %d", &coef, &exp);
		appendTerm(&list1, coef, exp);
		n--;
	}

	scanf("%d", &n);

	while (n > 0)
	{
		scanf("%d %d", &coef, &exp);
		appendTerm(&list2, coef, exp);
		n--;
	}

	res = addPoly(&list1, &list2);
	print(&res);

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
	list->header = getnode();
	list->header->next = NULL;
}

void appendTerm(Dlist *list, int c, int e)
{
	NODE *new_node, *p;

	p = list->header;
	new_node = getnode();
	new_node->coef = c;
	new_node->exp = e;

	while (p->next != NULL)
	{
		p = p->next;
	}

	p->next = new_node;
	new_node->next = NULL;
}

Dlist addPoly(Dlist *list1, Dlist *list2)
{
	NODE *i, *j;
	Dlist res;
	int sum = 0;

	initList(&res);
	i = list1->header->next;
	j = list2->header->next;

	while ((i != NULL) && (j != NULL))
	{
		if ((i->exp) > (j->exp))
		{
			appendTerm(&res, i->coef, i->exp);
			i = i->next;
		}

		else if ((i->exp) < (j->exp))
		{
			appendTerm(&res, j->coef, j->exp);
			j = j->next;
		}

		else
		{
			sum = i->coef + j->coef;
			if (sum != 0)
				appendTerm(&res, sum, i->exp);
			i = i->next;
			j = j->next;
		}
	}

	while (i != NULL)
	{
		appendTerm(&res, i->coef, i->exp);
		i = i->next;
	}

	while (j != NULL)
	{
		appendTerm(&res, j->coef, j->exp);
		j = j->next;
	}
	
	return res;
}

void print(Dlist *list)
{
	NODE *p;
	
	p = list->header->next;

	while (p != NULL)
	{
		printf(" %d %d", p->coef, p->exp);
		p = p->next;
	}
}