#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
}NODE;

NODE *get_node(NODE *node, int l, int r, int id) {
	
	if (node == NULL) {
		node = (NODE *)malloc(sizeof(NODE));
		node->data = id;
	}
	
	if (l == 0)
		node->left = NULL;
	else {
		node->left = (NODE *)malloc(sizeof(NODE));
		node->left->data = l;
	}

	if (r == 0)
		node->right = NULL;
	else {
		node->right = (NODE *)malloc(sizeof(NODE));
		node->right->data = r;
	}

	return node;
}

NODE *Find_node(NODE *node, int data) {
	NODE *ret;

	if (node != NULL)
	{
		if (node->data == data)
			return node;

		ret = Find_node(node->left, data);
		if (ret != NULL)
			return ret;

		ret = Find_node(node->right, data);
		if (ret != NULL)
			return ret;
	}

	return NULL;
}

void Print(NODE *node, char info[101]) {
	int len = strlen(info), i = 0;
	NODE *p = node;


	while (len >= 0) {
		printf(" %d", p->data);

		if (info[i] == 'R') {
			p = p->right;
		}
		
		if (info[i] == 'L') {
			p = p->left;
		}

		i++;
		len--;
	}
	printf("\n");

}

int main()
{
	NODE *root = NULL, *p = NULL;
	int i, n, s, id, l, r;
	char info[101] = "";
	
	scanf("%d", &n);

	while (n > 0) {
		scanf("%d %d %d", &id, &l, &r);
		
		if (root == NULL){
			root=get_node(root, l, r, id);
		}

		else {
			p = Find_node(root, id);
			p=get_node(p, l, r, id);
		}

		n--;
	}

	scanf("%d", &s);

	while (s > 0) {
		getchar();
		scanf("%s", info);

		Print(root, info);

		s--;
	}

	return 0;
}