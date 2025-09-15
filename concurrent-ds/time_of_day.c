#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval t1,t2;
    gettimeofday(&t1, NULL);
    long start = t1.tv_sec * 1000000 + t1.tv_usec;
    printf("Seconds: %ld, Microseconds: %ld\n", t1.tv_sec, t1.tv_usec);
    gettimeofday(&t2, NULL);
    long end = t2.tv_sec * 1000000 + t2.tv_usec;
    printf("Seconds: %ld, Microseconds: %ld\n", t2.tv_sec, t2.tv_usec);
    long diff = end - start;
    printf("Difference in microseconds = %ld\n", diff);
    return 0;
}