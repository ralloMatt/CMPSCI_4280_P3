#ifndef SCAN_C
#define SCAN_C

 
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "scanner.h"
#include "table.h"
#include <stdlib.h>

#define MAX 1024 //MAX is defined as 1024 (string shouldn't be bigger than that)

int token_list_size = -1;
TOKEN *token_list[0]; //list of tokens to send to parser when asked

int current_token = 0; //current token we are looking at in paraser

void print_token_array(){
	
	int i;
	for(i = 0; i <= token_list_size; i++){
		printf("TK: %s\n", token_list[i]->instance);
		
	}
	
}


TOKEN* scanner(){

	TOKEN *send_me;

	if(current_token <= token_list_size){ 
		//set token to send as current token
		send_me = token_list[current_token]; 
		//add to current_token so we look at next token
		current_token++;

	}

	return send_me;
}

void go_back(){

	current_token = current_token - 2;
	return;
}

//get previous token again
void get_previous(){

	current_token--;
	return;

}

void scan_file(FILE *fp){ //receives file pointer

	char line[MAX]; //the string associated with each line
	int line_num = 1; //line number of string in file

	while(fgets(line, MAX, fp)){ //get each line until EOF

		//printf("line #%d is: %s\n", line_num, line);

		find_string(line, line_num, fp); //send the line(string) to the find_string function

		line_num++; //add to line number
	}

	if(feof(fp)){
		// we should have EOF token
		// we check if fp is EOF later
		find_string(line, line_num, fp);
	}
	

	/*printf("size of token array: %d\n", token_list_size);


	int count = 0;
	while(count < token_list_size){

		printf("TOKEN instance: %s\n", token_list[count].instance);

		count++;
	}

	*/

	return;
}

void find_string(char line[MAX], int line_num, FILE *fp){ //find each string separated  by white space


	if(feof(fp)){ //we at end of file
		find_tokens(line, line_num, fp);
	}

	else {
		char *word; //the string from the line separated by white space

		char *newline; // used to not include the new line character in each token

		char *delim = " \t";
		
		word = strtok(line, delim); //the first string (strtoken used for search)

		while(word != NULL){ //go through other strings

			newline = strchr(word, '\n'); //check if the word contains a new line 
			if(newline) //if newline exists get rid of it 
				*newline=0;
			


			//printf("word is: %s, on line number: %d\n", word, line_num);
			
			//now we have each string so send to find_tokens;
			find_tokens(word, line_num, fp);


			word = strtok(NULL, delim);
		}
	}

	return;
}


void find_tokens(char *word, int line_num, FILE *fp){ //takes in a string and determines if multiple tokens

	char tokens[MAX]; //same as word variable, but easier to go through array
	strcpy(tokens, word); //copy the string word to tokens
	
	
	/*
	int i;
	printf("String/Token: ");
	for( i=0; i<strlen(token); i++){
		printf("%c", token[i]);

	}
	printf("\n");*/
	
	char main_token[MAX]; //the main token to send to the scanner functin
	char next_token[MAX]; //used to get the next token if there is more than one


	int place = 0; //place in tokens array, used to go through it
	int next_place = 0; //place for the possible next token

	//TOKEN *tok = NULL; //used for token structure made later
	
	if(feof(fp)){
		// we have EOF token
		
		token_list_size++;//add to ken size
		token_list[token_list_size] = malloc(sizeof(TOKEN));
		token_list[token_list_size]->instance = malloc(sizeof(char*)*MAX);
		token_list[token_list_size] = scan_tok(main_token, line_num, fp);

		/*tok = scan_tok(main_token, line_num, fp);
		//print out the token
		printf("* Token Type: %s, Instance: \"%s\", Line Number: %d\n\n", tokenNames[tok->id], tok->instance, tok->line+1);
		
		//free that memory
		free(tok->instance);
		free(tok);*/
		
		return;
	}
	
	
	
	if(isalpha(tokens[0])) { //starts with letter, could be identifier or keyword
	
		//keywords or identifiers are followed by numbers or letters
		while(isalpha(tokens[place]) || isdigit(tokens[place])){ 

			//set main token equal to tokens array as long as it's a letter or digit
			main_token[place] = tokens[place]; 

			place++; //go to next charater in tokens array
		}

		main_token[place] = '\0'; //set last character in array to null

		//printf("Main token is: %s\n", main_token);
		
		//send main_token to scanner
		token_list_size++;//add to ken size
		
		token_list[token_list_size] = malloc(sizeof(TOKEN));
		token_list[token_list_size]->instance = malloc(sizeof(char*)*MAX);
		
		token_list[token_list_size] = scan_tok(main_token, line_num, fp);

		/*tok = scan_tok(main_token, line_num, fp); 
	
		//print out the token
		printf("* Token Type: %s, Instance: \"%s\", Line Number: %d\n\n", tokenNames[tok->id], tok->instance, tok->line+1);
		
		//free that memory
		free(tok->instance);
		free(tok);*/

		if(tokens[place] != '\0'){ //means there could be another token

			while(tokens[place] != '\0'){ //loop through tokens array
				//set next_token equal to the rest of the tokens array
				next_token[next_place] = tokens[place];
				next_place++;
				place++;
			}

			//set last character in next token equal to null
			next_token[next_place] = '\0';

			//send possbile next_token to find_tokens function
			find_tokens(next_token, line_num, fp); 
		}



	} else if(isdigit(tokens[0])){ //starts with a digit, most likely have a number

				while(isdigit(tokens[place])){ //whle we have digits

					//set main token equal to tokens array
					main_token[place] = tokens[place];
					place++;
				}

				//set last character in main token array to null
				main_token[place] = '\0';

				//printf("Main token is: %s\n", main_token);
				
				//send main_token to scanner
				token_list_size++;//add to ken size
				token_list[token_list_size] = malloc(sizeof(TOKEN));
				token_list[token_list_size]->instance = malloc(sizeof(char*)*MAX);
				token_list[token_list_size] = scan_tok(main_token, line_num, fp);
				

				/*tok = scan_tok(main_token, line_num, fp);

				//print out the token
				printf("* Token Type: %s, Instance: \"%s\", Line Number: %d\n\n", tokenNames[tok->id], tok->instance, tok->line+1);
		
				//free that memory
				free(tok->instance);
				free(tok);*/


				if(tokens[place] != '\0'){ //means there could be another token

					//get the next token
					while(tokens[place] != '\0'){
						next_token[next_place] = tokens[place];
						next_place++;
						place++;
					}

					//set last next_token character to null
					next_token[next_place] = '\0';

					
					//send possible next_token to find tokens function
					find_tokens(next_token, line_num, fp);
				}
				

	}
	else{ //possibly some operator

		
	
		if(tokens[0] == '$'){ //just a comment so ignore
			//printf("Comment: %s, Line Number: %d\n", token, line_num);
			return;
		}

		int count = 0; //used later to possibly set token

		//if it's one of the single operators
		if(tokens[place] == '=' || tokens[place] == ':' || tokens[place] == '+' ||
			tokens[place] == '-' || tokens[place] == '*' || tokens[place] == '/' ||
			tokens[place] == '.' || tokens[place] == '(' || tokens[place] == ')' ||
			tokens[place] == ',' || tokens[place] == '{' || tokens[place] == '}' ||
			tokens[place] == ';' || tokens[place] == '[' || tokens[place] == ']'){
			
			//put single operator in main token then send the rest back to find_tokens		
			main_token[place] = tokens[place];
			place++;
				
			}
			else if(tokens[place] == '>' || tokens[place] == '<' || tokens[place] == '!'){

				//check for >=> <=< and !! then send rest to tokens function
					if(tokens[place] == '<' && tokens[place+1] == '=' && tokens[place+2] == '<'){
							//set main token as <=< 
							while(count < 3){
								main_token[place] = tokens[place];
								place++;
								count++;
							}
						
						
					}
						else if(tokens[place] == '>' && tokens[place+1] == '=' && tokens[place+2] == '>'){
							//set main token as >=>
							while(count < 3){
								main_token[place] = tokens[place];
								place++;
								count++;
							}
						}
							else if(tokens[place] == '!' && tokens[place+1] == '!'){
								//set main token as !!
								while(count < 2){
									main_token[place] = tokens[place];
									place++;
									count++;
								}
							}
								else {
									//most likely an error because < > and ! by themselves is not in alphabet
									//send rest of tokens to scanner then scanner should report error
									while(tokens[place] != '\0'){
										//set main token as rest of tokens array
										main_token[place] = tokens[place];
										place++;
									}
									
								}
				}
				else if(!isdigit(tokens[place]) || !isalpha(tokens[place]) || tokens[place] != '\0'){
				
					// most likely an error (character not in alphabet)
					// send rest of tokens to scanner then scanner should report error
	
					while(tokens[place] != '\0'){
						//set main token
						main_token[place] = tokens[place];
						place++;		
						}
				}
		
		//set last character in main tokens array to null
		main_token[place] = '\0';
		
		//if(main_token[0] != '\0')
			//printf("Main token is: %s\n", main_token);


		
		if(main_token[0] != '\0') //don't send empty token
		{
			//send main_token to scanner
			token_list_size++;//add to ken size
			token_list[token_list_size] = malloc(sizeof(TOKEN));
			token_list[token_list_size]->instance = malloc(sizeof(char*)*MAX);
			token_list[token_list_size] = scan_tok(main_token, line_num, fp);
			

			/*tok = scan_tok(main_token, line_num, fp);

			//print out the token
			printf("* Token Type: %s, Instance: \"%s\", Line Number: %d\n\n", tokenNames[tok->id], tok->instance, tok->line+1);
	
			//free that memory
			free(tok->instance);
			free(tok);*/
		}

		
		if(tokens[place] != '\0'){ //means there could be another token

			while(tokens[place] != '\0'){ //set next tokens equal to rest of tokens array
				next_token[next_place] = tokens[place];
				next_place++;
				place++;
			}

			//set laster character in next tokens array to null
			next_token[next_place] = '\0';

			//send possible next_token to tokens function
			find_tokens(next_token, line_num, fp);
		}
		
	}

	return;
}

TOKEN *scan_tok(char word[MAX], int line_num, FILE *fp){ //take in possibly token and line number

	//create token structure
	TOKEN *token = NULL;

	int current_state = 0; //start with initial state

	int count = 0; //used to loop though token
	

	//NOTE DFA_table values are defined in table.h
	//The rows of the DFA_table 2D array are the states s0 through s7
	//The columns of the DFA_table 2D array defined what state you needd to go to (final state, error state, or another state)
	
	if(feof(fp)){ //check for EOF first 
		current_state = DFA_table[0][20];
	}

	if(current_state == 0){ //first check initial state

			if(isalpha(word[count])){ //most likely identifier or keyword
				current_state = DFA_table[0][0]; //means at s0 state go to s1 state 
			}

			if(isdigit(word[count])){ //most likely a number
				current_state = DFA_table[0][1]; //means at s0 state go to s2 state
			}
			
			//then check for single operators
			//DFA_table says which state to go to
			//so I set the current state equal to the value associated with the character

			if(word[count] == '<'){
				current_state = DFA_table[0][2]; 
			}
			
			if(word[count] == '>'){
				current_state = DFA_table[0][3];
			}
			
			if(word[count] == '!'){
				current_state = DFA_table[0][5];
			}
			
			if(word[count] == '='){
				current_state = DFA_table[0][4];
				
			}
			if(word[count] == ':'){
				current_state = DFA_table[0][6];
				
			}
			if(word[count] == '+'){
				current_state = DFA_table[0][7];
				
			}
			if(word[count] == '-'){
				current_state = DFA_table[0][8];
				
			}
			if(word[count] == '*'){
				current_state = DFA_table[0][9];
				
			}
			if(word[count] == '/'){
				current_state = DFA_table[0][10];
				
			}
			if(word[count] == '.'){
				current_state = DFA_table[0][11];
				
			}
			if(word[count] == '('){
				current_state = DFA_table[0][12];
				
			}
			if(word[count] == ')'){
				current_state = DFA_table[0][13];
				
			}
			if(word[count] == ','){
				current_state = DFA_table[0][14];
				
			}
			if(word[count] == '{'){
				current_state = DFA_table[0][15];
				
			}
			if(word[count] == '}'){
				current_state = DFA_table[0][16];
				
			}
			if(word[count] == ';'){
				current_state = DFA_table[0][17];
				
			}
			if(word[count] == '['){
				current_state = DFA_table[0][18];
				
			}
			if(word[count] == ']'){
				current_state = DFA_table[0][19];
				
			}

			//**************************************************
			//set EOF token later
			
	}
	
	if(current_state == 0){
		//means state has not changed which means not in alphabet
		current_state = DFA_table[0][21]; //set to error
	}
	
	
	
	count++; //add the count to look at next character
	
	//then we loop until we have reached an error state or final state 
	while(current_state < 1000 && current_state > 0){ //means not final, error, or initial state
		

		if(current_state == 1){ //means possible identifier or keyword
			if(isalpha(word[count]) || isdigit(word[count])){ //check if number or letter
				current_state = DFA_table[1][1]; //set the current state
			}
			else	//means an identifier or keyword
				current_state = DFA_table[1][2];
			
			
		}
		
		if(current_state == 2){ //means possible number
			if(isdigit(word[count])) //check if number
				current_state = DFA_table[2][1];
			else //means a number
				current_state = DFA_table[2][2];
		}
		
		if(current_state == 3){ //means possible <=<
			if(word[count] == '='){ //means initial state was '<' so check for '='

				//since we have a < we need to add one to the count to move to next state
				current_state = DFA_table[3][4];
				count++;
			}
			else{
				current_state = DFA_table[3][0]; //which should be error
			}
		}
		
		if(current_state == 4){ //means possible <=<
			if(word[count] == '<') //means states before had '<' and '=' so check for another '<'
				current_state = DFA_table[4][2];
			else
				current_state = DFA_table[4][0]; //which should be error
		}
		
		if(current_state == 5){ //means possible >=>
			if(word[count] == '=') { //check for '='
				current_state = DFA_table[5][4];
				//since we have a < we need to add one to the count to move to next state
				count++;
			}
			else
				current_state = DFA_table[5][0]; //which should be error		
		}
		
		if(current_state == 6){//means possible >=>

			if(word[count] == '>') //means states before had '>' and '=' so check for another '>'
				current_state = DFA_table[6][3];
			else 
				current_state = DFA_table[6][0]; // which should be error
		}
		
		if(current_state == 7){ //means possible !!
			if(word[count] == '!') //means state before had '!' so check for another '!'
				current_state = DFA_table[7][5];
			else 
				current_state = DFA_table [7][0];//which should be error
		}
		
		
		count++;//used to check next character
	}
	
	


	if(current_state > 1000){ //means we have reached a final state 
		
		//malloc for a token structure
		token = malloc(sizeof(TOKEN));
		token->instance = malloc(sizeof(char*));
	

		//check for EOF token
		if(current_state == 5000){
			token->line = line_num;
			strcpy(token->instance, "EOF");
			token->id = 29;
			return token;
		}
	
		if(current_state == 1001){ //means we have identifier or keyword token
			//check for keywords and set token
			if(strcmp(word, "BEGIN") == 0){
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 2;
				return token;
			}
			if(strcmp(word, "END") == 0){
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 3;
				return token;
			}
			if(strcmp(word, "IF") == 0){
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 4;
				return token;
			}
			if(strcmp(word, "FOR") == 0){
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 5;
				return token;
			}
			if(strcmp(word, "VOID") == 0){
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 6;
				return token;
			}
			if(strcmp(word, "VAR") == 0){
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 7;
				return token;
			}
			if(strcmp(word, "RETURN") == 0){
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 8;
				return token;
			}
			if(strcmp(word, "INPUT") == 0){
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 9;
				return token;
			}
			if(strcmp(word, "OUTPUT") == 0){
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 10;
				return token;
			}


			//now that we checked for keywords
			//we know that it has to be an identifier
			//so set token as identifier

			token->line = line_num;
			strcpy(token->instance, word);
			token->id = 0;
			return token;
		} //end if checking for keyword/identifier token
	
	
		if(current_state == 2002){ //means we have a number token
			//set number token
			token->line = line_num;
			strcpy(token->instance, word);
			token->id = 1;
			return token;

		} //end if checking for number token
		
		if(current_state >= 3000){ 
			//means we have some SINGLE operator or SINGLE delimeter token
			
			//check numbers 3000 ~ 3014 and set token

			if(current_state == 3000){ //means we have '=' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 11;
				return token;
			}
			if(current_state == 3001){ //means we have ':' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 15;
				return token;
			}
			if(current_state == 3002){ //means we have '+' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 16;
				return token;
			}
			if(current_state == 3003){ //means we have '-' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 17;
				return token;
			}
			if(current_state == 3004){ //means we have '*' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 18;
				return token;
			}
			if(current_state == 3005){ //means we have '/' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 19;
				return token;
			}
			if(current_state == 3006){ //means we have '.' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 20;
				return token;
			}
			if(current_state == 3007){ //means we have '(' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 21;
				return token;
			}
			if(current_state == 3008){ //means we have ')' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 22;
				return token;
			}
			if(current_state == 3009){ //means we have ',' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 23;
				return token;
			}
			if(current_state == 3010){ //means we have '{' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 24;
				return token;
			}
			if(current_state == 3011){ //means we have '}' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 25;
				return token;
			}
			if(current_state == 3012){ //means we have ';' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 26;
				return token;
			}
			if(current_state == 3013){ //means we have '[' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 27;
				return token;
			}
			if(current_state == 3014){ //means we have ']' token
				//set token
				token->line = line_num;
				strcpy(token->instance, word);
				token->id = 28;
				return token;
			}

			
		}
		
		if (current_state == 4000){
			// we have <=< token
			token->line = line_num;
			strcpy(token->instance, word);
			token->id = 13;
			return token;
		}
		
		if (current_state == 4001){
			// we have >=> token
			token->line = line_num;
			strcpy(token->instance, word);
			token->id = 12;
			return token;

		}
		
		if (current_state == 6000){
			// we have !! token 
			token->line = line_num;
			strcpy(token->instance, word);
			token->id = 14;
			return token;
		}
		
	} //end final state if


	if(current_state < 0){ //means we have an error somewhere
		//report error then exit
		printf("ERROR: \"%c\" NOT IN ALPHABET! Located at line: %d\n\n", word[0], line_num+1);
		exit(0);
	}


	if(current_state < 1000){//UNKNOWN ERROR
		printf("UNKNOWN ERROR!\n\n");
		exit(0);	
	}


	return token;

}


#endif