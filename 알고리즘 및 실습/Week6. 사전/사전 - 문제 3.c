#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int FE(int l, int r, char *info) {
	char ch;
	int i = 0;
	
	while (1) {
		int mid = (l + r) / 2;

		if (l == r)
			return mid;
		
		if (info[i] == 'Y')
			l = mid + 1;
		else
			r = mid;

		i++;
	}
}

int main() {
	int A, B, num;
	char *info;

	scanf("%d %d %d", &A, &B, &num);
	info = (char *)malloc(sizeof(char)*num);
	getchar();
	
	scanf("%s", info);
	printf("%d", FE(A, B, info));

	return 0;
}