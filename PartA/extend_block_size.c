// Write a program that resize's a block of size A to size B

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int len = 0;
	printf("Enter initial length: ");
	scanf("%d", &len);

	int *array = calloc(len, sizeof(int));
	if (!array) return 1;
	for (int i = 0; i < len; i++) {
		printf("Enter element @ %d: ", i);
		scanf("%d", array + i);
	}

	printf("Elements: ");
	for (int i = 0; i < len; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");

	int new_len = 0;
	printf("Enter new length: ");
	scanf("%d", &new_len);
	printf("Resizing block of length : %d to %d\n", len, new_len);

	int *res = realloc(array, sizeof(int) * new_len);
	if (!res) {
		printf("Failed to resize block!\n");
		return -1;
	}
	array = res;

	for (int i = len; i < new_len; i++) {
		printf("Enter element @ %d: ", i);
		scanf("%d", array + i);
	}

	printf("Elements: ");
	for (int i = 0; i < new_len; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	free(array);
	return 0;
}
