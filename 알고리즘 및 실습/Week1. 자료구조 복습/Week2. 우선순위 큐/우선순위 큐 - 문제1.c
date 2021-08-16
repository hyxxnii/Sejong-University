#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void inPlaceSelectionSort(int *arr, int N) {
	int i, j, tmp, max, maxidx;

	//앞 부분을 정렬 상태로 유지
	/*for (i = 0; i < N; i++) {
		int min = arr[i];
		int minidx = i;
		for (j = i + 1; j < N; j++) {
			if (min > arr[j]) {
				min = arr[j];
				minidx = j;
			}
		}
		tmp = arr[minidx];
		arr[minidx] = arr[i];
		arr[i] = tmp;
	}*/

	//뒷부분을 정렬 상태로 유지
	for (i = N - 1; i > 0; i--) {
		max = arr[i];	
		maxidx = i;

		for (j = 0; j < i; j++) {
			if (max < arr[j]) {
				max = arr[j];
				maxidx = j;
			}
		}

		tmp = arr[maxidx];
		arr[maxidx] = arr[i];
		arr[i] = tmp;
	}
}

int main() {
	int i, N, *arr;

	scanf("%d", &N);
	arr = (int *)malloc(sizeof(int)*N);

	for (i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	inPlaceSelectionSort(arr, N);

	for (i = 0; i < N; i++)
		printf(" %d", arr[i]);

	free(arr);

	return 0;
}