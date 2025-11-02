#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    int pipefd[2];
    // Create a pipe: pipefd[0] is the read end; pipefd[1] is the write end.
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) { // Child process
        // Close the read end; child will write a signal.
        close(pipefd[0]);
        printf("hello\n");
        fflush(stdout);  // Ensure output is flushed immediately.

        // Write a byte into the pipe to signal the parent.
        if (write(pipefd[1], "x", 1) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        // Close the write end.
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    }
    else { // Parent process
        char buf;
        // Close the write end; parent will wait by reading.
        close(pipefd[1]);

        // Block until a byte is read from the pipe.
        if (read(pipefd[0], &buf, 1) <= 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        // Close the read end.
        close(pipefd[0]);

        // Now that the parent has received the signal, print "goodbye".
        printf("goodbye\n");
        fflush(stdout);
    }
    return 0;
}
