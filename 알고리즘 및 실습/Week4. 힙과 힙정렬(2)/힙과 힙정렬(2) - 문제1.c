#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct heap {
	int heap[99];
	int n;
}H;

void printArray() {
	for (int i = 1; i <= H.n; i++)
		printf(" %d", H.heap[i]);
	printf("\n");
	return;

}
void upHeap(int idx) {
	if (idx == 0 || idx == 1)
		return;

	if (H.heap[idx] > H.heap[idx / 2]) {
		int tmp;
		tmp = H.heap[idx];
		H.heap[idx] = H.heap[idx / 2];
		H.heap[idx / 2] = tmp;
		upHeap(idx / 2);
	}
	else
		return;
}

void insertItem(int key) {
	H.n++;
	H.heap[H.n] = key;
	upHeap(H.n);
	return;
}

void downHeap(int idx) {
	if (idx * 2 > H.n || idx * 2 + 1 > H.n)
		return;


	if (H.heap[idx] < H.heap[idx * 2] || H.heap[idx] < H.heap[idx * 2 + 1]) {
		if (H.heap[idx * 2] > H.heap[idx * 2 + 1]) {
			int tmp = H.heap[idx];
			H.heap[idx] = H.heap[idx * 2];
			H.heap[idx * 2] = tmp;
			downHeap(idx * 2);
		}
		else {
			int tmp = H.heap[idx];
			H.heap[idx] = H.heap[idx * 2 + 1];
			H.heap[idx * 2 + 1] = tmp;
			downHeap(idx * 2 + 1);
		}
	}

	else {
		if (H.heap[idx * 2] > H.heap[idx]) {
			int tmp;
			tmp = H.heap[idx];
			H.heap[idx] = H.heap[idx * 2];
			H.heap[idx * 2] = tmp;
			downHeap(idx * 2);
		}
	}
}

void inPlaceHeapSort() {
	int N = H.n;

	for (int i = 1; i <= N; i++) {
		if (H.n == 2) {
			if (H.heap[1] < H.heap[2])
				break;
		}
		int tmp = H.heap[1];
		H.heap[1] = H.heap[H.n];
		H.heap[H.n] = tmp;
		H.n--;
		downHeap(1);
	}
	H.n = N;

	return;
}

int main() {
	H.n = 0;
	int n, key;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &key);
		insertItem(key);
	}
	inPlaceHeapSort();
	printArray();

	return 0;
}