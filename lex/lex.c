#include "lex.h"

#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>






Token* lex(FILE* fp){
	char c = getc(fp),*dlm;

	while(isemptyspace(c)) c = getc(fp);

	if(c == EOF){
		return create_token(EOI,NULL);
	}


	if(isdelimitter(c)){
		dlm = (char*)malloc(sizeof(char)*2);
		dlm[0] = c;
		dlm[1] = '\0';
		return create_token(DLM,dlm);
	}

	if(isalpha(c) || c == '_'){
		return isIdentifier(fp,c);
	}

	if(isdigit(c) || c == '.'){
		return isNumeric(fp,c);
	}

	if(c == '"'){
		return isString(fp,c);
	}

	if(c == '\''){
		return isChar(fp,c);
	}

	if(isop(c)){
		return isOperator(fp,c);
	}

	return NULL;
} 

Token* isOperator(FILE* fp,char c){
	char* str = (char*) malloc(sizeof(char)*(VALUE_BUFFER_SIZE+1));
	int i=0;

	str[i] = c;
	i++;
	switch(c){
		case '+':{
			c = getc(fp);
			if( c == '+' || c == '='){
				str[i] = c;
				str[i+1] = '\0';
				return create_token(OPR,str);
			}
			ungetc(c,fp);
			return create_token(OPR,str);
			break;
		}

		case '-':{
			c = getc(fp);
			if( c == '-' || c == '='){
				str[i] = c;
				str[i+1] = '\0';
				return create_token(OPR,str);
			}
			ungetc(c,fp);
			return create_token(OPR,str);
			break;
		}

		case '&':{
			c = getc(fp);
			if( c == '&' || c == '='){
				str[i] = c;
				str[i+1] = '\0';
				return create_token(OPR,str);
			}
			ungetc(c,fp);
			return create_token(OPR,str);
			break;
		}

		case '|':{
			c = getc(fp);
			if( c == '|' || c == '='){
				str[i] = c;
				str[i+1] = '\0';
				return create_token(OPR,str);
			}
			ungetc(c,fp);
			return create_token(OPR,str);
			break;
		}

		default: {
			c = getc(fp);
			if(c == '='){
				str[i] = c;
				str[i+1] = '\0';
			}else{
				ungetc(c,fp);
				str[i] = '\0';
			}

			return create_token(OPR,str);
		}
	}
}

Token* isChar(FILE* fp,char c){
	char* str = (char*) malloc(sizeof(char)*(VALUE_BUFFER_SIZE+1));
	int i=0,state=0;

	while(1){
		if(i>VALUE_BUFFER_SIZE){
			printf("value buffer overflow: check value buf length [MAX_VALUE_BUF_LEN=%d]\n",VALUE_BUFFER_SIZE);
			exit(1);
		}

		str[i] = c;
		i++;

		c = getc(fp);

		switch(state){
			case 0:{
				if(c == '\\'){
					state = 2;
				}else if(c != EOF ){
					state = 1;
				}else{
					ungetc(c,fp);
					return NULL;
				}
				break;
			}

			case 1:{
				if(c == '\''){
					state = 3;
				}else{
					ungetc(c,fp);
					return NULL;
				}
				break;
			}

			case 2:{
				if(c == '\\' || c == '\''){
					state = 1;
				}else{
					ungetc(c,fp);
					return NULL;
				}
				break;
			}

			case 3:{
				ungetc(c,fp);
				str[i] = '\0';
				return create_token(CHR,str);
				break;
			}


		}
	}
}


Token* isString(FILE* fp,char c){
	char* str = (char*) malloc(sizeof(char)*(VALUE_BUFFER_SIZE+1));
	int i=0,state=0;

	while(1){
		if(i>VALUE_BUFFER_SIZE){
			printf("value buffer overflow: check value buf length [MAX_VALUE_BUF_LEN=%d]\n",VALUE_BUFFER_SIZE);
			exit(1);
		}

		str[i] = c;
		i++;

		c = getc(fp);

		switch(state){
			case 0:{
				if(c == '"'){
					state = 1;
				}else if(c == '\\'){
					state = 2;
				}else if(c != EOF){
					state = 0;
				}else{
					ungetc(c,fp);
					return NULL;
				}
				break;
			}

			case 1:{
				ungetc(c,fp);
				str[i] = '\0';
				return create_token(STR,str);
				break;
			}

			case 2:{
				if(c == '\\' || c == '"'){
					state = 0;
				}else{
					ungetc(c,fp);
					return NULL;
				}
				break;
			}
		}
	}
}

Token* isNumeric(FILE* fp,char c){
	char* str = (char*) malloc(sizeof(char)*(VALUE_BUFFER_SIZE+1));
	int i=0,state=0;
	// bool safe=true,flag=false,isint=true; // safe to return the current token
	// char temp;
	if(c == '.'){
		state = 1;
	}

	while(1){
		if(i>VALUE_BUFFER_SIZE){
			printf("value buffer overflow: check value buf length [MAX_VALUE_BUF_LEN=%d]\n",VALUE_BUFFER_SIZE);
			exit(1);
		}

		str[i] = c;
		i++;

		c = getc(fp);

		switch(state){
			case 0: {
				if(isdigit(c)){
					// temp = getc(fp);
					// safe = !(temp == '.' || temp == 'e' || temp == 'E');
					// ungetc(temp,fp);
					state = 0; 
				}else if(c == '.'){
					state = 1;
				}else if(c == 'e' || c == 'E'){
					state = 6;
				}else{
					str[i] = '\0';
					ungetc(c,fp);
					return create_token(NUM,str);
				}
				break;
			}

			case 1:{
				if(isdigit(c)){
					// temp = getc(fp);
					// safe = !(temp == 'e' || temp == 'E');
					// ungetc(temp,fp);
					state = 2;
				}else{
					ungetc(c,fp);
					return NULL;
				}
				break;
			}

			case 2:{
				if(isdigit(c)){
					// temp = getc(fp);
					// safe = !(temp == 'e' || temp == 'E');
					// ungetc(temp,fp);
					state = 2;
				}else if(c == 'e' || c == 'E'){
					state = 3;
				}else{
					ungetc(c,fp);
					str[i] = '\0';
					return create_token(REAL,str);
				}
				break;
			}

			case 3:{
				if(isdigit(c)){
					state = 4;
				}else if(c == '-' || c == '+'){
					state = 5;
				}else{
					ungetc(c,fp);
					return NULL;
				}
				break;
			}

			case 4:{
				if(isdigit(c)){
					state = 4;
				}else{
					ungetc(c,fp);
					str[i] = '\0';
					return create_token(REAL,str);
				}
				break;
			}

			case 5:{
				if(isdigit(c)){
					state = 4;
				}else{
					ungetc(c,fp);
					return NULL;
				}
				break;
			}

			case 6:{
				if(isdigit(c)){
					state = 7;
				}else if(c == '+' || c == '-'){
					state = 8;
				}else{
					ungetc(c,fp);
					return NULL;
				}
				break;
			}

			case 7:{
				if(isdigit(c)){
					state = 7;
				}else{
					ungetc(c,fp);
					str[i] = '\0';
					return create_token(NUM,str);
				}
				break;
			}

			case 8:{
				if(isdigit(c)){
					state = 7;
				}else{
					ungetc(c,fp);
					return NULL;
				}
				break;
			}
		}

	}




}

Token* isIdentifier(FILE* fp,char c){
	char* str = (char*) malloc(sizeof(char)*(VALUE_BUFFER_SIZE+1));
	int i=0;
	do{

		if(i>VALUE_BUFFER_SIZE){
			printf("value buffer overflow: check value buf length [MAX_VALUE_BUF_LEN=%d]\n",VALUE_BUFFER_SIZE);
			exit(1);
		}

		str[i] = c;
		i++;
		c = getc(fp);
		if(c == EOF){
			str[i] = '\0';
			return create_token(isKeyword(str)?KW:ID,str);
		}
	}while(isalnum(c));

	ungetc(c,fp);
	str[i] = '\0';
	return create_token(isKeyword(str)?KW:ID,str);
}



