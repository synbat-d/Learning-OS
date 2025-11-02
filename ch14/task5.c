#include<stdio.h>
#include<stdlib.h>

int main() {
	printf("start of task5 program\n");
	int* data = (int*)malloc(100*sizeof(int));
	
	printf("synbat-> allocated memory to data\n");
	
	data[66] = 5;
	
	printf("synbat-> set data[66] to zero\n");
	
	int * middle = &(data[50]);
	free(middle);
	printf("synbat-> value of data[66] %d\n", data[66]);
	return 0;
}