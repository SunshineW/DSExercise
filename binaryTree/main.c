#include<stdio.h>
#include<stdlib.h>
#include"lib/bin.h"
int main(int argc, char **argv)
{
	struct bin_tree *tree = bin_create();
	bin_insert(tree,5);
	bin_insert(tree,3);
	bin_insert(tree,11);
	bin_insert(tree,1);
	bin_insert(tree,13);
	bin_insert(tree,6);
	bin_insert(tree,7);
	bin_insert(tree,9);
	
	bin_walk(tree);
	printf("\n");
	printf("the tree has %d nodes\n", bin_count(tree));
	bin_destory(tree);
	return 0;
	
	
}