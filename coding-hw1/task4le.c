#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(int argc, char * argv[]) {
	printf("task 4 for execle starts with pid:%d\n", (int)getpid());
	int rc = fork();
	if(rc<0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	if(rc == 0) {
		printf("child process with pid:%d started\n", (int)getpid());
		char *envp[] = {"MYVAR=HelloWorld2",NULL};
		execle("/usr/bin/printenv", "printenv", (char *)NULL, environ);
		perror("execle failed");
		exit(1);
	}
	if(rc > 0) {
		printf("parent of pid:%d, process with pid:%d started\n", rc, (int)getpid());
		int status;
		wait(&status);
		printf("parent of pid:%d with status: %d, process with pid:%d ended\n", rc, status, (int)getpid());
	}
}