// Write a program that frees a block of memory

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int len = 0;
	printf("Enter length: ");
	scanf("%d", &len);

	int *array = calloc(len, sizeof(int));
	if (!array) {
		printf("Failed to allocate memory!\n");
		return 1;
	}

	for (int i = 0; i < len; i++) {
		printf("Element @ %d: ", i);
		scanf("%d", &array[i]);
	}

	printf("Elements: ");
	for (int i = 0; i < len; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");

	printf("Freeing allocated memory!\n");
	free(array);
	return 0;
}
