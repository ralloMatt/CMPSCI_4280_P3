#ifndef PARSER_H
#define PARSER_H 
#include "node.h" 
Node* parser(FILE *); //takes in file to send to scanner

//setNode allocates the memory for the node and labels it 
Node* setNode(char *);

//Nonterminals
Node* program();
Node* block();
Node* vars();
Node* mvars();
Node* expr();
Node* M();
Node* T();
Node* F();
Node* R();
Node* stats();
Node* mStat();
Node* stat();
Node* in();
Node* out();
Node* if_nterm(); // <if> named different because if taken
Node* loop();
Node* assign();
Node* RO();



#endif