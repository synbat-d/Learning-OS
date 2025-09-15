#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define NUM_PROC 16

typedef struct __counter_t {
    int global;
    pthread_mutex_t glock;
    int local[NUM_PROC];
    pthread_mutex_t llock[NUM_PROC];
    int threshold;
} counter_t;

void init(counter_t *c, int threshold) {
    c->threshold = threshold;
    c->global = 0;
    pthread_mutex_init(&c->glock, NULL);
    for(int i=0; i<NUM_PROC; i++) {
        c->local[i] = 0;
        pthread_mutex_init(&c->llock[i], NULL);
    }
}

void update(counter_t *c, int threadId, int amt) {
    int cpu = threadId % NUM_PROC;
    pthread_mutex_lock(&c->llock[cpu]);
    c->local[cpu] += amt;
    if(c->local[cpu] >= c->threshold) {
        pthread_mutex_lock(&c->glock);
        c->global += c->local[cpu];
        pthread_mutex_unlock(&c->glock);
        c->local[cpu] = 0;
    }
    pthread_mutex_unlock(&c->llock[cpu]);
}

int get(counter_t *c) {
    pthread_mutex_lock(&c->glock);
    int result = c->global;
    pthread_mutex_unlock(&c->glock);
    return result;
}

#define NUM_ITER 1000000

typedef struct {
    int id;
    counter_t *c;
} thread_args_t;

void *worker(void *arg) {
    thread_args_t *args = (thread_args_t *) arg;
    for(int i=0; i<NUM_ITER; i++) {
        update(args->c, args->id, 1);
    }
    return NULL;
}

int main(int argc, char *argv[]){
    if(argc != 3) {
        printf("Usage: %s <num_threads> <threshold>\n", argv[0]);
        return 1;
    }
    int num_threads = atoi(argv[1]);
    int threshold = atoi(argv[2]);
    pthread_t threads[num_threads];
    counter_t c;
    init(&c, threshold);
    thread_args_t args[num_threads];

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for(int i=0; i<num_threads; i++) {
        args[i].id = i;
        args[i].c = &c;
        pthread_create(&threads[i], NULL, worker, &args[i]);
    }

    for(int i=0; i<num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    gettimeofday(&end, NULL);

    long start_us = start.tv_sec * 1000000L + start.tv_usec;
    long end_us   = end.tv_sec * 1000000L + end.tv_usec;
    long diff_us  = end_us - start_us;

    printf("Threads: %d, Final counter = %d\n", num_threads, get(&c));
    printf("Time taken: %ld microseconds (%.3f seconds)\n",
           diff_us, diff_us / 1000000.0);

    return 0;
}