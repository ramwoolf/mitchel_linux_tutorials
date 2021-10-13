#include <stdio.h>
#include <pthread.h>

void * compute_prime(void *arg) {
    int candidate = 2;
    int n = *((int*)arg);

    while (1) {
        int factor;
        int is_prime = 1;

        for (factor = 2; factor < candidate; ++factor) {
            if (candidate % factor == 0) {
                is_prime = 0;
                break;
            }
        }

        if (is_prime) {
            if (--n == 0) {
                return (void *) candidate;
            }
        }

        ++candidate;
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t thread;
    int which_prime = 10;
    int prime;

    pthread_create(&thread, NULL, compute_prime, &which_prime);
    pthread_join(thread, (void *) &prime);
    printf("The %dth prime is %d\n", which_prime, prime);
    return 0;
}
