#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
// Created by synba on 18.03.2025.


int main(int argc, char *argv[]){
  printf("This is task8 starting with pid %d\n", getpid());
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    perror("pipe failed");
    exit(1);
  }
  int rc1 = fork();
  if (rc1 < 0) {
    perror("fork1 failed");
    exit(1);
  }
  if (rc1 == 0) {
    printf("This is first child process rc1 with pid %d\n", getpid());
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    printf("Hello from child 1 with pid %d\n", getpid());
    fflush(stdout);
    exit(0);
  }
  int rc2 = fork();
  if (rc2 < 0) {
    perror("fork2 failed");
    exit(1);
  }
  if (rc2 == 0) {
    printf("This is second child process rc2 with pid %d\n", getpid());
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    printf("In this second child i will now read pipe\n");
    char buffer[100];
    read(STDIN_FILENO, buffer, sizeof(buffer));
    printf("Child 2 received: %s\n", buffer);
    exit(0);
  }
  close(pipefd[0]);
  close(pipefd[1]);
  printf("This is again just a parent process with pid: %d\n", getpid());
  waitpid(rc1, NULL, 0);
  waitpid(rc2, NULL, 0);
  printf("Both children finished\n");
  exit(0);
}
