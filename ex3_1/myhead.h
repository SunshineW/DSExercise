#ifndef ex_3_1_H_
#define ex_3_1_H_

/* 二叉树的节点类型 */
typedef struct bin_node
{
	char data;
	struct bin_node *left, *right;
}bin_node;

/* 顺序队列，对二叉树层序遍历时用 */
typedef struct quene
{
	bin_node **node_array;
	int size;
	int front;
	int rear;
}quene;


/* 初始化队列, size为队列的大小 */
int quene_init(quene *q, int size);

/* 入队操作 */
int quene_put(quene *q, bin_node *node);

/* 出队操作 */
bin_node *quene_get(quene *q);

/* 判断队是否为空 */
int quene_empty(quene *q);

/* 层序遍历 */
int traversal_by_level(bin_node *node);

/* 先序插入顺序创建一个二叉树 */
int bin_creat(bin_node **node);

/* 求以NODE为跟的二叉树的深度 */
int deepth(bin_node *node);

/* 求以NODE为跟的二叉树的节点的数量 */
int nodes(bin_node *node);

/* 求以NODE为二叉树叶节点的数量 */
int leave(bin_node *node);

/* 把二叉树的左右子树经行交换 */
void exchange(bin_node *node);

/* 遍历二叉树，way为遍历方式，1：前序 2：中序 3： 后序 */
void traversal(bin_node *node, int way);

/* 打印二叉树的几种遍历方式输出的信息 */
void print_message(bin_node *node);

#endif