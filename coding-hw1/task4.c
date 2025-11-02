#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {  // Child process
        printf("child (pid: %d)\n", (int) getpid());

        char *myargs[3];
        myargs[0] = strdup("ls");
        myargs[1] = NULL;  // List all files instead of a specific one
        myargs[2] = NULL;

        execvp(myargs[0], myargs);

        // If execvp() fails, print an error and exit
        perror("execvp failed");
        free(myargs[0]);  // Free memory before exiting
        exit(1);
    } else {  // Parent process
        int status;
        int rc_wait = wait(&status);
        if (rc_wait == -1) {
            perror("wait failed");
            exit(1);
        }

        printf("parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
    }

    return 0;
}
