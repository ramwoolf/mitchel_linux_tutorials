#include <malloc.h>
#include <pthread.h>
#include <stdio.h>

static pthread_key_t thread_log_key;

void write_to_thread_log(char const* msg) {
    printf("Write log in %d\n", (int)pthread_self());
    FILE* thread_log = (FILE*)pthread_getspecific(thread_log_key);
    fprintf(thread_log, "%S\n", msg);
}

void close_thread_log(void* thread_log) {
    printf("Close file in %d\n", (int)pthread_self());
    fclose((FILE*)thread_log);
}

void* thread_function(void* args) {
    printf("HERE %d\n", (int)pthread_self());
    char thread_lof_filename[20];
    FILE* thread_log;

    sprintf(thread_lof_filename, "bin/thread%d.log", (int)pthread_self());
    thread_log = fopen(thread_lof_filename, "w");
    pthread_setspecific(thread_log_key, thread_log);

    write_to_thread_log("Start log.");
    write_to_thread_log("End log.");
    return NULL;
    // return thread_log;
}

int main(int argc, char const *argv[])
{
    int i = 0;
    // void* log = thread_function(NULL);
    // close_thread_log(log);

    pthread_t threads[5];
    pthread_key_create(&thread_log_key, close_thread_log);
    
    for (i = 0; i < 5; ++i) {
        pthread_create(&(threads[i]), NULL, thread_function, NULL);
    }

    for (i = 0; i < 5; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
