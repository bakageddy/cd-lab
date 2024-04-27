%{
#include <stdio.h>
%}

%token NUMBER ID
%left '+' '-' '*' '/'

%%
expr: expr '+' expr
	| expr '-' expr
	| expr '*' expr
	| expr '/' expr
	| '(' expr ')'
	| NUMBER
	| ID
	| '-' NUMBER
	| '-' ID
	;
%%

void main(void) {
	printf("Enter a valid expression: ");
	yyparse();
	printf("It's a valid expression!\n");
}

int yyerror(char *s) {
	printf("It's a invalid expression!\n");
}
