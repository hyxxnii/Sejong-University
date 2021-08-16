#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	struct node *prev;
	struct node *next;
	int elem;
}NODE;

typedef struct node2 {
	NODE *header;
	NODE *trailer;
	int n;
}Dlist;

void InitList(Dlist *list) {
	list->header = (NODE *)malloc(sizeof(NODE));
	list->trailer = (NODE *)malloc(sizeof(NODE));

	list->header->next = list->trailer;
	list->trailer->prev = list->header;
	list->n = 0;
}

void AddList(Dlist *list, int num, char ch) {
	NODE *new_node = (NODE *)malloc(sizeof(NODE));
	NODE *p = list->header;
	int cnt = 0;

	new_node->elem = ch;

	while (cnt != (num - 1)) {
		cnt++;
		p = p->next;
	}

	new_node->prev = p;
	new_node->next = p->next;
	(p->next)->prev = new_node;
	p->next = new_node;

	list->n++;
}

void DelList(Dlist *list, int num) {
	NODE *p = list->header;
	int cnt = 0;

	while (cnt != num) {
		cnt++;
		p = p->next;
	}

	(p->prev)->next = p->next;
	(p->next)->prev = p->prev;
	
	free(p);
	list->n--;
}

char Get_EntryList(Dlist *list, int num) {
	NODE *p = list->header;
	int cnt = 0;

	while (cnt != num) {
		cnt++;
		p = p->next;
	}
	
	return p->elem;
}

void PrintList(Dlist *list) {
	NODE *p = list->header;
	int cnt = 0;

	while (cnt != list->n) {
		printf("%c", p->next->elem);
		cnt++;
		p = p->next;
	}

	printf("\n");
}

int main() {
	Dlist list;
	int num, N;
	char cal, ch, ret;

	InitList(&list);
	scanf("%d", &num);
	getchar();

	while (num > 0) {
		scanf("%c", &cal);
		getchar();

		switch (cal) {
		case 'A':
			scanf("%d %c", &N, &ch);
			getchar();

			if (N < 1 || N > list.n + 1) {
				printf("invalid position\n");
				break;
			}

			AddList(&list, N, ch);
			break;

		case 'D':
			scanf("%d", &N);
			getchar();

			if (N < 1 || N > list.n) {
				printf("invalid position\n");
				break;
			}

			DelList(&list, N);
			break;

		case 'G':
			scanf("%d", &N);
			getchar();

			if (N < 1 || N > list.n) {
				printf("invalid position\n");
				break;
			}

			ret = Get_EntryList(&list, N);
			printf("%c\n", ret);
			break;

		case 'P':
			PrintList(&list);
			break;
		}

		num--;
	}

	return 0;
}