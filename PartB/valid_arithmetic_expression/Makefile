CC=gcc
BIN=output

.PHONY: all

all: lexer.l parser.y
	@flex lexer.l
	@yacc parser.y -d
	$(CC) lex.yy.c y.tab.h y.tab.c -ll -o $(BIN)

run: $(BIN)
	./$(BIN)
