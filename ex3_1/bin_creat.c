#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<assert.h>

typedef struct bin_node
{
	char data;
	struct bin_node *left, *right;
}bin_node;

/* 先序构造二叉树 */
int bin_creat(bin_node **node)
{
	char ch;
	scanf("%c",&ch);
	if(ch == ' ')
	{
		*node = NULL;
	}
	else
	{
		*node = (bin_node *)malloc(sizeof(bin_node));
		if (*node == NULL)
		{
			printf("malloc\n");
			return -1;
		}
		(*node)->data = ch;
		bin_creat(&((*node)->left));
		bin_creat(&((*node)->right));
	}
	return 0;
}

/* 遍历二叉树 way代表遍历方式
 * 1:先序  2:中序  3:后序 */
void traversal(bin_node *node, int way)
{
	switch(way)
	{
		case 1:
			if(node == NULL) return;
			printf("%c",node->data);
			traversal(node->left,1);
			traversal(node->right,1);
			break;
		case 2:
			if(node == NULL) return;
			traversal(node->left,2);
			printf("%c",node->data);
			traversal(node->right,2);
			break;			
		case 3:
			if(node == NULL) return;
			traversal(node->left,3);
			traversal(node->right,3);
			printf("%c",node->data);	
	}
} 

void main()
{
 	bin_node *tree;
	if(bin_creat(&tree) != -1)
		printf("creat success!\n");
	else
		printf("creat failure!\n");
	traversal(tree,1); 
	printf("\n");
	traversal(tree,2); 
	printf("\n");
	traversal(tree,3);
	printf("\n");
	printf("=============\n");
}