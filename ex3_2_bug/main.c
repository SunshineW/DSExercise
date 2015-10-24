#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "myhead.h"

int main(int argc, char **argv)
{
 	int i, n;
	int ret;
	while(scanf("%d",&n)&&n)
	{
		struct bin_tree* tree = bin_create();
		if (tree == NULL)
		{
			printf("bin_create error\n");
			exit(0);
		}
		int data[n];
		for (i=0; i<n; i++)
		{
			scanf("%d",&data[i]);
			ret = bin_insert(tree, data[i]);
			if (ret == 0)
			{
				printf("insert error\n");
				exit(0);
			}
		}
		printf("%d\n",result(tree->root)%9011);
		
		bin_destory(tree);
	} 
	return 0;
}


