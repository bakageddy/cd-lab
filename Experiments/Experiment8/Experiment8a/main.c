#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	token *tokens;
} token_vec;

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

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Usage: ./a.out <CODE>\n");
		return 1;
	}
	char *file_path = argv[1];
	char *contents = read_file(file_path);
	if (contents == NULL) {
		return 1;
	}
	free(contents);
	return 0;
}
