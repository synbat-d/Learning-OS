//
// Created by synba on 18.03.2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if(argc < 2) {
    fprintf(stderr, "Usage: ./child1 <command>\n");
    exit(EXIT_FAILURE);
  }
  int write_fd = atoi(argv[1]);
  dup2(write_fd, STDOUT_FILENO);
  close(write_fd);
  printf("Hello from child 1 with pid %d\n", getpid());
  fflush(stdout);
  exit(0);
}