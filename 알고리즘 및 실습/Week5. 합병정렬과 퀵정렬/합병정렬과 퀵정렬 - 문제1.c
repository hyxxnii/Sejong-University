#define _CRT_SECURE_NO_WARNINGS   
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
}NODE;

typedef struct list {
	struct node *header;
	int n;
}Dlist;

NODE *getNode() {
	NODE *new_node = (NODE *)malloc(sizeof(NODE));
	new_node->next = NULL;

	return new_node;
}

Dlist *initList(Dlist *list) {
	list = (Dlist *)malloc(sizeof(Dlist));
	list->header = getNode();
	list->n = 0;
	
	return list;
}

void printList(Dlist *list) {
	NODE *p = list->header->next;

	while (p != NULL) {
		printf(" %d", p->data);
		p = p->next;
	}
	printf("\n");
}

void addNode(Dlist *list, int data) {
	NODE *p = list->header;

	while (p->next != NULL) {
		p = p->next;
	}

	p->next = getNode();
	p->next->data = data;
	list->n++;
}

Dlist *merge(Dlist *L1, Dlist *L2) {
	Dlist *TL = NULL;
	TL = initList(TL);
	NODE *Tp = NULL, *Lp = L1->header->next, *Rp = L2->header->next;

	while (Lp != NULL && Rp != NULL) {
		if (Lp->data > Rp->data) {
			addNode(TL, Rp->data);
			Rp = Rp->next;
		}

		else {
			addNode(TL, Lp->data);
			Lp = Lp->next;
		}
	}

	while (Lp != NULL) {
		addNode(TL, Lp->data);
		Lp = Lp->next;
	}

	while (Rp != NULL) {
		addNode(TL, Rp->data);
		Rp = Rp->next;
	}

	return TL;
}

Dlist *mgPartition(Dlist *list, int k) {
	NODE *p = list->header;
	Dlist *L2 = NULL;

	L2 = initList(L2);
	int cnt = 0;

	while (cnt != k) {
		p = p->next;
		cnt++;
	}

	L2->header->next = p->next;
	L2->n = list->n - k;
	p->next = NULL;
	list->n = k;

	return L2;
}

Dlist *mergeSort(Dlist *list) {
	Dlist *L2 = NULL;

	L2 = mgPartition(list, (int)((float)list->n / 2 + 0.5));
	
	if (list->n > 1) 
		list = mergeSort(list);

	if (L2->n > 1)
		L2 = mergeSort(L2);

	return merge(list, L2);
}

int main() {
	Dlist *list = NULL;
	int N, i, data;

	list=initList(list);
 	scanf("%d", &N);

	for (i = 0; i < N; i++) {
		scanf("%d", &data);
		addNode(list, data);
	}

	list = mergeSort(list);
	printList(list);

	return 0;
}