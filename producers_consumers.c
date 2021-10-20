#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    __uint16_t working_time_seconds;
} job_t;

typedef struct {
    job_t* first;
    job_t* last;
} job_queue_t;

void job_queue_ctor(job_queue_t *queue) {
    queue->first = NULL;
    queue->last = NULL;
}

bool add_task_to_queue() {
    //
}


job_queue_t job_queue;
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

void producer_function() {
    //
}

void consumer_function() {
    //
}

int main(int argc, char const *argv[])
{
    if (argc < 3) {
        printf("Provide two integer arguments\n");
        return -1;
    }

    job_queue_ctor(&job_queue);

    int producers_count = atoi(argv[1]);
    int consumers_count = atoi(argv[2]);
    
    pthread_t *producers = NULL;
    pthread_t *consumers = NULL;

    producers = malloc(producers_count * sizeof(pthread_t));
    if (producers == NULL) {
        printf("Cannot allocate memory for threads\n");
        return -1;
    }
    consumers = malloc(consumers_count * sizeof(pthread_t));
    if (consumers == NULL) {
        free(producers);
        printf("Cannot allocate memory for threads\n");
        return -1;
    }

    int i = 0;
    for (i = 0; i < producers_count; ++i) {
        pthread_create(&(producers[i]), NULL, producer_function, NULL);
    }

    for (i = 0; i < consumers_count; ++i) {
        pthread_create(&(consumers[i]), NULL, producer_function, NULL);
    }

    for (i = 0; i < producers_count; ++i) {
        pthread_join(producers[i], NULL);
    }

    for (i = 0; i < consumers_count; ++i) {
        pthread_join(producers[i], NULL);
    }

    free(producers);
    free(consumers);
    return 0;
}

