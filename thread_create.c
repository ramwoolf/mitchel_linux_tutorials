#include <stdio.h>
#include <pthread.h>

struct char_print_params {
    char character;
    int count;
};

void char_print(void *parameters) {
    struct char_print_params *p = (struct char_print_params *) parameters;
    int i = 0;

    for (i = 0; i < p->count; ++i) {
        fputc(p->character, stderr);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t thread1_id;
    pthread_t thread2_id;
    struct char_print_params p1;
    struct char_print_params p2;

    p1.character = 'x';
    p1.count = 100;
    p2.character = 'o';
    p2.count = 150;

    pthread_create(&thread1_id, NULL, char_print, &p1);
    pthread_create(&thread2_id, NULL, char_print, &p2);

    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);
    return 0;
}
