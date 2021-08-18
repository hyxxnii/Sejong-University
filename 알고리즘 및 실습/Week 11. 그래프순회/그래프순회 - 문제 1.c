#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct incidence {
	struct incidence* next;
	struct edge* edge;
}Incidence;

typedef struct vertex {
	int data;
	struct vertex* next;
	struct incidence* incidence;
	int visited;	//0이면 방문x, 1이면 방문o
}Vertices;

typedef struct edge {
	struct vertex* from;	//간선의 시작점
	struct vertex* target;	//간선의 끝점
	struct edge* next;
}Edges;

typedef struct graph {
	struct vertex* Vertex;	//head
	struct edge* Edge;	//head
}Graph;

void initGraph(Graph* G) {
	G->Vertex = NULL;
	G->Edge = NULL;
}

void CreatVertex(Graph* G, int f) {
	Vertices* new_v = (Vertices*)malloc(sizeof(Vertices));
	Vertices* p = G->Vertex;

	new_v->data = f;
	new_v->incidence = NULL;
	new_v->next = NULL;
	new_v->visited = 0;	//방문 초기화는 0 (방문x)

	if (p == NULL)
		G->Vertex = new_v;
	else {
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = new_v;
	}
}

void CreatEdge(Graph* G, int a, int b) {
	Vertices* pa = G->Vertex, * pb = G->Vertex;
	Incidence* qa, * qb;
	Edges* new_e = (Edges*)malloc(sizeof(Edges));

	new_e->next = NULL;

	if (a > b) {
		int tmp = a;
		a = b;
		b = tmp;
	}

	//edge의 from, target 정점 연결
	while (pa != NULL) {	//pa는 정점 a
		if (pa->data == a) {
			new_e->from = pa;
			break;
		}
		pa = pa->next;
	}

	while (pb != NULL) {	//pb는 정점 b
		if (pb->data == b) {
			new_e->target = pb;
			break;
		}
		pb = pb->next;
	}
		
	Edges* e = G->Edge;		//edge 연결
	if (e == NULL)
		G->Edge = new_e;
	else {
		while (e->next != NULL) {
			e = e->next;
		}
		e->next = new_e;
	}

	//1. 정점 pa에 대한 간선 추가 (오름차순)
	qa = pa->incidence;
	Incidence* new_i = (Incidence*)malloc(sizeof(Incidence));
	new_i->edge = new_e;
	new_i->next = NULL;

	if (qa == NULL)		//정점 pa에 연결된 부착리스트가 0개인 경우
		pa->incidence = new_i;
	else {
		Incidence* i = qa;
		if (qa->edge->from->data == a && qa->edge->target->data > b) {	//처음부터 from의 data는 a와 같은데 target의 data가 b보다 큰 경우 맨 앞에 넣어주고 끝
			new_i->next = qa;
			pa->incidence = new_i;	//굳이 뒤에 더 확인x
		}
		else {
			while (1) {
				if (qa == NULL)
					break;
				if (qa->edge->from->data == a) {
					if (qa->edge->target->data < b) {
						if (qa->next != NULL) {
							if (qa->next->edge->from->data != a) {
								new_i->next = qa->next;
								qa->next = new_i;
								break;
							}
						}
						else {
							qa->next = new_i;
							break;
						}
					}
					else {
						new_i->next = qa;
						i->next = new_i;
						break;
					}
				}
				else if (qa->edge->from->data < a) {
					if (qa->next != NULL) {
						if (qa->next->edge->from->data > a) {
							new_i->next = qa->next;
							qa->next = new_i;
							break;
						}
					}
					else {
						qa->next = new_i;
						break;
					}
				}
				i = qa;
				qa = qa->next;
			}
		}
	}

	if (a != b) {	//셀프 간선(a=b)은 위에서 한 번만 ! 
	//2. pb의 부착리스트 오름차순 정렬
		qb = pb->incidence;
		Incidence* new_i2 = (Incidence*)malloc(sizeof(Incidence));
		new_i2->next = NULL;
		new_i2->edge = new_e;

		if (qb == NULL)		//정점 pb에 연결된 부착리스트가 0개인 경우
			pb->incidence = new_i2;
		else {
			Incidence* i = qb;
			if (qb->edge->target->data > b) {	//처음부터 target이 b보다 더 크면 맨 앞에 넣어주고 끝
				new_i2->next = qb;
				pb->incidence = new_i2;
				//굳이 뒤에 더 확인 안해봐도됨
			}
			else if (qb->edge->target->data == b && qb->edge->from->data > a) {		//target = b 일 때 처음부터 from > a인 경우 (맨 앞에 넣어줘야하는 경우)
				new_i2->next = qb;
				pb->incidence = new_i2;
			}
			else {
				while (1) {
					if (qb == NULL)
						break;

					if (qb->edge->target->data == b) {
						if (qb->edge->from->data < a) {
							if (qb->next != NULL) {
								if (qb->next->edge->target->data != b) {
									new_i2->next = qb->next;	//ex) (2,5) -> (5,6) 사이에 (3,5)추가 / qb는 (2,5)인 상태
									qb->next = new_i2;
									break;
								}
							}
							else {
								qb->next = new_i2;
								break;
							}
						}
						else {
							new_i2->next = qb;
							i->next = new_i2;
							break;
						}
					}

					else if (qb->edge->target->data > b) {
						new_i2->next = qb;
						i->next = new_i2;
						break;
					}
					i = qb;
					qb = qb->next;
				}
			}
		}
	}
}

void DFS(Graph *G, int s) {
	Vertices* p = G->Vertex;
	Incidence* q;

	while (1) {
		if (p==NULL || p->data == s)
			break;
		p = p->next;
	}

	p->visited = 1;
	printf("%d\n", p->data);

	q = p->incidence;
	while (1) {
		if (q == NULL)
			return;
		if (q->edge->from->data == s) {
			if (q->edge->target->visited == 0)	//방문하지않는 정점이라면
				DFS(G, q->edge->target->data);
		}
		else {
			if (q->edge->from->visited == 0)
				DFS(G, q->edge->from->data);
		}
		q = q->next;
	}
}

int main() {
	Graph G;
	int n, m, s;	//n:정점의 개수, m:간선의 개수, s:순회 시작 정점 번호
	int a, b;	//f,t:정점

	initGraph(&G);

	scanf("%d %d %d", &n, &m, &s);

	for (int i = 0; i < n; i++)
		CreatVertex(&G, i + 1);	//먼저 정점의 개수만큼 정점 만들기

	while (m > 0) {
		scanf("%d %d", &a, &b);
		CreatEdge(&G, a, b);
		m--;
	}

	DFS(&G, s);

	return 0;
}