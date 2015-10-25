#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<assert.h>

#include"myhead.h"

/* 求树的深度 */
int deepth(bin_node *node)
{
	if (node == NULL)
	{
		return 0;
	}
	return 1 + (deepth(node->left) >= deepth(node->right) \
				? deepth(node->left) \
				: deepth(node->right));			
}

/* 求树的节点数 */
int nodes(bin_node *node)
{
	if (node == NULL)
	{
		return 0;
	}
	return 1 + nodes(node->left) + nodes(node->right);
}

/* 求树的叶节点数 */
int leave(bin_node *node)
{
	if (node == NULL)
	{
		return 0;
	}
	if(node->left == NULL && node->right == NULL)
	{
		return 1;
	}
	return leave(node->left) + leave(node->right);
}

/* 将树的所有左右子树经行交换 */
void exchange(bin_node *node)
{
	if (node == NULL)
	{
		return;
	}
	bin_node *temp;
	temp = node->left;
	node->left = node->right;
	node->right = temp;
	exchange(node->left);
	exchange(node->right);
}

/* 初始化队列, size为队列的大小 */
int quene_init(quene *q, int size)
{
	q->size = size;
	q->front = q->rear = 0;
	q->node_array = (bin_node **)malloc(sizeof(bin_node *) * size);
	if (q->node_array == NULL)
	{
		return -1;
	}
	else
		return 0;
}
int quene_put(quene *q, bin_node *node)
{
	assert(q->rear != q->size - 1);
	q->node_array[(q->rear)++] = node;
	return 0;
}
int quene_empty(quene *q)
{
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}
bin_node *quene_get(quene *q)
{
	assert(quene_empty(q) != 1);
	return q->node_array[(q->front)++];
}

/* 层序遍历 */
int traversal_by_level(bin_node *node)
{
	bin_node *temp = node;
	
	quene *q = (quene *)malloc(sizeof(quene));
	if(q == NULL)
	{
		return -1;
	}
	
	int deep = deepth(node);/* 根据树的高度求出所需队列的最大大小 */
	int size = 1;
	while(deep > 0)
	{
		size <<= 1;
		deep--;
	}
	quene_init(q, size);
	quene_put(q, temp);
	while (quene_empty(q)!= 1)
	{
		temp = quene_get(q);
		printf("%c",temp->data);
		if (temp->left != NULL)
		{
			quene_put(q, temp->left);
		}
		if (temp->right != NULL)
		{
			quene_put(q, temp->right);
		}
	}
	return 0;
}

/* 先序插入顺序创建一个二叉树 */
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
void print_message(bin_node *node)
{
	printf("%-12s: ", "pre_order");
	traversal(node,1); 
	printf("\n%-12s: ", "in_order");
	traversal(node,2); 
	printf("\n%-12s: ", "post_order");
	traversal(node,3);
	printf("\n%-12s: ", "lever_order");
	traversal_by_level(node);
	printf("\n");
}