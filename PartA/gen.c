// Write a program that generates target code for the given three address target code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	ADD, SUB, MUL, DIV
} Operation;

typedef struct {
	char *lhs;
	Operation op;
	char *arg1;
	char *arg2;
} Expression;

Expression *parse_expression(Expression *buf, char *line) {
	buf -> lhs = strsep(&line, "=");
	unsigned long arg1len = strcspn(line, "+-/*");
	if (line[arg1len] == '+') {
		buf -> op = ADD;
		buf -> arg1 = strsep(&line, "+");
	} else if (line[arg1len] == '-') {
		buf -> op = SUB;
		buf -> arg1 = strsep(&line, "-");
	} else if (line[arg1len] == '*') {
		buf -> op = MUL;
		buf -> arg1 = strsep(&line, "*");
	} else if (line[arg1len] == '/') {
		buf -> op = DIV;
		buf -> arg1 = strsep(&line, "/");
	} else {
		return NULL;
	}
	buf -> arg2 = line;
	return buf;
}

int gen_asm(FILE *f, Expression *exp) {
	fprintf(f, "ld R0, %s\n", exp -> arg1);
	fprintf(f, "ld R1, %s\n", exp -> arg2);
	switch (exp -> op) {
	case ADD:
		fprintf(f, "add R0, R0, R1\n");
		break;
	case SUB:
		fprintf(f, "sub R0, R0, R1\n");
		break;
	case MUL:
		fprintf(f, "mul R0, R0, R1\n");
		break;
	case DIV:
		fprintf(f, "div R0, R0, R1\n");
		break;
	default:
		return -1;
	}
	fprintf(f, "st %s, R0\n", exp -> lhs);
	return 0;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Usage: ./a.out [THREE_ADDRESS_CODE]\n");
		printf("Example: ./a.out \"one=two+three\"\n");
		exit(1);
	}
	for (int i = 1; i < argc; i++) {
		Expression foo = {0};
		if (!parse_expression(&foo, argv[i])) continue;
		gen_asm(stdout, &foo);
	}
	return 0;
}
