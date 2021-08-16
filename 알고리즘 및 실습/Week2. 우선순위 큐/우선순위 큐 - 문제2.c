#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void inPlaceInsertionSort(int *arr, int N) {
	int i, j, save, tmp;

	for (i = 1; i < N; i++) {
		save = i;
		j = i - 1;
		while(j >= 0 && arr[save] < arr[j]) {
			tmp = arr[save];
			arr[save] = arr[j];
			arr[j] = tmp;
			j--;
			save--;
		}
	}
}

int main() {
	int i, N, *arr;

	scanf("%d", &N);
	arr = (int *)malloc(sizeof(int)*N);

	for (i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	inPlaceInsertionSort(arr, N);

	for (i = 0; i < N; i++)
		printf(" %d", arr[i]);

	free(arr);

	return 0;
}