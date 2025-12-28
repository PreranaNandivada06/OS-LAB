#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


long var = 0;
sem_t sem;


void* f1(void* arg) {
    for (int i=0; i<20; i++) {
        sem_wait(&sem);
        var = var + 1;
        fprintf(stderr, "thread1 var:%ld\n", var);
        sem_post(&sem);
        sleep(1);
    }
    return NULL;
}


void* f2(void* arg) {
    for (int i=0; i<20; i++) {
        sem_wait(&sem);
        var = var - 1;
        fprintf(stderr, "thread2 var:%ld\n", var);
        sem_post(&sem);
        sleep(1);
    }
    return NULL;
}


int main() {
    pthread_t t1, t2;
    sem_init(&sem, 0, 1); // unnamed semaphore for threads


    fprintf(stderr, "Parent starts\n");
    pthread_create(&t1, NULL, f1, NULL);
    pthread_create(&t2, NULL, f2, NULL);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);


    fprintf(stderr, "final var:%ld\n", var);
    sem_destroy(&sem);
    return 0;
}


