#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	struct node *prev;
	struct node *next;
	char item;
}NODE;

typedef struct list {
	struct node *header;
	struct node *trailer;
	int n;
}Dlist;

void initList(Dlist *list);
NODE *getnode();
void add(Dlist *list, int position, char item);
void delete(Dlist *list, int position);
char get_entry(Dlist *list, int position);
void print(Dlist *list);
int main()
{
	Dlist list;
	int N, position = 0;
	char cal = '\0', item = '\0', ret='\0';

	initList(&list);

	scanf("%d", &N);

	while (N > 0)
	{
		getchar();
		scanf("%c", &cal);
		
		switch (cal)
		{
		case 'A':
			scanf("%d %c", &position, &item);
			
			if ((position > list.n + 1) || position < 1)
			{
				printf("invalid position\n");
				break;
			}

			add(&list, position, item);
			break;

		case 'D':
			scanf("%d", &position);

			if ((position > list.n) || (position < 1))
			{
				printf("invalid position\n");
				break;
			}

			delete(&list, position);
			break;

		case 'G':
			scanf("%d", &position);
			
			if ((position > list.n) || (position < 1))
			{
				printf("invalid position\n");
				break;
			}

			ret = get_entry(&list, position);
			printf("%c\n", ret);
			break;

		case 'P':
			print(&list);
			break;
		}

		N--;
	}

	return 0;
}

void initList(Dlist *list)
{
	list->header = getnode();
	list->trailer = getnode();
	list->header->next = list->trailer;
	list->trailer->prev = list->header;
	list->n = 0;
}

NODE *getnode()
{
	NODE *new_node;

	new_node = (NODE *)malloc(sizeof(NODE));

	return new_node;
}

void add(Dlist *list, int position, char item)
{
	NODE *new_node, *p;
	int cnt = 1;

	new_node = getnode();
	new_node->item = item;
	p = list->header;

	while (cnt != position)
	{
		p = p->next;
		cnt++;
	}
	
	new_node->prev = p;
	new_node->next = p->next;
	p->next->prev = new_node;
	p->next = new_node;
	list->n++;
}

void delete(Dlist *list, int position)
{
	NODE *p;
	int cnt = 0;

	p = list->header;

	while (cnt != position)
	{
		p = p->next;
		cnt++;
	}

	p->next->prev = p->prev;
	p->prev->next = p->next;
	free(p);
	list->n--;
}

char get_entry(Dlist *list, int position)
{
	NODE *p;
	int cnt = 0;

	p = list->header;

	while (cnt != position)
	{
		p = p->next;
		cnt++;
	}

	return (p->item);
}

void print(Dlist *list)
{
	NODE *p;
	int cnt = 0;

	p = list->header->next;

	while (cnt!=list->n)
	{
		printf("%c", p->item);
		p = p->next;
		cnt++;
	}

	printf("\n");
}