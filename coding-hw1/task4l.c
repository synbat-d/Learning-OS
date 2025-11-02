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
        printf("child (pid: %d) executing ls using execl()\n", (int) getpid());

        execl("/bin/ls", "ls", "-l", (char *)NULL);

        // If execvp() fails, print an error and exit
        perror("execl failed");
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
