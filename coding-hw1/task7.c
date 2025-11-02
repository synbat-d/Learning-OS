#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	printf("This is task5 program started running\n");
	printf("ProcessId of this before fork: %d\n", (int)getpid());
	int rc = fork();
	if(rc<0){
		perror("Fork failed\n");
		exit(1);
	}
	if(rc == 0) {
		printf("Before closing stdout: This should print\n");
		fflush(stdout); // Flush to make sure it gets printed
		close(STDOUT_FILENO);
    
		printf("After closing stdout: This will NOT be visible\n");
		fflush(stdout); // This does nothing since stdout is closed
		perror("Flush failed\n");
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