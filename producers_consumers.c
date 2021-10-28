#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

typedef struct job_t {
    __uint16_t working_time_seconds;
    struct job_t* next;
} job_t;

typedef struct {
    struct job_t* first;
    struct job_t* last;
} job_queue_t;

void job_queue_ctor(job_queue_t *queue) {
    queue->first = NULL;
    queue->last = NULL;
}

void job_queue_dtor(job_queue_t *queue) {
    while (queue->first != queue->last) {
        job_t* temp = queue->first;
        queue->first = queue->first->next;
        free(temp);
    }
}

bool add_task_to_queue(job_queue_t *queue) {
    // queue->last
}


job_queue_t job_queue;
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t job_count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t done_job_count_mutex = PTHREAD_MUTEX_INITIALIZER;
int job_count = 0;
int done_job_count = 0;

void * producer_function(void *number) {
    int producer_number = *((int*)number);
    while (1) {
        pthread_mutex_lock(&job_count_mutex);
        if (job_count > 0) {
            --job_count;
            pthread_mutex_unlock(&job_count_mutex);
            sleep(1 + (rand() % 10));
            job_t *new_job = malloc(sizeof(job_t));

            if (new_job == NULL) {
                printf("Producer %d cannot create a new task and finished\n", producer_number);
                return NULL;
            }

            new_job->next = NULL;
            new_job->working_time_seconds = 1 + (rand() % 10);

            printf("Produce %d add new task to queue\n", producer_number);

            pthread_mutex_lock(&job_queue_mutex);
            job_queue.last->next = new_job;
            pthread_mutex_unlock(&job_queue_mutex);
        }
        else {
            pthread_mutex_unlock(&job_count_mutex);
            return NULL;
        }
    }
    return NULL;
}

void * consumer_function(void *number) {
    int consumer_number = *((int*)number);
    return NULL;
}

int main(int argc, char const *argv[])
{
    if (argc < 4) {
        printf("Provide three integer arguments\n");
        return -1;
    }

    job_queue_ctor(&job_queue);

    int producers_count = atoi(argv[1]);
    int consumers_count = atoi(argv[2]);
    job_count = atoi(argv[3]);

    srand(time(NULL));
    
    pthread_t *producers = NULL;
    pthread_t *consumers = NULL;

    producers = malloc(producers_count * sizeof(pthread_t));
    if (producers == NULL) {
        printf("Cannot allocate memory for threads\n");
        job_queue_dtor(&job_queue);
        return -1;
    }
    consumers = malloc(consumers_count * sizeof(pthread_t));
    if (consumers == NULL) {
        free(producers);
        printf("Cannot allocate memory for threads\n");
        job_queue_dtor(&job_queue);
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
    job_queue_dtor(&job_queue);

    printf("Job count is %d\n Done %d tasks\n", job_count, done_job_count);
    return 0;
}

