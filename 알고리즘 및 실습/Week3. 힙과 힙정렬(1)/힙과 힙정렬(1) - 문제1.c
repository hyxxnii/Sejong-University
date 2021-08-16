#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct heap {
	int h[99];
	int n;
}Heap;

void upHeap(int idx) {
	if (idx == 0 || idx == 1)
		return;
	
	if (Heap.h[idx] > Heap.h[idx / 2]) {
		int tmp;
		tmp = Heap.h[idx];
		Heap.h[idx] = Heap.h[idx / 2];
		Heap.h[idx / 2] = tmp;
		upHeap(idx / 2);
	}

	else
		return;
}

void downHeap(int idx) {
	if (idx * 2 > Heap.n)
		return;

	if (Heap.h[idx] < Heap.h[idx * 2] || Heap.h[idx] < Heap.h[idx * 2 + 1]) {
		if (Heap.h[idx * 2] > Heap.h[idx * 2 + 1]) {
			int tmp;
			tmp = Heap.h[idx];
			Heap.h[idx] = Heap.h[idx * 2];
			Heap.h[idx * 2] = tmp;
			downHeap(idx * 2);
		}

		else {
			int tmp;
			tmp = Heap.h[idx];
			Heap.h[idx] = Heap.h[idx * 2 + 1];
			Heap.h[idx * 2 + 1] = tmp;
			downHeap(idx * 2 + 1);
		}
	}

	else
		return;
}

void insertItem(int key) {
	Heap.n++;
	Heap.h[Heap.n] = key;
	upHeap(Heap.n);
	return;
}

int removeMax() {
	int key = Heap.h[1];
	Heap.h[1] = Heap.h[Heap.n];
	Heap.n--;
	downHeap(1);
	return key;
}

void printHeap() {
	for(int i=1;i<=Heap.n;i++)
		printf(" %d", Heap.h[i]);
	printf("\n");
	return;
}

int main() {
	int key;
	char dem;

	Heap.n = 0;

	while (1) {
		scanf("%c", &dem);

		switch (dem) {
		case 'i':
			getchar();
			scanf("%d", &key);
			insertItem(key);
			printf("0\n");
			break;

		case 'd':
			printf("%d\n",removeMax());
			break;

		case 'p':
			printHeap();
			break;

		case 'q':
			exit(1);
		}
		getchar();
	}

	return 0;
}