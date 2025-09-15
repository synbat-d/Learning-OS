#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// Usage: ./memory-user <megabytes> [seconds]

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <megabytes> [seconds]\n", argv[0]);
        return 1;
    }

    int mb = atoi(argv[1]);
    if (mb <= 0) {
        fprintf(stderr, "Invalid memory size: %s\n", argv[1]);
        return 1;
    }

    int seconds = -1; // run forever by default
    if (argc >= 3) {
        seconds = atoi(argv[2]);
    }

    size_t size = (size_t)mb * 1024 * 1024;
    char *buffer = malloc(size);
    if (!buffer) {
        perror("malloc");
        return 1;
    }

    printf("Allocated %d MB, starting to touch memory...\n", mb);

    time_t start_time = time(NULL);

    while (seconds < 0 || time(NULL) - start_time < seconds) {
        // Access each page (assume 4 KB pages)
        for (size_t i = 0; i < size; i += 4096) {
            buffer[i] = (char)(i % 256);
        }

        // Sleep for a short moment to not totally hog the CPU
        usleep(10000); // 10ms
    }

    printf("Finished.\n");
    free(buffer);
    return 0;
}