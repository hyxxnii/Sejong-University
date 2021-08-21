#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//<1. 위상순서 찾기>
//1) G가 방향 비싸이클 그래프(directed acyclic graph: DAG)면 위상순서(topological order)를 구해 인쇄.
//2) G에 방향 싸이클(directed cycle)이 존재하면 위상순서를 구할 수 없으므로 0을 인쇄.
//위상순서를 구하는 과정에서 방향싸이클의 존재 여부를 확인할 수 있어야함
//부착리스트 구축 시, 새로 입력되는 간선에 대한 노드를 리스트의 맨 앞에 삽입
//최초로 진입간선의 개수가 0인 정점을 찾을 때, 정점번호 순서대로 조사
 
int n, m;	//n:정점 수(n<100), m:간선 수(m<1000)
int* topOrder;	//topOrder[0] = 1(G가 DAG인 경우), 0(G가 non-DAG인 경우)
				//topOrder[1:n] = 정점들의 위상순서 (G가 DAG인 경우에 유효)
int* in;	//정점 i의 진입차수
char* topSort;
struct node* Q;

typedef struct node {
	int v;	//정점들의 대기열
}Queue;

typedef struct edge {
	int origin;
	int destination;
}Edge;

typedef struct icd {
	int edgeid;
	struct icd* next;
}Incidence;

typedef struct vertex {
	char vname;
	Incidence* inEdges;
	Incidence* outEdges;
	int inDegree;
}Vertex;

typedef struct graph {
	Vertex* vertices;
	int vsize;	//정점 수
	Edge* edges;
	int esize;	//간선 수
}Graph;

Incidence* get_incidence(int edgeid, Incidence* next) {
	Incidence* new_node = (Incidence*)malloc(sizeof(Incidence));
	
	new_node->edgeid = edgeid;
	new_node->next = next;

	return new_node;
}

void initializeGraph(Graph *G) {
	G->vertices = (Vertex*)malloc(sizeof(Vertex) * 99);
	G->edges = (Edge*)malloc(sizeof(Edge) * 999);
}

Incidence* get_Incidence(int edgeid, Incidence* next) {
	Incidence* new_node = (Incidence*)malloc(sizeof(Incidence));
	
	new_node->edgeid = edgeid;
	new_node->next = next;

	return new_node;
}

void insertVertex(Graph* G, char vname, int i) {
	G->vertices[i].vname = vname;	//정점 i의 이름 저장
	G->vertices[i].inEdges = get_Incidence(-1, NULL);	//진입부착간선리스트 초기화
	G->vertices[i].outEdges = get_Incidence(-1, NULL);	//진출부착간선리스트 초기화
	G->vertices[i].inDegree = 0;	//정점 i의 진입차수 초기화
}

void addFirst(Incidence* H, int i) {
	Incidence* new_node = (Incidence*)malloc(sizeof(Incidence));
	
	//H를 헤더로 하는 부착연결리스트
	new_node->edgeid = i;	//new_node의 원소로 i를 저장
	new_node->next = H->next;	//기존 연결리스트를 new_node 뒤에 연결 (새로 추가되는 new_node가 맨 앞에 추가되게끔)
	H->next = new_node;	//다시 new_node를 H의 첫 노드로 설정 (H를 헤더로 하는 연결리스트)
}

int index(Graph *G, char vname) {
	for (int i = 0; i < n; i++) {
		if (G->vertices[i].vname == vname)
			return i;
	}
}

void insertDirectedEdge(Graph* G, char fname, char tname, int i) {
	int f, t; //f: fname 정점의 배열 인덱스, t: tname 정점의 배열 인덱스

	f = index(G, fname);
	t = index(G, tname);

	G->edges[i].origin = f; 	//간선 i의 시점을 f로 저장
	G->edges[i].destination = t;	//간선 i의 종점을 t로 저장
	addFirst(G->vertices[f].outEdges, i);	//정점 f의 진출부착간선리스트에 i 삽입, f->t 방향이니깐
  	addFirst(G->vertices[t].inEdges, i);		//정점 t의 진입부착간선리스트에 i 삽입
	G->vertices[t].inDegree++;	//정점 t의 진입차수 갱신 (f에서 들어오니까)

}

void BuildGraph(Graph *G) {
	char vname, f, t;

	initializeGraph(G);
	
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		getchar();
		scanf("%c", &vname);
		insertVertex(G, vname, i);
	}

	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		getchar();
		scanf("%c %c", &f, &t);
		insertDirectedEdge(G, f, t, i);
	}
}

int isEmpty(int f, int r) {
	return ((r+1) % n == f);
}

void enqueue(int v, int *f, int *r) {
	*r = (*r + 1) % n;
	Q[*r].v = v;
}

int dequeue(int *f, int *r) {
	int ret;
	
	ret = Q[*f].v;
	*f = (*f + 1) % n;

	return ret;
}

void TopologicalSort(Graph *G) {
	int f = 0, r = -1;
	int u, w;

	Q = (Queue*)malloc(sizeof(Queue) * n);
	in = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		in[i] = G->vertices[i].inDegree;
		if (in[i] == 0)
			enqueue(i, &f, &r);
	}

	int t = 1; //t:위상순위
	topOrder = (int*)malloc(sizeof(int) * n);	//정점들의 위상순서,topOrder[0]은 DAG 확인하는 자리, topOrder[1:n]이 위상순서자리

	while (!isEmpty(f, r)) {
		u = dequeue(&f, &r);
		topOrder[t] = u;
		t++;

		Incidence* q = G->vertices[u].outEdges->next;
		while (q != NULL) {
			w = G->edges[q->edgeid].destination;
			in[w] = in[w] - 1;
			if (in[w] == 0)
				enqueue(w, &f, &r);
			q = q->next;
		}
	}

	if (t <= n)	//아직 위상순위가 매겨지지 않은 정점이 존재하면
		topOrder[0] = 0;
	else
		topOrder[0] = 1;
}

int main() {
	Graph G;

	BuildGraph(&G);

	TopologicalSort(&G);

	if (topOrder[0] == 0)
		printf("%d", 0);
	else {
		for (int i = 1; i <= n; i++)
			printf("%c ", G.vertices[topOrder[i]].vname);
	}

	return 0;
}