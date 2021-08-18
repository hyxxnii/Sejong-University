#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int rFE(int *arr, int key, int l, int r) {
	int mid = (l + r) / 2;

	if (l > r)
		return mid;

	if (arr[mid] == key)
		return mid;
	else if (arr[mid] > key)
		return rFE(arr, key, l, mid - 1);
	else
		return rFE(arr, key, mid + 1, r);
}

int main() {
	int i, N, key;
	int *arr;

	scanf("%d %d", &N, &key);
	arr = (int *)malloc(sizeof(int)*N);

	for (i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	if (arr[0] > key)
		printf(" %d", -1);
	else
		printf(" %d", rFE(arr, key, 0, N - 1));

	return 0;
}
