#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

// #define TRACE
#ifdef TRACE
#define TRACE_FUNC printf("Enter to function %s()\n", __func__)
#define TRACE_LINE printf("Pass line %d in func %s()\n", __LINE__, __func__)
#define TRACE_THREAD_LINE(mark, thread_number) printf( \
    "%s, Thread %d, Pass line %d in func %s()\n", \
    mark, thread_number, __LINE__, __func__)
#else
#define TRACE_FUNC
#define TRACE_LINE
#define TRACE_THREAD_LINE(mark, thread_number)
#endif

typedef struct job_t {
    __uint16_t working_time_seconds;
    struct job_t* next;
} job_t;

typedef struct {
    struct job_t* first;
    struct job_t* last;
    int size;
    pthread_mutex_t add_job_mutex;
    pthread_mutex_t get_job_mutex;
} job_queue_t;

bool job_queue_ctor(job_queue_t *queue) {
    // TRACE_FUNC;
    queue->first = malloc(sizeof(job_t));
    if (queue->first == NULL) {
        return false;
    }
    queue->last = queue->first;
    queue->first->working_time_seconds = -1;
    queue->first->next = NULL;
    queue->size = 0;
    pthread_mutex_init(&queue->add_job_mutex, NULL);
    pthread_mutex_init(&queue->get_job_mutex, NULL);
    return true;
}

void job_queue_dtor(job_queue_t *queue) {
    // TRACE_FUNC;
    while (queue->first != NULL) {
        // TRACE_LINE;
        job_t* temp = queue->first;
        queue->first = queue->first->next;
        free(temp);
    }
    queue->size = 0;
}

bool add_job_to_queue(job_queue_t *queue, job_t *job) {
    // TRACE_FUNC;
    if (job == NULL) {
        return false;
    }

    pthread_mutex_lock(&queue->add_job_mutex);
    queue->last->next = job;
    queue->last = queue->last->next;
    queue->last->next = NULL;
    ++(queue->size);
    pthread_mutex_unlock(&queue->add_job_mutex);
    return true;
}

job_t* get_job_from_queue(job_queue_t *queue) {
    TRACE_FUNC;
    pthread_mutex_lock(&queue->get_job_mutex);
    TRACE_LINE;
    job_t *result = NULL;
    if (queue->first->next != NULL) {
        TRACE_LINE;
        result = queue->first->next;
        queue->first->next = result->next;
        --(queue->size);
        TRACE_LINE;
    }
    pthread_mutex_unlock(&queue->get_job_mutex);
    TRACE_LINE;
    return result;
}

job_queue_t job_queue;
pthread_mutex_t job_count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t done_job_count_mutex = PTHREAD_MUTEX_INITIALIZER;
int job_count = 0;
int done_job_count = 0;
int initial_job_count = 0;

void * producer_function(void *number) {
    TRACE_FUNC;
    int producer_number = *((int*)number);

    return NULL;
}

void * consumer_function(void *number) {
    TRACE_FUNC;
    int consumer_number = *((int*)number);
    
    return NULL;
}

int main(int argc, char const *argv[])
{
    // TRACE_FUNC;
    if (argc < 4) {
        printf("Provide three integer arguments\n");
        return -1;
    }

    if (job_queue_ctor(&job_queue) == false) {
        printf("Cannot create a job queue\n");
        return -1;
    }

    int producers_count = atoi(argv[1]);
    int consumers_count = atoi(argv[2]);
    initial_job_count = atoi(argv[3]);
    job_count = initial_job_count;

    printf("Job count is %d\n", job_count);

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

    TRACE_LINE;

    int i = 0;
    for (i = 0; i < producers_count; ++i) {
        pthread_create(&(producers[i]), NULL, producer_function, &i);
    }

    TRACE_LINE;

    for (i = 0; i < consumers_count; ++i) {
        pthread_create(&(consumers[i]), NULL, consumer_function, &i);
    }

    TRACE_LINE;

    for (i = 0; i < producers_count; ++i) {
        TRACE_LINE;
        pthread_join(producers[i], NULL);
    }

    TRACE_LINE;

    for (i = 0; i < consumers_count; ++i) {
        pthread_join(consumers[i], NULL);
    }

    TRACE_LINE;

    printf("Job count is %d\nDone %d tasks\n", job_count, done_job_count);
    // printf("Queue size is %d\n", job_queue.size);

    free(producers);
    free(consumers);
    job_queue_dtor(&job_queue);
    return 0;
}

