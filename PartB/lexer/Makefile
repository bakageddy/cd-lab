all: lexer.l
	@flex lexer.l
	@gcc lex.yy.c -o output -ll
	@cat test.c | ./output
