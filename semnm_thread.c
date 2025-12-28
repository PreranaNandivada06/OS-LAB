#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>


long var = 5;
sem_t *sem;   // named semaphore for threads


void* f1(void* arg);
void* f2(void* arg);


int main() {
    // Create/open named semaphore
    sem = sem_open("/mysem1", O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }


    printf("Parent starts\n");


    pthread_t t1, t2;
    pthread_create(&t1, NULL, f1, NULL);
    pthread_create(&t2, NULL, f2, NULL);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);


    fprintf(stderr, "final var:%ld\n", var);


    sem_close(sem);
    sem_unlink("/mysem1"); // remove from system


    return 0;
}


void* f1(void* arg) {
    for (long i = 0; i < 20; i++) {
        
        sleep(1);
        sem_wait(sem);
        var = var + 1;
        sem_post(sem);
        fprintf(stderr, "f1 var:%ld\n", var);
        
    }
    return NULL;
}


void* f2(void* arg) {
    for (long i = 0; i < 20; i++) {
        
        sleep(1);
        sem_wait(sem);
        var = var - 1;
        sem_post(sem);
        fprintf(stderr, "f2 var:%ld\n", var);
        
    }
    return NULL;
}
