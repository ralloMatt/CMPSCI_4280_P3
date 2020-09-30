#ifndef TOKEN_H
#define TOKEN_H
  
enum tokenID {ID_tk, NUM_tk, BEG_tk, END_tk, IF_tk, FOR_tk, VOID_tk, VAR_tk,
				RET_tk, INP_tk, OUT_tk, EQU_tk, GREAT_EQU_GREAT_tk, 
				LESS_EQU_LESS_tk, TWOEXC_tk, COLON_tk, PLUS_tk, MINUS_tk,
				TIMES_tk, DIV_tk, DOT_tk, LPAR_tk, RPAR_tk, COMMA_tk, 
				LCURL_tk, RCURL_tk, SEMICOL_tk, LBRA_tk, RBRA_tk, EOF_tk} ;

static char *tokenNames[30]= {"Identifier", "Number", "BEGIN keyword", 
						"END keyword", "IF keyword", "FOR keyword",
						"VOID keyword", "VAR keyword", "RETURN keyword",
						"INPUT keyword", "OUTPUT keyword", "Equal operator",
						"GREAT EQUAL GREAT operator", "LESS EQUAL LESS operator",
						"TWO EXCLAMATION operator",
						"COLON operator", "PLUS operator", "MINUS operator",
						"MULTIPLY operator", "DIVIDE operator", "DOT operator",
						"LEFT PARATHESIS operator", "RIGHT PARATHESIS operator",
						"COMMA operator",
						"LEFT CURLY BRACKET operator", "RIGHT CURLY BRACKET operator",
						"SEMI COLON operator", "LEFT BRACKET operator",
						"RIGHT BRACKET operator", "EOF token", };


static char *check_id[30]= { //used to check id of token when needed in paraser (same as enum)
				"ID_tk", "NUM_tk", "BEG_tk", "END_tk", "IF_tk", "FOR_tk", "VOID_tk", "VAR_tk",
				"RET_tk", "INP_tk", "OUT_tk", "EQU_tk", "GREAT_EQU_GREAT_tk", 
				"LESS_EQU_LESS_tk", "TWOEXC_tk", "COLON_tk", "PLUS_tk", "MINUS_tk",
				"TIMES_tk", "DIV_tk", "DOT_tk", "LPAR_tk", "RPAR_tk", "COMMA_tk", 
				"LCURL_tk", "RCURL_tk", "SEMICOL_tk", "LBRA_tk", "RBRA_tk", "EOF_tk" };
					

typedef struct TOKEN{
	enum tokenID id;
	char *instance; 
	int line;
} TOKEN;

#endif 