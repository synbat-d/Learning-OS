#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	int fd = open ("/tmp/fileLuffy.txt", O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
	assert(fd > -1);
	int rc = write(fd, "hello OSTEP INTRO !\n", 21);
	assert(rc == 21);
	close(fd);
	return 0;
}