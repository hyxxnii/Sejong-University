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
}Vertices;

typedef struct edge {
	struct vertex* from;	//간선의 시작점
	struct vertex* target;	//간선의 끝점
	struct edge* next;
	int weight;
}Edges;

typedef struct graph {
	struct vertex* Vertex;	//head
	struct edge* Edge;	//head
}Graph;

Graph* initGraph() {
	Graph* new_G = (Graph*)malloc(sizeof(Graph));
	new_G->Vertex = NULL;
	new_G->Edge = NULL;

	return new_G;
}

void CreatVertex(Graph* G, int data) {
	Vertices* new_v = (Vertices*)malloc(sizeof(Vertices));
	Vertices* p = G->Vertex;

	new_v->data = data;
	new_v->incidence = NULL;
	new_v->next = NULL;

	if (p == NULL)
		G->Vertex = new_v;

	else {
		while (p->next != NULL) {
			p = p->next;
		}

		p->next = new_v;
	}
}

void CreatEdge(Graph* G, int f, int t, int w) {
	Vertices* p = G->Vertex;
	Incidence* q;
	Incidence* new_i = (Incidence*)malloc(sizeof(Incidence));
	Incidence* new_i2 = (Incidence*)malloc(sizeof(Incidence));
	Edges* e = G->Edge;
	Edges* new_e = (Edges*)malloc(sizeof(Edges));

	new_e->weight = w;
	new_e->next = NULL;
	new_i->next = NULL;
	new_i2->next = NULL;

	if (e == NULL)
		G->Edge = new_e;
	else {
		while (e->next != NULL) {
			e = e->next;
		}
		e->next = new_e;
	}

	while (1) {	//f에 대한 간선 추가 
		if (p == NULL)
			break;

		if (p->data == f) {
			new_e->from = p;
			q = p->incidence;
			new_i->edge = new_e;

			if (q == NULL)
				p->incidence = new_i;
			else {
				while (q->next != NULL) {
					q = q->next;
				}
				q->next = new_i;
			}
			break;
		}
		p = p->next;
	}

	//p=G->Vertex;
	//함수 인자로 넣을때 항상 f <= t로 넣을거기때문에 위처럼 초기화 안했음

	if (f == t) {
		new_e->target = p;
		return;
	}

	while (1) {	//t에 대한 간선추가
		if (p == NULL)
			break;

		if (p->data == t) {
			new_e->target = p;
			q = p->incidence;
			new_i2->edge = new_e;

			if (q == NULL)
				p->incidence = new_i2;
			else {
				while (q->next != NULL) {
					q = q->next;
				}
				q->next = new_i2;
			}
			break;
		}
		else
			p = p->next;
	}
}

void AdjacentNode(Graph* G, int num) {
	//node와 node의 간선 가중치를 오름차순 출력
	//정점이 존재하지않으면 -1 출력

	Vertices* p = G->Vertex;
	Incidence* q;

	while (p != NULL) {
		if (p->data == num)
			break;
		p = p->next;
	}

	if (p == NULL) {
		printf("-1\n");
		return;
	}

	q = p->incidence;
	while (1) {
		if (q == NULL)
			break;

		if (q->edge->from->data == num)
			printf(" %d %d", q->edge->target->data, q->edge->weight);
		else
			printf(" %d %d", q->edge->from->data, q->edge->weight);

		q = q->next;
	}

	printf("\n");
}

void RemoveGraph(Graph* G, int a, int b, int w) {
	//w=0이면 (a,b) 삭제
	//삭제할때 삭제할 incidence와 연결된 vertex의 incidence NULL로 해주기
	//edge도 삭제해줘야함 (복잡예상)
	//edge 맨 첫번째 꺼 삭제되는 경우 생각해봐

	Vertices* pa = G->Vertex, * pb = G->Vertex;	//p = 정점 a, q = 정점 b
	Incidence* qa, * qb;
	int flag = 0, flag2 = 0;

	if (a > b) {
		//오름차순으로 넣었기 때문에 edge의 f < = t가 되도록 만들었음
		//즉 확인할 때도 (a, b)가 a <= b가 되도록 만들어주고 확인
		int tmp = a;
		a = b;
		b = tmp;
	}

	while (pa != NULL) {	//정점 a가 존재하는지 확인
		if (pa->data == a) {
			flag = 1;
			break;
		}
		pa = pa->next;
	}

	while (pb != NULL) {	//정점 b가 존재하는지 확인
		if (pb->data == b) {
			flag2 = 1;
			break;
		}
		pb = pb->next;
	}

	if (flag == 0 || flag2 == 0) {	//정점 a 혹은 정점 b가 존재하지않는 경우
		printf("-1\n");
		return;
	}

	flag = 0;
	flag2 = 0;

	//간선 (a,b)가 존재하는지 확인, a와 b 중 하나만 탐색해도됨
	//pa는 정점 a, pb는 정점 b를 가리키고 있는 상태
	qa = pa->incidence;
	if (qa != NULL) {
		while (1) {	//간선 (a,b)가 존재하면 w 바꾸고 flag 세우기
			if (qa == NULL)
				break;

			if (qa->edge->from->data == a) {
				if (qa->edge->target->data == b) {
					qa->edge->weight = w;
					flag = 1;
					break;
				}
			}
			else {
				if (qa->edge->from->data == b) {
					qa->edge->weight = w;
					flag = 1;
					break;
				}
			}
			qa = qa->next;
		}
	}

	if (flag == 0)	//간선 (a,b)가 존재하지않으면 return
		return;

	//pa는 정점 a, pb는 정점 b를 가리키고 있는 상태
	//1.pa의 간선 삭제(부착리스트 삭제)
	qa = pa->incidence;
	qb = pb->incidence;

	if (qa->edge->from->data == a && qa->edge->target->data == b) {	//삭제할 간선이 맨 앞에 존재하는 경우
		if (qa->next == NULL) {
			pa->incidence = NULL;
			free(qa);
		}
		else {
			pa->incidence = qa->next;
			free(qa);
		}
	}
	else {
		Incidence* i = qa;
		while (1) {
			if (qa == NULL)
				break;

			if (qa->edge->from->data == a && qa->edge->target->data == b) {
				if (qa->next == NULL) {	//맨 뒤인 경우
					i->next = NULL;
					free(qa);
				}
				else {
					i->next = qa->next;
					free(qa);
				}
				break;
			}

			i = qa;
			qa = qa->next;
		}
	}

	if (a == b)	//셀프 간선이면 위에서 1번만!
		return;
	//2.pb의 간선 삭제(부착리스트 삭제)
	if (qb->edge->from->data == a && qb->edge->target->data == b) {
		if (qb->next == NULL) {
			pb->incidence = NULL;
			free(qb);
		}
		else {
			pb->incidence = qb->next;
			free(qb);
		}
	}
	else {
		Incidence* i = qb;
		while (1) {
			if (qb == NULL)
				break;

			if (qb->edge->from->data == a && qb->edge->target->data == b) {
				if (qb->next == NULL) {
					i->next = NULL;
					free(qb);
				}
				else {
					i->next = qb->next;
					free(qb);
				}

				break;
			}
			i = qb;
			qb = qb->next;
		}
	}

	//edge 삭제

	Edges* E = G->Edge;

	if (E->from->data == a && E->target->data == b) {	//삭제할 edge가 맨 앞에 있는 경우
		G->Edge = E->next;
		free(E);
	}
	else {
		Edges* ep = E;
		while (1) {
			if (E == NULL)
				break;

			if (E->from->data == a && E->target->data == b) {
				if (E->next == NULL) {
					ep->next = NULL;
					free(E);
				}
				else {
					ep->next = E->next;
					free(E);
				}
				break;
			}

			ep = E;
			E = E->next;
		}
	}
}

void Modify(Graph* G, int a, int b, int w) {
	//오름차순 넣기
	//간선 (a,b)의 가중치를 w로 변경
	//그래프에 정점 a 혹은 b가 존재하지않으면 -1 출력
	//간선이 존재하지 않을 때는 가중치 w인 새로운 간선 (a,b) 생성

	Vertices* pa = G->Vertex, * pb = G->Vertex;	//p = 정점 a, q = 정점 b
	Incidence* qa, * qb;
	int flag = 0, flag2 = 0;

	if (a > b) {
		//오름차순으로 만들 것이기 때문에 edge의 f < = t가 되도록 넣어줌
		//즉 (a, b)가 a <= b가 되도록
		int tmp = a;
		a = b;
		b = tmp;
	}

	while (pa != NULL) {	//정점 a가 존재하는지 확인
		if (pa->data == a) {
			flag = 1;
			break;
		}
		pa = pa->next;
	}

	while (pb != NULL) {	//정점 b가 존재하는지 확인
		if (pb->data == b) {
			flag2 = 1;
			break;
		}
		pb = pb->next;
	}

	if (flag == 0 || flag2 == 0) {	//정점 a 혹은 정점 b가 존재하지않는 경우
		printf("-1\n");
		return;
	}

	flag = 0;
	flag2 = 0;

	//간선 (a,b)가 존재하는지 확인, a와 b 중 하나만 탐색해도됨
	//pa는 정점 a, pb는 정점 b를 가리키고 있는 상태
	qa = pa->incidence;
	if (qa != NULL) {
		while (1) {	//간선 (a,b)가 존재하면 w 바꾸고 flag 세우기
			if (qa == NULL)
				break;

			if (qa->edge->from->data == a) {
				if (qa->edge->target->data == b) {
					qa->edge->weight = w;
					flag = 1;
					break;
				}
			}
			else {
				if (qa->edge->from->data == b) {
					qa->edge->weight = w;
					flag = 1;
					break;
				}
			}
			qa = qa->next;
		}
	}

	if (flag == 1)	//간선 (a,b)가 존재해서 w 바꿨으면 return
		return;

	//간선 (a,b)가 존재하지 않는 경우
	//1. pa의 부착리스트 오름차순 정렬
	qa = pa->incidence;
	Edges* new_e = (Edges*)malloc(sizeof(Edges));
	Incidence* new_i = (Incidence*)malloc(sizeof(Incidence));
	new_e->weight = w;
	new_e->next = NULL;
	new_i->edge = new_e;
	new_i->next = NULL;

	Vertices* v = G->Vertex;
	while (v != NULL) {
		if (v->data == a)
			break;
		v = v->next;
	}
	new_e->from = v;

	while (v != NULL) {
		if (v->data == b)
			break;
		v = v->next;
	}
	new_e->target = v;

	if (qa == NULL)		//정점 pa에 연결된 부착리스트가 0개인 경우
		pa->incidence = new_i;
	else {
		Incidence* i = qa;
		if (qa->edge->from->data == a && qa->edge->target->data > b) {	//처음부터 from의 data는 a와 같은데 target의 data가 b보다 큰 경우 맨 앞에 넣어주고 끝
			new_i->next = qa;
			pa->incidence = new_i;
			//굳이 뒤에 더 확인 안해봐도됨
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
		Incidence* new_i2 = (Incidence*)malloc(sizeof(Incidence));
		new_i2->next = NULL;
		new_i2->edge = new_e;
		qb = pb->incidence;
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

	//edge 맨 뒤에 달아주기
	Edges* e = G->Edge;
	while (e != NULL) {
		e = e->next;
	}
	e = new_e;
}

int main() {
	Graph* G = initGraph();
	int num, a, b, w;
	char dem;

	for (int i = 1; i <= 6; i++)
		CreatVertex(G, i);

	CreatEdge(G, 1, 2, 1);
	CreatEdge(G, 1, 3, 1);
	CreatEdge(G, 1, 4, 1);
	CreatEdge(G, 1, 6, 2);
	CreatEdge(G, 2, 3, 1);
	CreatEdge(G, 3, 5, 4);
	CreatEdge(G, 5, 5, 4);
	CreatEdge(G, 5, 6, 3);

	//예제 : m 4 1 0  ->  m 1 4 4 완료!
	//예제 : a 1 -> m 1 2 0 -> m 1 3 0 완료!
	//예제 : 1~6까지 모두 삭제 후 m 2 4 4 완료!

	while (1) {
		scanf("%c", &dem);

		switch (dem) {
		case 'a':
			scanf("%d", &num);
			getchar();
			AdjacentNode(G, num);
			break;

		case 'm':
			scanf("%d %d %d", &a, &b, &w);
			getchar();
			if (w == 0)
				RemoveGraph(G, a, b, w);
			else
				Modify(G, a, b, w);
			break;

		case 'q':
			exit(-1);
			break;
		}
	}

	return 0;
}