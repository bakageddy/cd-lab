CC=gcc
BIN=output

.PHONY: all

all: lex.l parser.y
	@flex lex.l
	@yacc parser.y -d
	$(CC) lex.yy.c y.tab.h y.tab.c -ll -o $(BIN)

run: $(BIN)
	./$(BIN)
