#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int FE(int *arr, int key, int l, int r) {
	int mid;

	while (1) {
		mid = (l + r) / 2;

		if (l > r)
			break;

		if (arr[mid] == key)
			break;

		else if (arr[mid] > key) 
				r = mid - 1;
		
		else
			l = mid + 1;
	}

	return l;
}

int main() {
	int i, N, key;
	int *arr;

	scanf("%d %d", &N, &key);
	arr = (int *)malloc(sizeof(int)*N);

	for (i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	if (arr[N - 1] < key)
		printf(" %d", N);
	else
		printf(" %d", FE(arr, key, 0, N - 1));

	return 0;
}