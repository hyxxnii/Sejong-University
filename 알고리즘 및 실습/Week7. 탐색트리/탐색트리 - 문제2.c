#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct node {
	struct node *left;
	struct node *right;
	struct node *parent;
	int key;
	int height;
}AVL;

struct node *root;

void *expandExternal(AVL *w, int key) {
	AVL *left = (AVL *)malloc(sizeof(AVL));
	AVL *right = (AVL *)malloc(sizeof(AVL));

	left->left = NULL;
	left->right = NULL;
	left->parent = w;
	left->height = 0;

	right->left = NULL;
	right->right = NULL;
	right->parent = w;
	right->height = 0;

	w->left = left;
	w->right = right;
	w->key = key;
	w->height++;
}

int isExternal(AVL *node) {
	return (node->left == NULL && node->right == NULL);
}

int isBalanced(AVL *node) {
	if (node->left->height >= node->right->height)
		return (node->left->height - node->right->height < 2);
	else
		return (node->right->height - node->left->height < 2);
}

int updateHeight(AVL *node) {
	int h;

	if (node->left->height > node->right->height)
		h = node->left->height + 1;
	else
		h = node->right->height + 1;
	
	if (h != node->height) {
		node->height = h;
		return 1;
	}
	else
		return 0;
}

void *restructure(AVL *x, AVL *y, AVL *z) {
	AVL *a, *b, *c;
	AVL *T0, *T1, *T2, *T3;

	//4가지 유형의 회전

	if (x->key < y->key && y->key < z->key) {
		a = x;
		b = y;
		c = z;
		T0 = a->left;
		T1 = a->right;
		T2 = b->right;
		T3 = c->right;
	}

	else if (z->key < y->key && y->key < x->key) {
		a = z;
		b = y;
		c = x;
		T0 = a->left;
		T1 = b->left;
		T2 = c->left;
		T3 = c->right;
	}

	else if ((x->key > y->key) && (y->key < z->key)) {
		a = y;
		b = x;
		c = z;
		T0 = a->left;
		T1 = b->left;
		T2 = b->right;
		T3 = c->right;
	}

	else {
		a = z;
		b = x;
		c = y;
		T0 = a->left;
		T1 = b->left;
		T2 = b->right;
		T3 = c->right;
	}

	if (z->parent == NULL) {
		root = b;
		b->parent = NULL;
	}

	else if (z->parent->left == z) {
		z->parent->left = b;
		b->parent = z->parent;
	}

	else if (z->parent->right == z) {
		z->parent->right = b;
		b->parent = z->parent;
	}

	a->left = T0;
	T0->parent = a;
	a->right = T1;
	T1->parent = a;
	updateHeight(a);

	c->left = T2;
	T2->parent = c;
	c->right = T3;
	T3->parent = c;
	updateHeight(c);

	b->left = a;
	a->parent = b;
	b->right = c;
	c->parent = b;
	updateHeight(b);
}

void searchAndFixAfterInsertion(AVL *node) {
	AVL *z = NULL, *y = NULL, *x = NULL;

	if (node->parent == NULL)
		return;

	z = node->parent;

	while (isBalanced(z) && updateHeight(z)) {
		if (z->parent == NULL)
			break;
		z = z->parent;
	}

	if (isBalanced(z))
		return;
	
	if (z->left->height > z->right->height)
		y = z->left;
	else
		y = z->right;

	if (y->left->height > y->right->height)
		x = y->left;
	else
		x = y->right;

	restructure(x, y, z);
}

AVL *treeSearch(AVL *node, int key) {
	if (isExternal(node))
		return node;
	if (node->key == key)
		return node;
	else if (node->key > key)
		return treeSearch(node->left, key);
	else
		return treeSearch(node->right, key);
}

void insertItem(AVL *root, int key) {
	AVL *p = treeSearch(root, key);

	if (!isExternal(p))
		exit(-1);

	expandExternal(p, key);
	searchAndFixAfterInsertion(p);
}

void printTree(AVL *root) {
	if (root->left != NULL && root->right != NULL) {
		printf(" %d", root->key);
		printTree(root->left);
		printTree(root->right);
	}
}

int main() {
	char dem;
	int key;
	root = NULL;

	while (1) {
		scanf("%c", &dem);
		getchar();

		switch (dem) {
		case 'i':
			scanf("%d", &key);
			getchar();
			if (root == NULL) {
				root = (AVL *)malloc(sizeof(AVL));
				root->left = (AVL *)malloc(sizeof(AVL));
				root->right = (AVL *)malloc(sizeof(AVL));
				root->parent = NULL;
				root->left->parent = root;
				root->right->parent = root;
				root->left->left = NULL;
				root->left->right = NULL;
				root->right->left = NULL;
				root->right->right = NULL;
				root->left->height = 0;
				root->right->height = 0;
				root->key = key;
				root->height = 1;
			}
			else
				insertItem(root, key);
			break;

		case 's':
			scanf("%d", &key);
			getchar();
			AVL *p = treeSearch(root, key);
			if (!isExternal(p))
				printf("%d\n", p->key);
			else
				printf("X\n");
			break;

		case 'p':
			printTree(root);
			printf("\n");
			break;

		case 'q':
			exit(-1);
		}
	}

	return 0;
}