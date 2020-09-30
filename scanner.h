#ifndef SCANNER_H
#define SCANNER_H
 
#include "token.h" 

void print_token_array();

//scanner() returns the next token everytime it's called by the parser
TOKEN* scanner();

//used to go back in array if needed to
void go_back();

//get previous token again
void get_previous();

//everyting below just builds token array
void scan_file(FILE *); //called by parser, then scans the file

//find_string recieves a line from the file 
//then find_string finds each string separated by a white space or tab inside the line
//then find_string sends that string to the find_tokens function
void find_string(char[], int, FILE *); 


//find_tokens takes in a string and determines if multiple tokens exist 
// then find_tokens sends each token to scan_tok
void find_tokens(char*, int, FILE *);

//scan_tok function takes a token string and line number, then returns a token structure
TOKEN *scan_tok(char[], int, FILE *); 


#endif  
