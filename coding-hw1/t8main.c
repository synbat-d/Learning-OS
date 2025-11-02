#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  printf("Hello from main process with pid: %d\n", getpid());
  int pipefd[2];
  if(pipe(pipefd) < 0) {
    perror("pipe failed");
    exit(1);
  }
  int rc1 = fork();
  if (rc1 < 0) {
    perror("fork1 failed");
    exit(1);
  }
  if (rc1 == 0) {
    close(pipefd[0]);
    char wrt_fd[10];
    sprintf(wrt_fd, "%d", pipefd[1]);
    execl("./t8child1", "t8child1", wrt_fd, NULL);
    perror("execl1 failed");
    exit(0);
  }
  int rc2 = fork();
  if (rc2 < 0) {
    perror("fork2 failed");
    exit(1);
  }
  if (rc2 == 0) {
    close(pipefd[1]);
    char read_fd[10];
    sprintf(read_fd, "%d", pipefd[0]);
    execl("./t8child2", "t8child2", read_fd, NULL);
    perror("execl2 failed");
    exit(0);
  }
  close(pipefd[0]);
  close(pipefd[1]);
  printf("Goodbye from main process with pid: %d\n", getpid());
  waitpid(rc1, NULL, 0);
  waitpid(rc2, NULL, 0);
  printf("Both child process finished\n");
  exit(0);
}
