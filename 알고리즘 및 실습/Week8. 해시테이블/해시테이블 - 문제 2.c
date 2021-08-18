#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int getNextBucket(int v, int i, int N) {
	return (v + i) % N;
}

int isEmpty(int* hashTable, int b) {
	return hashTable[b] == 0;
}
void searchItem(int* hashTable, int key, int N) {
	int v = key % N, i = 0, b;
	
	while (i < N) {
		b = getNextBucket(v, i, N);
		if (isEmpty(hashTable, b)) {
			printf("-1\n");
			return;
		}
		else if (key == hashTable[b]) {
			printf("%d %d\n", b, key);
			return;
		}
		else
			i++;
	}
	printf("-1\n");
}

void insertItem(int* hashTable, int key, int N) {
	int v = key % N, i = 0, b;

	while (i < N) {
		b = getNextBucket(v, i, N);
		if (hashTable[b] == 0) {
			hashTable[b] = key;
			for (int j = 0; j < i; j++)
				printf("C");
			printf("%d\n", b);
			return;
		}
		else 
			i++;
	}
}

void initBucketTable(int* hashTable, int N) {
	for (int i = 0; i < N; i++)
		hashTable[i] = 0;
}

int main() {
	int* hashTable;
	int N, key, n;
	char dem;
	scanf("%d %d", &N, &n);
	getchar();

	hashTable = (int*)malloc(sizeof(int) * N);
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
			searchItem(hashTable, key, N);
			break;

		case 'e':
			free(hashTable);
			exit(-1);
		}
		getchar();
	}

	return 0;
}