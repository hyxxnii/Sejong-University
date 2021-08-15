#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int data;
	int id;
	struct node *left;
	struct node *right;
}NODE;

NODE *getnode(NODE *left, int data, NODE *right, int id)
{
	NODE *new_node;

	new_node = (NODE *)malloc(sizeof(NODE));
	new_node->left = left;
	new_node->right = right;
	new_node->data = data;
	new_node->id = id;

	return new_node;
}

void Find_node(NODE *treenode, int num)
{
	if (treenode != NULL)
	{
		if (treenode->data == num && treenode->id == 1)
		{
			printf("root");
			exit(-1);
		}

		if (treenode->left != NULL)
		{
			if (treenode->left->data == num)
			{
				printf("left");
				exit(-1);
			}
		}
		
		if (treenode->right != NULL)
		{
			if (treenode->right->data == num)
			{
				printf("right");
				exit(-1);
			}
		}
		
		if (treenode->id == 8)
		{
			printf("nowhere");
			exit(-1);
		}
		Find_node(treenode->left, num);
		Find_node(treenode->right, num);
	}
}

int main()
{
	NODE *t8 = getnode(NULL, 80, NULL, 8);
	NODE *t7 = getnode(NULL, 130, NULL, 7);
	NODE *t6 = getnode(t7, 120, t8, 6);
	NODE *t5 = getnode(NULL, 90, NULL, 5);
	NODE *t4 = getnode(NULL, 70, NULL, 4);
	NODE *t3 = getnode(NULL, 50, t6, 3);
	NODE *t2 = getnode(t4, 30, t5, 2);
	NODE *t1 = getnode(t2, 20, t3, 1);
	NODE *tree = t1;
	NODE *find_node;
	int num;

	scanf("%d", &num);

	Find_node(tree, num);

	return 0;
}