#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	int data;
	int id;
	struct node *left;
	struct node *right;
}NODE;

NODE *getnode(NODE *left, NODE *right, int elem, int id) {
	NODE *node = (NODE *)malloc(sizeof(NODE));

	node->left = left;
	node->right = right;
	node->data = elem;
	node->id = id;

	return node;
}

NODE *Find_node(NODE *node, int id) {
	NODE *ret;

	if (node != NULL)
	{
		if (node->id == id)
			return node;

		ret = Find_node(node->left, id);
		if (ret != NULL)
			return ret;

		ret = Find_node(node->right, id);
		if (ret != NULL)
			return ret;
	}

	return NULL;
}

void PreOrder(NODE *root) {
	if (root != NULL) {
		printf(" %d", root->data);
		PreOrder(root->left);
		PreOrder(root->right);
	}
}

void inOrder(NODE *root) {
	if (root != NULL) {
		inOrder(root->left);
		printf(" %d", root->data);
		inOrder(root->right);
	}
}

void PostOrder(NODE *root) {
	if (root != NULL) {
		PostOrder(root->left);
		PostOrder(root->right);
		printf(" %d", root->data);
	}
}

int main()
{
	NODE *F8, *F7, *F6, *F5, *F4, *F3, *F2, *F1, *root, *p = NULL;
	int order, ID;

	F8 = getnode(NULL, NULL, 80, 8);
	F7 = getnode(NULL, NULL, 130, 7);
	F6 = getnode(F7, F8, 120, 6);
	F5 = getnode(NULL, NULL, 90, 5);
	F4 = getnode(NULL, NULL, 70, 4);
	F3 = getnode(NULL, F6, 50, 3);
	F2 = getnode(F4, F5, 30, 2);
	F1 = getnode(F2, F3, 20, 1);
	root = F1;
	
	scanf("%d %d", &order, &ID);

	p = Find_node(root, ID);

	if (p == NULL) {
		printf("-1");
		return -1;
	}

	switch (order) 
	{
	case 1:
		PreOrder(p);
		break;
	
	case 2:
		inOrder(p);
		break;

	case 3:
		PostOrder(p);
		break;
	}
	
	return 0;
}