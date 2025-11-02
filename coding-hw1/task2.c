#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv []) {
	
	srand(time(NULL));
	
	int rc = fork();
	if(rc<0) {
		fprintf(stderr, "fork failedd\n");
		exit(1);
	} else if(rc == 0){
		close(STDOUT_FILENO);
	    open("./task2-output.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
		
		for(int i=0; i<10; i++){
			printf("This is child pid: %d\n", getpid());
			usleep(rand() % 1000000);
		}
	}
	else {
		for(int i=0; i<10; i++){
			printf("This is parent pid: %d, parent of son(pid:%d)\n", getpid(), rc);
			usleep(rand() % 1000000);
		}
		wait(NULL);
	}
	return 0;
}