#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<assert.h>

#include"myhead.h"

/*求以BST为根的树的节点数*/
int nodes(struct bin_node* bst) 
{
	if (bst == NULL)
	{
		return 0;
	}
	return 1 + nodes(bst->left) + nodes(bst->right);
}

/*求组合C(m,n)的值*/
int combin(int base, int select)
{
	/*当base为零时返回1,这里与数学中的组合不同*/
	if (base == 0) 
	{
		return 1;
	}
	int numerator, denominator;
	numerator = denominator = 1;
	while(select > 0)
	{
		numerator *= base;
		denominator*= select;
		base--;
		select--;
	}
	return numerator / denominator;
}

/* 求有多少种序列能构造相同的树 */
int result(struct bin_node* bst)
{
	if (bst == NULL)
		return 1;
	return result(bst->left) * result(bst->right) * combin(nodes(bst)-1, nodes(bst->left));
}