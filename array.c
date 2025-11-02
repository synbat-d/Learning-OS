#include <stdio.h>

int main(int argc, char *argv[]) {
	int array[1000];
	puts("Hello Array!");
	for(int i=1; i<=1000; i++){
		array[i-1] = i;
	}
	puts("Bye Array!");
	return 0;
}