#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char lhs;
	char arg1;
	char arg2;
	bool useful;
} Exp;

int parse_expression(Exp *expr, char *line) {
	if (expr == NULL || line == NULL) return -1;
	expr -> lhs = line[0];
	expr -> arg1 = line[2];
	expr -> arg2 = line[4];
	return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: ./a.out [EXPRESSIONS]\n");
        return 1;
    }

    int len = argc - 1;
    char **lines = argv + 1;
    Exp *exprs = calloc(len, sizeof(Exp));
    if (exprs == NULL)
        return 1;

    for (int i = 0; i < len; i++) {
        if (parse_expression(&exprs[i], lines[i]) < 0) {
			printf("Failed to parse expression: %s\n", lines[i]);
			exit(1);
		}
    }

	// Dead Code Elimination
	for (int i = 0; i < len; i++) {
		bool useful = false;
		for (int j = 0; j < len; j++) {
			if (i == j) continue;
			if (exprs[i].lhs == exprs[j].arg1 || exprs[i].lhs == exprs[j].arg2) {
				useful = true;
			}
		}
		exprs[i].useful = useful;
	}

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (i == j) continue;
			if (exprs[i].lhs == exprs[j].arg1) {
				exprs[j].arg1 = exprs[i].lhs;
			}
			if (exprs[i].lhs == exprs[j].arg2) {
				exprs[j].arg2 = exprs[i].lhs;
			}
		}
	}

	printf("Optimization of Three Code Expressions\n");
	for (int i = 0; i < len; i++) {
		if (exprs[i].useful) {
			printf("LHS: %c\t\tARG1: %c\t\tARG2: %c\n", exprs[i].lhs, exprs[i].arg1, exprs[i].arg2);
		}
	}

    free(exprs);
    return 0;
}
