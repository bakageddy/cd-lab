#include "lexer.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
	if (argc == 1) {
		printf("USAGE: %s <filepath>\n", __FILE__);
		exit(-1);
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		printf("Failed to open file: %s %s\n", argv[1], strerror(errno));
		exit(-1);
	}

	struct stat st;
	if (fstat(fd, &st) == -1) {
		printf("Failed to stat file: %s %s\n", argv[1], strerror(errno));
		exit(-1);
	}
	size_t file_size = st.st_size + 1;
	char *file_contents = malloc(sizeof(char) * file_size);

	if (read(fd, file_contents, file_size) == -1) {
		printf("Failed to read file: %s %s\n", argv[1], strerror(errno));
		exit(-1);
	}

	file_contents[file_size - 1] = '\0';
	lexer_t* lexer = init_lexer(file_contents, file_size - 1);

	do {
		Token* tok = next_token(lexer);
		print_token(tok);
		free(tok);
	} while (lexer -> cursor < lexer -> len);
	puts("");

	free(lexer);
	free(file_contents);
	return 0;
}
