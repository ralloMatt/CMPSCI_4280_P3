#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include "stack.h"
#define MAX 100 //number of items in stack

char *stack[MAX]; //stack of strings(variables)
int tos = -1; //top of stack
int varct = -1; //the number of variables in that scope

int block_varct[MAX];
int place = 0;

//make the stack
void build_stack(Node* parse_tree){
	
	if(parse_tree == NULL){ //end of tree (at a leaf when function was called)
		return;
	}
	else if(strcmp(parse_tree->nonterminal, "program") == 0){

		//go through first child (vars)
		build_stack(parse_tree->child1);

		//keep track of number of variables defined
		block_varct[place] = varct;
		place++; //add to place for more vartct's

		//go through second child (block) and so on
		build_stack(parse_tree->child2);
		build_stack(parse_tree->child3);
		build_stack(parse_tree->child4);
		
		//pop variables in global scope
		pop(parse_tree->token->instance);
	}
	else if(strcmp(parse_tree->nonterminal, "block") == 0){
		
		//go through first child (vars)
		build_stack(parse_tree->child1);

		//keep track of number of variables defined
		block_varct[place] = varct;
		place++; //add to place for more vartct's
	
		//go through second child (stats) and so on
		build_stack(parse_tree->child2);
		build_stack(parse_tree->child3);
		build_stack(parse_tree->child4);
	
		// once done with a block
		// pop variables in that scope
		pop(parse_tree->token->instance);
	

	}
	else if(strcmp(parse_tree->nonterminal, "vars") == 0){
		//start varct
		varct = -1; 
		//put in stack
		push(parse_tree->token->instance, parse_tree->token);
		
		//go through first child (mvars) and so on
		build_stack(parse_tree->child1);
		build_stack(parse_tree->child2);
		build_stack(parse_tree->child3);
		build_stack(parse_tree->child4);
	}
	else if(strcmp(parse_tree->nonterminal, "mvars") == 0){
		//put in stack
		push(parse_tree->token->instance, parse_tree->token);
		
		//go through first child (mvars) and so on
		build_stack(parse_tree->child1);
		build_stack(parse_tree->child2);
		build_stack(parse_tree->child3);
		build_stack(parse_tree->child4);
	}
	else if(strcmp(parse_tree->nonterminal, "R") == 0){
		
		//see if token is identifier
		if(strcmp(check_id[parse_tree->token->id], "ID_tk") == 0){
			//check to see if identifier has been defined
			if(find(parse_tree->token->instance) == -1) {
				printf("ERROR: '%s' not defined\n", parse_tree->token->instance);
				printf("Located at line %d\n", parse_tree->token->line);
				exit(0);
			}
		}
		//go through other nonterminals child and so on (don't care right now)
		//we only care about static semantics
		build_stack(parse_tree->child1);
		build_stack(parse_tree->child2);
		build_stack(parse_tree->child3);
		build_stack(parse_tree->child4);
		
		
	}
	else if(strcmp(parse_tree->nonterminal, "in") == 0){
		//check to see if identifier has been defined
		if(find(parse_tree->token->instance) == -1) {
				printf("ERROR: '%s' not defined\n", parse_tree->token->instance);
				printf("Located at line %d\n", parse_tree->token->line);
				exit(0);
		}
		
		//go through other nonterminals child and so on (don't care right now)
		//we only care about static semantics
		build_stack(parse_tree->child1);
		build_stack(parse_tree->child2);
		build_stack(parse_tree->child3);
		build_stack(parse_tree->child4);
	}
	else if(strcmp(parse_tree->nonterminal, "assign") == 0){
		//check to see if identifier has been defined
		if(find(parse_tree->token->instance) == -1) {
				printf("ERROR: '%s' not defined\n", parse_tree->token->instance);
				printf("Located at line %d\n", parse_tree->token->line);
				exit(0);
		}
		
		//go through other nonterminals child and so on (don't care right now)
		//we only care about static semantics
		build_stack(parse_tree->child1);
		build_stack(parse_tree->child2);
		build_stack(parse_tree->child3);
		build_stack(parse_tree->child4);
	}
	
	
	else { 
		//go through other nonterminals child and so on (don't care right now)
		//we only care about static semantics
		build_stack(parse_tree->child1);
		build_stack(parse_tree->child2);
		build_stack(parse_tree->child3);
		build_stack(parse_tree->child4);
	}
	
	return;
}

void push(char* string, TOKEN *tk){

	if(check_me(string) == 1){ //has not been defined
		if(tos == MAX - 1){ //stack overflow
			printf("ERROR stack overflow\n");
			printf("Too many variables defined\n");
			exit(0);
			
		}
		else { // have not reached MAX number in stack
			tos++;
			varct++;
			//printf("PUSH: %s\n", string);
			strcpy(stack[tos], string); 
			return;	
		}	
	}
	else if(check_me(string) == -1){ //has already been defined ERROR
		printf("ERROR '%s' has already been defind in scope!\n", string);
		printf("Located at line: %d\n", tk->line);
		exit(0);
	}
	
	return;
}

void pop(char* string){
	
	place--;
	
	if(tos == -1){
		return; 
	}
	else {
		
		if(place == 0){ //means we are done with local variables in blocks
		
			//pop the globals
			while(tos != -1){
				//printf("\tGLOBAL_POP: %s\n", stack[tos]);
				tos--;
			}
		}
		else { //pop the locals

			while(block_varct[place] != -1){
				//printf("\tPOP: %s\n", stack[tos]);
				tos--;
				block_varct[place]--;
			}
		}
	}
	
	return;
}

//check if defined more than once
int check_me(char* string){
	int check = 1;
	
	if(tos != -1){ //means we are not at the bottom of stack
		
		//stack_ct is the number of variables in that scope
		int stack_ct;
		stack_ct = varct;
	
		//scope is the place where we are at in the stack
		int scope = tos;
	
		while(stack_ct != -1){
			//means variable has been defined in that scope
			if(strcmp(string, stack[scope]) == 0){
				check = -1;	
			}
			scope--;
			stack_ct--;
		}
	}
	
	return check;
}

//see if variable is in stack then if so
//find the distance of a variable in the stack
int find(char* string){
	//if distance is -1 then not found
	//else found the variable
	int distance = -1;
	
	int count = 0;
	int top_of_stack = tos; //used to loop through stack
	

	
	while(top_of_stack != -1){
		if(strcmp(string, stack[count]) == 0){			
			//found string
			distance = tos - count; //set distance from top of stack
			break;
		}
		count++;
		top_of_stack--;
	}

	return distance;
}

void print_stack(){

	while(tos != 0){
		printf("%s\n", stack[tos]);
		tos--;	
	}
	
	return;
}
