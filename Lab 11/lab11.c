#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    double *a;
    double sum;
    int N;
    int size;
    long tid;
} ThreadArgs;

void *compute(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int myStart, myEnd, myN, i;

    // Extract arguments from the structure
    int N = args->N;
    int size = args->size;
    int tid = args->tid;
    double *a = args->a;

    // Determine start and end of computation for the current thread
    myN = N / size;
    myStart = tid * myN;
    myEnd = myStart + myN;
    if (tid == (size - 1)) myEnd = N;

    // Compute partial sum
    double mysum = 0.0;
    for (i = myStart; i < myEnd; i++)
        mysum += a[i];

    // Grab the lock, update global sum, and release lock
    pthread_mutex_lock(&mutex);
    args->sum += mysum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char **argv) {
    long i;
    pthread_t *tid;

    if (argc != 3) {
        printf("Usage: %s <# of elements> <# of threads>\n", argv[0]);
        exit(-1);
    }

    int N = atoi(argv[1]); // No. of elements
    int size = atoi(argv[2]); // No. of threads

    // Allocate vector and initialize
    double *a = (double *)malloc(sizeof(double) * N);
    for (i = 0; i < N; i++)
        a[i] = (double)(i + 1);

    // Create thread IDs array
    tid = (pthread_t *)malloc(sizeof(pthread_t) * size);

    // Create thread arguments array
    ThreadArgs *args = (ThreadArgs *)malloc(sizeof(ThreadArgs) * size);

    // Create threads
    for (i = 0; i < size; i++) {
        args[i].a = a;
        args[i].sum = 0.0;
        args[i].N = N;
        args[i].size = size;
        args[i].tid = i;
        pthread_create(&tid[i], NULL, compute, (void *)&args[i]);
    }

    // Wait for threads to complete
    for (i = 0; i < size; i++)
        pthread_join(tid[i], NULL);

    // Calculate total sum from individual thread sums
    double total_sum = 0.0;
    for (i = 0; i < size; i++)
        total_sum += args[i].sum;

    printf("The total is %g, it should be equal to %g\n",
           total_sum, ((double)N * (N + 1)) / 2);

    // Free allocated memory
    free(a);
    free(tid);
    free(args);

    return 0;
}