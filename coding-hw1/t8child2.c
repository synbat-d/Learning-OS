//
// Created by synba on 18.03.2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Usage: ./child2 <command>\n");
        exit(EXIT_FAILURE);
    }
    int read_fd = atoi(argv[1]);
    dup2(read_fd, STDIN_FILENO);
    close(read_fd);
    char buffer[100];
    read(STDIN_FILENO, buffer, 100);
    printf("Hello from child 2 with pid %d\n", getpid());
    printf("Child 2 received message: %s\n", buffer);
    exit(0);
}