#include<stdio.h>
#include"myhead.h"

int main(int argc, char **argv)
{
 	bin_node *tree;
	if(bin_creat(&tree) != -1)
	{
		printf("creat success!\n");
	}
	else
	{
		printf("creat failure!\n");
		return 0;
	}
		
	printf("deepth: %d\n", deepth(tree));
	printf("nodes: %d\n", nodes(tree));
	printf("leave: %d\n\n", leave(tree));
	print_message(tree);
	
	exchange(tree);
	printf("\nthe traveral order after exchange\n");
	print_message(tree);
	
	return 0;
}