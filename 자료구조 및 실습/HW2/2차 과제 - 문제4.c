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
void append_n(Dlist *list, int n);
void initList(Dlist *list);
void print(Dlist *list);
Dlist addpoly(Dlist *list1, Dlist *list2);
int main()
{
	Dlist list1, list2, res;
	int N, M;

	initList(&list1);
	initList(&list2);
	initList(&res);

	scanf("%d %d", &N, &M);

	while (1)
	{
		if (N == 0)
			break;
		append_n(&list1, N % 10);
		N = N / 10;
	}

	while (1)
	{
		if (M == 0)
			break;
		append_n(&list2, M % 10);
		M = M / 10;
	}

	res = addpoly(&list1, &list2);
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
	list->header = (NODE *)malloc(sizeof(NODE));
	list->header->next = NULL;
}

void append_n(Dlist *list, int n)
{
	NODE *new_node, *p;

	p = list->header;
	new_node = getnode();
	new_node->num = n;

	while (p->next != NULL)
	{
		p = p->next;
	}

	p->next= new_node;
	new_node->next = NULL;
}

void print(Dlist *list)
{
	NODE *p;
	int i, cnt = 0, res_num = 0;

	p = list->header->next;

	while (p != NULL)
	{
		for (i = 0; i < cnt; i++)
			p->num = (p->num) * 10;

		res_num += p->num;
		cnt++;
		p = p->next;
	}

	printf("%d", res_num);
}

Dlist addpoly(Dlist *list1, Dlist *list2)
{
	Dlist res;
	NODE *i, *j;
	int NUM = 0, flag = 0;

	initList(&res);
	i = list1->header->next;
	j = list2->header->next;

	while ((i != NULL) && (j != NULL))
	{
		NUM = (i->num) + (j->num);

		if (NUM > 10)
		{
			if (flag == 0)
			{
				append_n(&res, NUM % 10);
				flag = 1;
			}
			else
				append_n(&res, NUM % 10 + 1);
		}
		else
		{
			if (flag == 1)
			{
				append_n(&res, NUM + 1);
				flag = 0;
			}
			else
				append_n(&res, NUM);
		}
		i = i->next;         
		j = j->next;
	}

	while (i != NULL)
	{
		if (flag == 1)
		{
			append_n(&res, i->num + 1);
			flag = 0;
		}
		else	
			append_n(&res, i->num);

		i = i->next;
	}

	while (j != NULL)
	{
		if (flag == 1)
		{
			append_n(&res, j->num + 1);
			flag = 0;
		}
		else
			append_n(&res, j->num);

		j = j->next;
	}

	if (flag == 1)
	{
		append_n(&res, 1);
		flag = 0;
	}

	return res;
}