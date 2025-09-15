#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c){
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c){
    pthread_mutex_lock(&c->lock);
    c->value--;
    pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    int rc = c->value;
    pthread_mutex_unlock(&c->lock);
    return rc;
}

#define NUM_ITER 1000000

void *worker(void *arg) {
    counter_t *c = (counter_t *) arg;
    for(int i=0; i<NUM_ITER; i++) {
        increment(c);
    }
    return NULL;
}

int main(int argc, char *argv[]){
    if(argc != 2) {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }
    int num_threads = atoi(argv[1]);
    pthread_t threads[num_threads];
    counter_t c;
    init(&c);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for(int i=0; i<num_threads; i++) {
        pthread_create(&threads[i], NULL, worker, &c);
    }

    for(int i=0; i<num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    gettimeofday(&end, NULL);

    long start_us = start.tv_sec * 1000000L + start.tv_usec;
    long end_us   = end.tv_sec * 1000000L + end.tv_usec;
    long diff_us  = end_us - start_us;

    printf("Threads: %d, Final counter = %d\n", num_threads, c.value);
    printf("Time taken: %ld microseconds (%.3f seconds)\n",
           diff_us, diff_us / 1000000.0);

    return 0;
}


