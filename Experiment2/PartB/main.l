%{
#include <stdio.h>
%}

%%
int|float|double|void|short|char|string {
	printf("Keyword: %s\n", yytext);
}

[a-zA-Z][a-zA-Z0-9]* {
	printf("Identifier: %s\n", yytext);
}

; {
	printf("Semi Colon: \';\'");
}

\= {
	printf("Equal: =\n");
}

[\+\-\*\/] {
	printf("Arithmetic Operator: %s\n", yytext);
}

[0-9]+ {
	printf("Number: %s\n", yytext);
}

%%

int main(void) {
	yylex();
	printf("Lexing done!\n");
	return 0;
}
