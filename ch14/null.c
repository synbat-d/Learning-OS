#include<stdio.h>
#include<stdlib.h>

int main() {
	int* somePointer = NULL;
	printf("Some pointer: %p\n", somePointer);
	printf("Some content of pointer: %d\n", *somePointer);
	return 0;
}