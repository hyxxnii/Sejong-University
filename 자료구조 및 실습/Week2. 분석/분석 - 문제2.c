#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mostOnes(int *A[], int n);
int main()
{
	int **bitmatrix;
	int n, i, j, maxrow = 0;

	scanf("%d", &n);

	bitmatrix = (int **)malloc(n * sizeof(int *));
	if (bitmatrix == NULL)
	{
		printf("Not enought memory!");
		return -1;
	}
	
	for (i = 0; i < n; i++)
	{
		bitmatrix[i] = (int *)malloc(n * sizeof(int));
		if (bitmatrix[i] == NULL)
		{
			printf("Not enought memory!");
			return -1;
		}

		for (j = 0; j < n; j++)
			scanf("%d", &bitmatrix[i][j]); 
	}

	maxrow = mostOnes(bitmatrix, n);

	printf("%d", maxrow);

	return 0;
}

int mostOnes(int *A[], int n)
{
	int i = 0, j = 0, row = 0;

	while ((i < n) && (j < n))
	{
		if (A[i][j] == 0)
			i++;

		else
		{
			row = i;
			j++;
		}
	}

	return row;
}