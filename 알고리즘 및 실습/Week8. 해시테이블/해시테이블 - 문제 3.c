#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int h2(int key, int q) {
	return q - (key % q);
}

int getNextBucket(int v, int i, int N, int q, int key) {
	return (v + i * h2(key, q)) % N;
}

int isEmpty(int* hashTable, int b) {
	return hashTable[b] == 0;
}

void searchItem(int* hashTable, int key, int N, int q) {
	int v = key % N, i = 0, b;

	while (i < N) {
		b = getNextBucket(v, i, N, q, key);
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

void insertItem(int* hashTable, int key, int N, int q) {
	int v = key % N, i = 0, b;

	while (i < N) {
		b = getNextBucket(v, i, N, q, key);
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

void PrintTable(int* hashTable, int N) {
	for (int i = 0; i < N; i++)
		printf(" %d", hashTable[i]);
	printf("\n");
}

void initBucketTable(int* hashTable, int N) {
	for (int i = 0; i < N; i++)
		hashTable[i] = 0;
}

int main() {
	int* hashTable;
	int N, key, n, q;
	char dem;
	scanf("%d %d %d", &N, &n, &q);
	getchar();

	hashTable = (int*)malloc(sizeof(int) * N);
	initBucketTable(hashTable, N);

	while (1) {
		scanf("%c", &dem);
		switch (dem) {
		case 'i':
			scanf("%d", &key);
			insertItem(hashTable, key, N, q);
			break;

		case 's':
			scanf("%d", &key);
			searchItem(hashTable, key, N, q);
			break;

		case 'p':
			PrintTable(hashTable, N);
			break;

		case 'e':
			PrintTable(hashTable, N);
			free(hashTable);
			exit(-1);
		}
		getchar();
	}

	return 0;
}