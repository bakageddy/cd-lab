all: main.l test.c
	flex --read main.l
	gcc lex.yy.c -o lexer -lfl
	cat test.c | ./lexer
