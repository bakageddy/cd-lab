#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
} Type;

const static char* types[] = {"char", "int", "float", "double"};

typedef struct {
	Type type;
	char* symbols;
	long long address;
	size_t size;
} Expr;

void print_expr(Expr* expr) {
	printf("Type: %s\t\t|Size: %zu\t\t|Address: %llu\t\t|Symbols: %s\n",
			types[expr -> type],
			expr -> size,
			expr -> address,
			expr -> symbols);
}

int parse_expr(Expr* dst, const char* expr, size_t expr_len) {
	// input: "float a, b, c" => float, a, b, c
	
	// Extract keyword
	char* type = strchr(expr, ' ');
	assert(type != NULL);
	long type_size = type - expr;
	if (memcmp("float", expr, type_size) == 0) {
		dst -> type = FLOAT;
		dst -> size = sizeof(float);
	} else if (memcmp("int", expr, type_size) == 0) {
		dst -> type = INT;
		dst -> size = sizeof(int);
	} else if (memcmp("char", expr, type_size) == 0) {
		dst -> type = CHAR;
		dst -> size = sizeof(char);
	} else if (memcmp("double", expr, type_size) == 0) {
		dst -> type = DOUBLE;
		dst -> size = sizeof(double);
	} else {
		return -1;
	}

	// Extract Symbols
	assert(type[1] != '\0');
	char *symbols = type + 1;
	dst -> symbols = symbols;
	dst -> address = (long long) symbols;
	return 0;
}

int main(int argc, char** argv) {
	if (argc == 1) {
		printf("USAGE: %s <Expression>\n", __FILE__);
		exit(-1);
	}

	Expr foo = {
		.size = 0,
		.symbols = NULL,
		.type = INT,
	};

	for (int i = 1; i < argc; i++) {
		int result = parse_expr(&foo, argv[i], strlen(argv[i]));
		if (result != -1) {
			print_expr(&foo);
		} else {
			exit(-1);
		}
	}
	return 0;
}
