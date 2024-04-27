// Write a program to identify whether the given statement is a comment or not

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

char *read_from_file(const char *file_path) {
	int fd = open(file_path, O_RDONLY);
	if (fd < 0) {
		printf("Failed to open file: %s\n", strerror(errno));
		return NULL;
	}

	struct stat st;
	if (fstat(fd, &st) < 0) {
		printf("Failed to stat file: %s\n", strerror(errno));
		return NULL;
	}

	size_t file_size = st.st_size;
	char *buf = calloc(file_size, sizeof(char));
	if (!buf) {
		printf("Failed to allocate memory\n");
		return NULL;
	}

	if (read(fd, buf, file_size) < 0) {
		printf("Failed to read file!\n");
		free(buf);
		return NULL;
	}
	close(fd);
	return buf;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Usage: ./a.out [FILENAME]\n");
		exit(1);
	}

	char *filename = argv[1];
	char *buf = read_from_file(filename);
	if (!buf) return 1;

	char *contents = buf;
	while (1) {
		char *line = strsep(&contents, "\n");
		if (line == NULL) break;

		if (strstr(line, "//")) {
			printf("Found comment: %s\n", line);
		}

		if (strstr(line, "/*") || strstr(line, "*/")) {
			printf("Found multiline comment: %s\n", line);
		}
	}
defer:
	if (buf) free(buf);
	return 0;
}
