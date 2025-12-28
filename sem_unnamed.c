#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>


int main() {
    sem_t sem;           // unnamed semaphore (local variable)
    int val;


    // Initialize unnamed semaphore
    // 0 = semaphore shared between threads of the same process
    // 5 = initial value
    sem_init(&sem, 0, 5);


    sem_getvalue(&sem, &val);
    printf("sem value = %d\n", val);


    sem_wait(&sem);  // acquire
    sem_getvalue(&sem, &val);
    printf("sem value = %d\n", val);


    sem_post(&sem);  // release
    sem_getvalue(&sem, &val);
    printf("sem value = %d\n", val);


    printf("I am here\n");


    // Destroy unnamed semaphore
    sem_destroy(&sem);


    return 0;
}
=
