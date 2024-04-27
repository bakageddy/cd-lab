// Write a program to define a array size at runtime

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int len = 0;
	printf("Enter size of array: ");
	scanf("%d", &len);

	// Calloc better than malloc :)
	int *array = calloc(len, sizeof(int));
	if (!array) return 1;

	for (int i = 0; i < len; i++) {
		printf("Enter element at %d: ", i);
		scanf("%d", array + i);
	}

	printf("Elements: ");
	for (int i = 0; i < len; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");

	free(array);
	return 0;
}
