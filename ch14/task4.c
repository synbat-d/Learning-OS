#include <stdio.h>
#include <stdlib.h>

int main() {
	int* mirror = malloc(sizeof(int*));
	printf("some pointer called mirror adress: %p\n", mirror);
	printf("some pointer called mirror content: %d\n", *mirror);
	*mirror = 27;
	printf("some pointer called mirror after setting some content: %d\n", *mirror);
	return 0;
}