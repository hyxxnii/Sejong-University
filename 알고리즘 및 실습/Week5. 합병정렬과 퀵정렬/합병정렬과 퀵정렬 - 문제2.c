#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int inPlacePartition(int *arr, int l, int r, int pidx) {
	int pivot = arr[pidx], tmp, i = l, j = r - 1;

	tmp = arr[pidx];
	arr[pidx] = arr[r];
	arr[r] = tmp;
	pidx = r;

	while (i <= j) {
		while (arr[i] < pivot) {
			i++;
		}

		while (arr[j] > pivot) {
			j--;
		}

		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}

	tmp = arr[i];
	arr[i] = arr[pidx];
	arr[pidx] = tmp;

	return i;
}

int find_pivot_index(int *arr, int l, int r) {
	int i, random, Rand[3], ridx[3], mid, n;

	n = r - l + 1;

	if (n < 3) {
		if (arr[l] > arr[r])
			mid = l;
		else
			mid = r;

		return mid;
	}//남은 개수가 2개면 둘 중에 큰 값을 중앙값으로

	else {
		for (i = 0; i < 3; i++) {
			if (i == 0)
				ridx[i] = rand() % n + l;

			else {
				while (1) {
					int j = 0;
					random = rand() % n + l;

					while (j != i) {
						if (random == ridx[j])
							break;
						else
							j++;
					}

					if (j == i)
						break;
				}
				ridx[i] = random;
			}
			Rand[i] = arr[ridx[i]];

		}//중복되지않은 random값 3개 찾기
		
		if (Rand[0]<=Rand[1] && Rand[0]>=Rand[2] || Rand[0]<=Rand[2] && Rand[0]>=Rand[1])
			mid = 0;

		if (Rand[1]<=Rand[0] && Rand[1]>=Rand[2] || Rand[1]<=Rand[2] && Rand[1]>=Rand[0])
			mid = 1;

		if (Rand[2]<=Rand[0] && Rand[2]>=Rand[1] || Rand[2]<=Rand[1] && Rand[2]>=Rand[0])
			mid = 2;
		// 중앙값 찾기

		for (i = l; i <= r; i++) {
			if (Rand[mid] == arr[i]) 
				break;
		}
	}
	return i;
}

void inPlaceQuickSort(int *arr, int l, int r) {
	if (l >= r)
		return;

	int pidx = find_pivot_index(arr, l, r);
	int a = inPlacePartition(arr, l, r, pidx);

	inPlaceQuickSort(arr, l, a - 1);
	inPlaceQuickSort(arr, a + 1, r);
}

void printAll(int *arr, int N) {
	for (int i = 0; i < N; i++)
		printf(" %d", arr[i]);
}

int main() {
	int i, N, *arr;

	scanf("%d", &N);
	arr = (int *)malloc(sizeof(int)*N);

	for (i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	inPlaceQuickSort(arr, 0, N - 1);

	printAll(arr, N);

	return 0;
}