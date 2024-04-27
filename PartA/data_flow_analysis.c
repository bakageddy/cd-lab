// Write a program that performs data flow analysis on the given three address code

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

int live_at(const char *var, const Expression *src) {
	if (strcmp(var, src -> lhs) == 0 || strcmp(var, src -> arg1) == 0 || strcmp(var, src -> arg2) == 0) {
		return 1;
	}
	return 0;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Usage: ./a.out [THREE_ADDRESS_CODE]\n");
		printf("Example Three Address Code: a=b+c\n");
		printf("Example Three Address Code: hi=bye*bye\n");
		exit(1);
	}
	Expression *list = calloc(argc - 1, sizeof(*list));
	if (!list) return 1;

	for (int i = 0; i < argc - 1; i++) {
		Expression *res = parse_expression(list + i, strdup(argv[i + 1]));
		if (!res) {
			printf("Failed to parse expression: %s\n", argv[i + 1]);
		}
		list[i] = *res;
	}

	for (int i = 0; i < argc - 1; i++) {
		Expression a = list[i];
		for (int j = 0; j < argc - 1; j++) {
			Expression b = list[j];
			if (live_at(a.lhs, &b))
				printf("%s is live at expression: %s\n", a.lhs, argv[j + 1]);
			if (live_at(a.arg1, &b))
				printf("%s is live at expression: %s\n", a.arg1, argv[j + 1]);
			if (live_at(a.arg2, &b))
				printf("%s is live at expression: %s\n", a.arg2, argv[j + 1]);
		}
	}

	return 0;
}
