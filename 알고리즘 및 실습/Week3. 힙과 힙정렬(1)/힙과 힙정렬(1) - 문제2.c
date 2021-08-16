#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct heap {
	int h[99];
	int n;
}Heap;


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

void printHeap() {
	for (int i = 1; i <= Heap.n; i++)
		printf(" %d", Heap.h[i]);
	printf("\n");
	return;
}

void rBuildHeap(int idx) {
	if (idx > Heap.n)
		return;

	rBuildHeap(2 * idx);
	rBuildHeap(2 * idx + 1);
	downHeap(idx);
	return;
}

int main() {
	int key;
	char dem;

	Heap.n = 0;

	scanf("%d", &key);
	for (int i = 0; i < key; i++) {
		scanf("%d", &Heap.h[i + 1]);
		Heap.n++;
	}

	rBuildHeap(1);
	printHeap();

	return 0;
}