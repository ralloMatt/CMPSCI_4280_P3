#ifndef STACK_H
#define STACK_H 
#include "node.h" 

//build the stack while checking static semantics
void build_stack(Node*);

//push onto stack
void push(char*, TOKEN*);

//pop off of stack
void pop(char*);

//used to see if a variable has been defined more than once in stack
int check_me(char*);

//used to see if variable has been defined
int find(char*); 

void print_stack();
#endif