#ifndef MYHEAD_H_
#define MYHEAD_H_

#include"lib/bin.h"


/* return the count of the nodes of the tree 
 * rooted at BST */
int nodes(struct bin_node* bst);

/* the combine algorithm*/
int combin(int base, int select);

/* the fianlly result that we wanted*/
int result(struct bin_node* bst);

#endif