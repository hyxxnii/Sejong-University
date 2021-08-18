#define _CRT_SECURE_NO_WARNINGS
#define MAX 6;

#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
	int data;
}Vertices;

typedef struct edge {
	int from;
	int target;
	int weight;
}Edges;

typedef struct graph {
	Vertices V[6];
	Edges E[21];
	int AdjacencyMatrix[6][6];
}Graph;

void initGraph(Graph* G) {
	int i, j, size = MAX;

	for (i = 0; i < size; i++)
		G->V[i].data = i + 1;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++)
			G->AdjacencyMatrix[i][j] = -1;
	}

	for (i = 0; i < (size * (size + 1) / 2); i++) {	//edge -1로 초기화
		G->E[i].from = -1;
		G->E[i].target = -1;
		G->E[i].weight = -1;
	}
}

void CreatAdjacencyMatrix(Graph* G, int from, int target, int edge_num) {
	G->AdjacencyMatrix[from][target] = edge_num;
	if (from != target)	//from과 target 같은 경우에 1번만, 다른 경우엔 반대로해서 값 또 넣어줘
		G->AdjacencyMatrix[target][from] = edge_num;
}

void CreatEdge(Graph* G, int from, int target, int weight) {
	int i = 0;

	while (1) {
		if (G->E[i].weight == -1) {
			G->E[i].from = G->V[from].data;
			G->E[i].target = G->V[target].data;
			G->E[i].weight = weight;
			break;
		}
		i++;
	}

	CreatAdjacencyMatrix(G, from, target, i);
}

void SearchGraph(Graph* G, int data) {
	int i = 0, j = 0, size = MAX;

	if (data < 1 || data > size)
		return printf("-1\n");

	for (i = 0; i < size; i++) {
		if (G->AdjacencyMatrix[data - 1][i] != -1) {
			int edge_num = G->AdjacencyMatrix[data - 1][i];
			if (G->E[edge_num].from == data)
				printf(" %d %d", G->E[edge_num].target, G->E[edge_num].weight);
			else
				printf(" %d %d", G->E[edge_num].from, G->E[edge_num].weight);
		}
	}
	printf("\n");
}

void ModifyGraph(Graph* G, int from, int target, int weight) {
	int i = from - 1, j = target - 1, size = MAX;

	if (from < 1 || from > size || target < 1 || target > size)
		return printf("-1\n");

	int edge_num = G->AdjacencyMatrix[i][j];

	if (weight == 0) {
		if (G->AdjacencyMatrix[i][j] != -1) {
			G->E[edge_num].from = -1;
			G->E[edge_num].target = -1;
			G->E[edge_num].weight = -1;
			G->AdjacencyMatrix[i][j] = -1;
			G->AdjacencyMatrix[j][i] = -1;
		}
	}

	else {
		if (G->AdjacencyMatrix[i][j] == -1)	//간선이 존재하지 않는 경우 생성
			CreatEdge(G, i, j, weight);

		else
			G->E[edge_num].weight = weight;
	}
}

int main() {
	Graph G;
	int data, from, target, weight;
	char dem;

	initGraph(&G);

	CreatEdge(&G, 0, 1, 1);
	CreatEdge(&G, 0, 2, 1);
	CreatEdge(&G, 0, 3, 1);
	CreatEdge(&G, 0, 5, 2);
	CreatEdge(&G, 1, 2, 1);
	CreatEdge(&G, 2, 4, 4);
	CreatEdge(&G, 4, 4, 4);
	CreatEdge(&G, 4, 5, 3);

	while (1) {
		scanf("%c", &dem);

		switch (dem) {
		case 'a':
			scanf("%d", &data);
			getchar();
			SearchGraph(&G, data);
			break;

		case 'm':
			scanf("%d %d %d", &from, &target, &weight);
			getchar();
			ModifyGraph(&G, from, target, weight);
			break;

		case 'q':
			exit(-1);
		}
	}

	return 0;
}