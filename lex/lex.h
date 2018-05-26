#ifndef LEX_H
#define LEX_H


#include <stdio.h>
#include "token.h"

#define VALUE_BUFFER_SIZE 50


Token* lex(FILE* fp);



Token* isIdentifier(FILE* fp,char c);
Token* isNumeric(FILE* fp,char c);
Token* isString(FILE* fp,char c);
Token* isChar(FILE* fp,char c);
Token* isOperator(FILE* fp,char c);




#endif