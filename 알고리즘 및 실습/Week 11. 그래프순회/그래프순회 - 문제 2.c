#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct vertex {
	int data;
	int visited;
}Vertices;

typedef struct edge {
	int from;
	int target;
	int visited;
}Edges;

typedef struct list {
	Vertices vertex;
	struct list* next;
}List;

typedef struct Dlist {
	List* list;	//L0, L1, L2 만들때마다 얘의 next로 연결?
	struct Dlist* next;
}DList;

typedef struct graph {
	Vertices V[100];
	Edges E[1000];
	int AdjacencyMatrix[100][100];
}Graph;

void initGraph(Graph* G, int n, int m) {
	int i, j;

	for (i = 0; i < n; i++) {
		G->V[i].data = i + 1;
		G->V[i].visited = 0;	//0이면 방문x, 1이면 방문o
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			G->AdjacencyMatrix[i][j] = -1;
	}

	for (i = 0; i < m; i++) {
		G->E[i].from = -1;
		G->E[i].target = -1;
		G->E[i].visited = 0;	//0이면 방문x, 1이면 방문o
	}
}

void CreatAdjacenyMatrix(Graph* G, int from, int target, int edge_num) {
	G->AdjacencyMatrix[from - 1][target - 1] = edge_num;
	if (from != target)
		G->AdjacencyMatrix[target - 1][from - 1] = edge_num;
}

void CreatEdge(Graph* G, int from, int target) {
	int i = 0;

	while (1) {
		if (G->E[i].from == -1) {
			G->E[i].from = from;
			G->E[i].target = target;
			break;
		}
		i++;
	}
	CreatAdjacenyMatrix(G, from, target, i);
}

void BFS(Graph* G, DList *DL, int s, int n) {
	int i = 0;
	DList* pp;
	List* p , * new_l = (List*)malloc(sizeof(List));

	G->V[s - 1].visited = 1;	//방문 표시 해주기
	printf("%d\n", G->V[s - 1]);

	new_l->vertex = G->V[s - 1];
	new_l->next = NULL;

	DL->list = new_l;	//L0에 첫 번째 시작 정점 넣기
	p = DL->list;
	pp = DL;
	while (pp->list != NULL) {
		DList* new_DL = (DList*)malloc(sizeof(DList));
		new_DL->list = NULL;
		new_DL->next = NULL;
		/*while (pp->next != NULL) {
				pp = pp->next;
			}*/
		List* q = NULL;
		p = pp->list;
		while (p != NULL) {
			//p는 Li에 있는 리스트들을 도는 포인터
			int j = 0;
			while (j != n) {
				List* new_L = (List*)malloc(sizeof(List));
				new_L->next = NULL;

				int edge_num = G->AdjacencyMatrix[p->vertex.data - 1][j];

				if (edge_num != -1) {
					if (G->E[edge_num].visited == 0){	//방문하지않은 간선이면
						if (G->E[edge_num].from == p->vertex.data) {
							if (G->V[G->E[edge_num].target - 1].visited == 0) {	//반대 정점이 방문하지않은 정점이면
								G->V[G->E[edge_num].target - 1].visited = 1;	//방문표시
								printf("%d\n", G->V[G->E[edge_num].target - 1 ]);
								new_L->vertex = G->V[G->E[edge_num].target - 1];

								if (new_DL->list == NULL) {
									new_DL->list = new_L;
									q = new_DL->list;
								}

								else {
									q->next = new_L;
									q = q->next;
								}
							}
						}
						else {
							if (G->V[G->E[edge_num].from - 1].visited == 0) {
								G->V[G->E[edge_num].from - 1].visited = 1;
								printf("%d\n", G->V[G->E[edge_num].from - 1]);
								new_L->vertex = G->V[G->E[edge_num].from - 1];
								
								if (new_DL->list == NULL) {
									new_DL->list = new_L;
									q = new_DL->list;
								}

								else {
									q->next = new_L;
									q = q->next;
								}
							}
						}

					}
				}
				j++;
			}
			p = p->next;
		}
		pp->next = new_DL;	//L0, L1, L2 - - - 생성
		pp = pp->next;
	}
}

int main() {
	Graph G;
	DList DL;

	DL.list = NULL;
	DL.next = NULL;

	int n, m, s, a, b;
	
	scanf("%d %d %d", &n, &m, &s);

	initGraph(&G, n, m);

	while (m > 0) {
		scanf("%d %d", &a, &b);
		CreatEdge(&G, a, b);
		m--;
	}

	BFS(&G, &DL, s, n);

	return 0;
}