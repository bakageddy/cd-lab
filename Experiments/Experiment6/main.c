#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <fcntl.h>
#include <ctype.h>

#define OPTION_IMPL
#include "option.h"

typedef struct {
	char lhs;
	char rhs[256];
} production;

char *read_file(const char *file_path) {
	int fd = open(file_path, O_RDONLY);
	if (fd == -1) {
		printf("Failed to read file: %s\n", strerror(errno));
		return NULL;
	}
	struct stat st;
	if (fstat(fd, &st) < 0) {
		printf("Failed to get length of file!\n");
		return NULL;
	}
	long file_length = st.st_size;
	char *file_contents = malloc(sizeof(char) * file_length);
	if (file_contents == NULL) return NULL;
	if (read(fd, file_contents, file_length) < 0) {
		printf("Failed to read file!\n");
		return NULL;
	}
	return file_contents;
}

bool is_whitespace(char c) {
	return c == '\n' || c == '\r' || c == ' ' || c == '\t';
}

char* skip_whitespace(char *line, size_t len) {
	if (line == NULL) return 0;
	size_t i = 0;
	while (i < len && *line != '\0') {
		if (is_whitespace(*line)) {
			i += 1;
			line = line + i;
		}
		else break;
	}
	return line;
}


option parse_prod(char *line, size_t len) {
	production p = {0};
	char *non_terminal = skip_whitespace(line, len);
	p.lhs = non_terminal[0];
	if (!isupper(p.lhs)) {
		return none();
	}
	non_terminal += 1;

	len = len - (non_terminal - line);
	char *arrow = skip_whitespace(non_terminal, len);
	if (arrow[0] != '-' || arrow[1] != '>') {
		return none();
	}

	arrow += 2;
	len = len - (arrow - non_terminal);
	char *rule = skip_whitespace(arrow, len);
	for (int i = 0; i < len - 1; i++) {
		p.rhs[i] = rule[i];
	}
	return some(&p);
}

char *get_first(production *ps, size_t n, production p) {
	// TODO
	return NULL;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Usage: ./a.out <PRODUCTION>");
		return 1;
	}
	char *file_path = argv[1];
	char *contents = read_file(file_path);

	char *another = contents;

	while (*another != '\0') {
		char *end = strchr(another, '\n');
		long length = end - another;
		option o = parse_prod(another, length);
		if (is_some(o)) {
			production p = *(production *) o.data;
			printf("LHS:%c RHS:%s\n", p.lhs, p.rhs);
		} else {
			printf("Failed to parse production!\n");
			break;
		}
		another = end + 1;
	}

	free(contents);
	return 0;
}
