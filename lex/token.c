#include "token.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void map_tok_type_to_str(char* str,int type){
	switch(type){
		case EOI: {
			strcpy(str,"EOI");
			break;
		}
		case NUM: {
			strcpy(str,"NUM");
			break;
		}
		case REAL: {
			strcpy(str,"REAL");
			break;
		}
		case OPR: {
			strcpy(str,"OPR");
			break;
		}
		case CHR: {
			strcpy(str,"CHR");
			break;
		}
		case STR: {
			strcpy(str,"STR");
			break;
		}
		case ID: {
			strcpy(str,"ID");
			break;
		}
		case DLM: {
			strcpy(str,"DLM");
			break;
		}

		case KW:{
			strcpy(str,"KW");
			break;
		}
	}
}

void write_token(Token* t, FILE* fp){
	char tok_str[5];
	map_tok_type_to_str(tok_str,t->type);
	fprintf(fp, "<%d:%s:\"%s\">",t->type,tok_str,t->value);
}


Token* create_token(int type,char* val){
	Token* t = (Token*) malloc(sizeof(Token));
	t->type = type;
	t->value = val;

	return t;
}


bool isKeyword(char* str){
	const char keywords[13][30] = {
		"if",
		"else",
		"int",
		"float",
		"char",
		"double",
		"return",
		"break",
		"continue",
		"for",
		"while",
		"do",
		"const"
	};

	for(int i=0;i<13;++i){
		if(strcmp(str,keywords[i]) == 0){
			return true;
		}
	}

	return false;
}

bool isop(char c){
	switch(c){
		case '+':
		case '-':
		case '*':
		case '/':
		case '&':
		case '^':
		case '|':
		case '%':
		case '=':
		case '!':
		case '<':
		case '>':
		case '~': return true;
	}

	return false;
}


bool isdelimitter(char c){
	switch(c){
		case '(':
		case ')':
		case '{':
		case '}':
		case '[':
		case ']':
		case ',':
		case ';': return true;
	}

	return false;
}

bool isemptyspace(char c){
	switch(c){
		case ' ':
		case '\n':
		case '\r': return true;
	}

	return false;
}