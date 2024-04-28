#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct DAGNode {
	struct DAGNode *left;
	struct DAGNode *right;
	char *id;
} DAGNode;

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

DAGNode *new_node(char *id) {
	DAGNode *node = calloc(1, sizeof(*node));
	if (!node) return NULL;
	node -> id = id;
	node -> left = NULL;
	node -> right = NULL;
	return node;
}

DAGNode *get_node(Expression *expr) {
	if (!expr) return NULL;
	DAGNode *node = calloc(1, sizeof(*node));
	if (!node) return NULL;
	node -> id = expr -> lhs;
	node -> left = new_node(expr -> arg1);
	node -> right = new_node(expr -> arg2);
	return node;
}

int node_eq(DAGNode *self, DAGNode *other) {
	if (!self || !other) return 0;
	return strcmp(self -> id, other -> id) == 0;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Usage: ./a.out [EXPRESSIONS]");
		printf("Example: ./a.out d=a+b");
		return 1;
	}

	Expression *exprs = calloc(argc - 1, sizeof(Expression));
	if (!exprs) exit(1);
	for (int i = 0; i < argc - 1; i++) {
		Expression *res = parse_expression(exprs + i, argv[i + 1]);
		if (res == NULL) {
			printf("Failed to parse expression!\n");
			exit(1);
		}
		exprs[i] = *res;
	}

	DAGNode **nodes = calloc(argc - 1, sizeof(DAGNode *));
	for (int i = 0; i < argc - 1; i++) {
		DAGNode *res = get_node(&exprs[i]);
		if (!res) {
			printf("Failed to construct expression!\n");
			exit(1);
		}
		nodes[i] = res;
	}

	for (int i = 0; i < argc - 1; ++i) {
		for (int j = 0; j < argc - 1; ++j) {
			if (i == j) continue;
			if (node_eq(nodes[i] -> left, nodes[j])) {
				nodes[i] -> left = nodes[j];
			}
			if (node_eq(nodes[i] -> right, nodes[j])) {
				nodes[i] -> right = nodes[j];
			}
		}
	}

	printf("DAG Table:\n");
	for (int i = 0; i < argc - 1; ++i)
		printf("Head: %s\t\tLeft: %s\t\tRight: %s\n",
		 nodes[i] -> id,
		 nodes[i] -> left -> id,
		 nodes[i] -> right -> id);

	free(exprs);
	for (int i = 0; i < argc; ++i) {
		free(nodes[i]->right);
		free(nodes[i]->left);
		free(nodes[i]);
	}
	free(nodes);
	return 0;
}
