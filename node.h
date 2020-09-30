#ifndef NODE_H
#define NODE_H

#include "token.h"

typedef struct Node{ 
	char *nonterminal; //function the node was made from
	TOKEN *token; //token of the node
	struct Node *child1;
	struct Node *child2;
	struct Node *child3;
	struct Node *child4;
} Node; 

#endif 
