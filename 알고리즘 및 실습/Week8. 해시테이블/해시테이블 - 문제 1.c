#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int item;
	struct node* next;
}Hnode;

int searchItem(Hnode* hashTable, int key, int N) {
	int m = key % N, cnt = 1;
	Hnode* p = hashTable + m;

	if (p->next == NULL)
		return 0;

	else {
		while (1) {
			p = p->next;
			if (p == NULL)
				return 0;
			else if (p->item == key)
				return cnt;
			else
				cnt++;
		}
	}
}

void insertItem(Hnode* hashTable, int key, int N) {
	int m = key % N;
	Hnode* new_node = (Hnode*)malloc(sizeof(Hnode));
	Hnode* p = hashTable + m;

	new_node->item = key;
	new_node->next = NULL;

	if (p->next == NULL)
		p->next = new_node;

	else {
		new_node->next = p->next;
		p->next = new_node;
	}
}

int removeElement(Hnode* hashTable, int key, int N) {
	int m = key % N, cnt = 1;
	Hnode* p = hashTable + m, * q = p;

	if (p->next == NULL)
		return 0;

	else {
		while (1) {
			p = p->next;
			if (p == NULL)
				return 0;
			if (p->item == key) {
				while (q->next != p) {
					q = q->next;
				}
				q->next = p->next;
				free(p);
				return cnt;
			}
			cnt++;
		}
	}
}

void Print(Hnode* hashTable, int N) {
	Hnode* p;

	for (int i = 0; i < N; i++) {
		p = hashTable + i;
		while (p->next != NULL) {
			printf(" %d", p->next->item);
			p = p->next;
		}
	}

	printf("\n");
}

void initBucketTable(Hnode* hashTable, int N) {
	for (int i = 0; i < N; i++) {
		hashTable[i].item = 0;	//hashTable[i]는 포인터가 아니고 값이라서 ->아니고 .
		hashTable[i].next = NULL;
	}
}

int main() {
	Hnode* hashTable;
	int N, key, num;
	char dem;
	scanf("%d", &N);
	getchar();
	hashTable = (Hnode*)malloc(sizeof(Hnode) * N);
	initBucketTable(hashTable, N);

	while (1) {
		scanf("%c", &dem);
		switch (dem) {
		case 'i':
			scanf("%d", &key);
			insertItem(hashTable, key, N);
			break;

		case 's':
			scanf("%d", &key);
			num = searchItem(hashTable, key, N);
			printf("%d\n", num);
			break;

		case 'd':
			scanf("%d", &key);
			num = removeElement(hashTable, key, N);
			printf("%d\n", num);
			break;

		case 'p':
			Print(hashTable, N);
			break;

		case 'e':
			exit(-1);
			break;
		}
		getchar();
	}

	return 0;
}