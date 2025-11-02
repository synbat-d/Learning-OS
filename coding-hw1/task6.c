#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char* argv[]) {
	
	printf("This is task5 program started running\n");
	printf("ProcessId of this before fork: %d\n", (int)getpid());
	srand(time(0));
	int rc = fork();
	if(rc<0){
		perror("Fork failed\n");
		exit(1);
	}
	if(rc==0){
		printf("This child process with pid:%d\n", (int)getpid());
		int sum = 0;
		for(int i=0; i<100000; i++){
			sum += rand()%25;
		}
		printf("We get random sum of: %d\n", sum);
		exit(0);
	}
	if(rc>0) {
		int status;
		int rc_wait = waitpid(rc, &status, 0);
		if(rc_wait==-1){
			perror("Wait failed\n");
			exit(1);
		}
		printf("This is again parent process with pid:%d\n", (int)getpid());
		printf("So it is parent of process with pid:%d\n", (int)rc);
		printf("value of status %d\n", status);
		printf("value of rc_wait %d\n", rc_wait);
		exit(0);
	}
	
}