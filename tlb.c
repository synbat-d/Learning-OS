#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

long get_time_microseconds() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000L + tv.tv_usec;
}

int main(int argc, char *argv[]) {
	if(argc != 3) {
		fprintf(stderr, "Usage: %s <NUMPAGES> <REPEATS>\n", argv[0]);
		exit(1);
	}
	int NUMPAGES = atoi(argv[1]);
	int REPEATS = atoi(argv[2]);
	printf("NUMPAGES = %d, REPEATS = %d\n", NUMPAGES, REPEATS);
    long page_size = sysconf(_SC_PAGESIZE);
    printf("Page size: %ld bytes\n", page_size);
	int jump = ((int)page_size) / sizeof(int);
	
	int* array = malloc(sizeof(int)* jump * NUMPAGES);
	
	if (array == NULL) {
        perror("malloc failed");
        exit(1);
    }
	
	for (int i = 0; i < NUMPAGES * jump; i += jump) {
        array[i] = 0;
    }
	
	long start = get_time_microseconds();
	
	for(int i=0; i<REPEATS; i++) {
		for(int j=0; j<NUMPAGES*jump; j = j + jump) {
			array[j] += 1;
		}
	}
	
	long end = get_time_microseconds();
	
	long difference = end - start;
	
	double access_time = (double)difference / (NUMPAGES*REPEATS);
	double nanos = access_time * 1000;
	
	printf("Total time: %ld microseconds\n", difference);
    printf("Access time: %.2f microseconds\n", access_time);
    printf("Access time: %.2f nanoseconds\n", nanos);
	
	free(array);
    return 0;
}