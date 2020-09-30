#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>
#include "token.h"
#include "node.h"

void traversePreorder (Node* parse_tree, int level){
	
	if(parse_tree == NULL) //end of tree
		return;
	
	printf("%*c%d: %s \n", level*2, ' ', level, parse_tree->nonterminal);

	if(strcmp(parse_tree->token->instance, "\0") != 0)
		printf("%*cTOKEN: %s \n", level*2, ' ', parse_tree->token->instance);

	traversePreorder(parse_tree->child1, level+1);//go through first child and so on
	traversePreorder(parse_tree->child2, level+1);
	traversePreorder(parse_tree->child3, level+1);
	traversePreorder(parse_tree->child4, level+1);
	
	return;
}