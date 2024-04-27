#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>

// Comment

int main(int argc, char** argv) {
	if (argc == 1) {
		printf("Usage: %s [FILE]\n", __FILE__);
		exit(-1);
	}

	char* filename = argv[1];
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		printf("Error Opening file: %s\n", strerror(errno));
		exit(-1);
	}

	struct stat st;
	fstat(fd, &st);
	printf("Size: %lu\n", st.st_size);

	char* contents = malloc(sizeof(char) * st.st_size);
	assert(contents != NULL);

	read(fd, contents, st.st_size);

	char *found = NULL;
	while (contents != NULL) {
		char* foo = strsep(&contents, "\n");
		found = strstr(foo, "//");
		if (found != NULL)
			printf("%s\n", foo);
	}

	free(contents);
	close(fd);
	return 0;
}
