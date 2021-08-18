#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	struct node *lChild;
	struct node *rChild;
	struct node *parent;
	int key;
}NODE;

NODE *getNode(NODE *parent, int key) {
	NODE *new_node = (NODE *)malloc(sizeof(NODE));

	new_node->lChild = (NODE *)malloc(sizeof(NODE));
	new_node->rChild = (NODE *)malloc(sizeof(NODE));
	new_node->lChild->parent = new_node;
	new_node->rChild->parent = new_node;
	new_node->lChild->lChild = NULL;
	new_node->lChild->rChild = NULL;
	new_node->rChild->lChild = NULL;
	new_node->rChild->rChild = NULL;
	new_node->parent = parent;
	new_node->key = key;

	return new_node;
}

int isExternal(NODE *node) {	// 외부노드인지 아닌지
	if (node->lChild == NULL && node->rChild == NULL)
		return 1;
	else
		return 0;
}

NODE *treeSearch(NODE *node, int key) {
	if (isExternal(node))
		return node;
	if (node->key == key)
		return node;
	else if (node->key > key)
		return treeSearch(node->lChild, key);
	else
		return treeSearch(node->rChild, key);
}

void findElement(NODE *root, int key) {
	NODE *p = treeSearch(root, key);

	if (isExternal(p))
		printf("X\n");
	else
		printf(" %d\n", p->key);
}

void insertItem(NODE *root, int key) {
	NODE *new_node;
	NODE *p = treeSearch(root, key);
	NODE *P = p->parent;

	if (!isExternal(p))
		return;

	new_node = getNode(P, key);

	if (P->key > new_node->key)
		P->lChild = new_node;

	else
		P->rChild = new_node;
}

NODE *sibling(NODE *node) {
	if (node->parent->lChild == node)
		return node->parent->rChild;
	else
		return node->parent->lChild;
}

void reduceExternal(NODE *root, NODE *node) {
	NODE *w = node->parent;
	NODE *zs = sibling(node);

	if (w->parent == NULL) {	//삭제하고자 하는 노드(w)가 root이면
		root->lChild = zs->lChild;
		root->rChild = zs->rChild;
		root->lChild->parent = zs;
		root->rChild->parent = zs;
		zs->parent = NULL;
	}

	else {
		NODE *g = w->parent;
		zs->parent = g;
		if (g->lChild == w)		//삭제하고자 하는 노드(w)가 g(w의 parent)의 오른쪽 자식이면 zs를 오른쪽 자식으로 연결
			g->lChild = zs;
		else
			g->rChild = zs;		//삭제하고자 하는 노드(w)가 g(w의 parent)의 왼쪽 자식이면 zs를 왼쪽 자식으로 연결
	}

	free(w);
	free(node);
	return zs;
}

NODE *inOrderSucc(NODE *node) {
	node = node->rChild;

	while (!isExternal(node->lChild)) {
		node = node->lChild;
	}

	return node;
}

void removeElement(NODE *root, int key) {
	NODE *w = treeSearch(root, key);
	NODE *z, *y;
	int elem;

	if (isExternal(w))
		printf(" X\n");

	else {
		z = w->lChild;
		elem = w->key;

		if (!isExternal(z))
			z = w->rChild;

		if (isExternal(z))	//z는 w의 왼쪽자식. z가 외부노드면 w의 자식 중 하나가 외부노드임->reduceExternal(z)
			reduceExternal(w, z);

		else {
			y = inOrderSucc(w);
			z = y->lChild;
			w->key = y->key;
			reduceExternal(w, z);
		}
		printf("%d\n", elem);
	}
}

void preOrder(NODE *root) {
	if (root->lChild != NULL || root->rChild != NULL) {
		printf(" %d", root->key);
		preOrder(root->lChild);
		preOrder(root->rChild);
	}
}

int main() {
	NODE *root = NULL;
	int key;
	char dem;

	while (1) {

		scanf("%c", &dem);

		switch (dem) {

		case 'i':
			getchar();
			scanf("%d", &key);
			getchar();

			if (root == NULL) {
				root = (NODE *)malloc(sizeof(NODE));
				root->key = key;
				root->lChild = (NODE *)malloc(sizeof(NODE));
				root->rChild = (NODE *)malloc(sizeof(NODE));
				root->parent = NULL;
				root->lChild->lChild = NULL;
				root->lChild->rChild = NULL;
				root->rChild->lChild = NULL;
				root->rChild->rChild = NULL;
				root->lChild->parent = root;
				root->rChild->parent = root;
				break;
			}

			insertItem(root, key);
			break;

		case 'd':
			getchar();
			scanf("%d", &key);
			removeElement(root, key);
			getchar();
			break;

		case 's':
			scanf("%d", &key);
			findElement(root, key);
			getchar();
			break;

		case 'p':
			preOrder(root);
			printf("\n");
			break;

		case 'q':
			exit(-1);
			break;
		}
	}

	return 0;
}