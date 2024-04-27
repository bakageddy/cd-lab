%{
#include <stdio.h>
%}

%token LETTER DIGIT

%%
variable: LETTER|LETTER rest
		;
rest: LETTER rest
	| DIGIT rest
	| LETTER
	| DIGIT;
%%

void main() {
	printf("Enter a variable name: ");
	yyparse();
	printf("It's a valid variable!\n");
}

int yyerror(char *s) {
	printf("It's a invalid variable!\n");
	return 1;
}
