#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>
#include <stdio.h>

// tokens
#define EOI  255
#define NUM  254
#define REAL 253
#define OPR  252
#define CHR  251
#define STR  250
#define ID   249
#define DLM  248
#define KW   247

typedef struct
{
	int type;
	char* value;
	
}Token;

// creates a token struct 
Token* create_token(int type,char* val);

// writes a string formated version of the Token to the given stream
void write_token(Token* t,FILE* fp);

// maps the token vales to human readable strings
void map_tok_type_to_str(char* str,int type);


// check if the given char is a delimitter
bool isdelimitter(char c);
// check if the given char is an operator
bool isop(char c);
// check if the given char is an emptyspace
bool isemptyspace(char c);
// check if the given string is a keyword
bool isKeyword(char* str);


#endif