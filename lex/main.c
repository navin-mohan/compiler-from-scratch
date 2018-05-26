#include "lex.h"
#include <stdio.h>
#include "token.h"
#include <stdbool.h>
#include <stdlib.h>


int main(int argc,char** argv){
	FILE* fp = fopen(argv[1],"r");
	FILE* outf = fopen(argv[2],"w");
	Token* t = NULL;

	while(!feof(fp)){
		t = lex(fp);
		if(t == NULL){
			printf("Error in code\n");
			exit(1);
		}
		write_token(t,outf);
	}
	

	return 0;
}