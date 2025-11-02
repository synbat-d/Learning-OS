#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int x = 152;
	printf("hello (pid:%d) and x value: %d \n", (int) getpid(), x);
	int rc = fork();
	if(rc<0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if(rc == 0) {
		//x = 165;
		printf("child (pid:%d), and child's x value:%d \n", (int) getpid(), x);
	}
	else {
		x = 175;
		printf("parent of %d (pid:%d) and parent's x value: %d \n", rc, (int) getpid(), x);
	}
	return 0;
}