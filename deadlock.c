#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


pthread_mutex_t first_mutex;
pthread_mutex_t second_mutex;


void *do_work_one(void *param) {
    pthread_mutex_lock(&first_mutex);
    printf("Thread 1 acquired first_mutex\n");


    sleep(1); // simulate work, gives thread 2 a chance to run


    pthread_mutex_lock(&second_mutex);
    printf("Thread 1 acquired second_mutex\n");


    printf("Thread 1 doing work...\n");


    pthread_mutex_unlock(&second_mutex);
    pthread_mutex_unlock(&first_mutex);
    pthread_exit(0);
}


void *do_work_two(void *param) {
    pthread_mutex_lock(&second_mutex);
    printf("Thread 2 acquired second_mutex\n");


    sleep(1); // simulate work


    pthread_mutex_lock(&first_mutex);
    printf("Thread 2 acquired first_mutex\n");


    printf("Thread 2 doing work...\n");


    pthread_mutex_unlock(&first_mutex);
    pthread_mutex_unlock(&second_mutex);
    pthread_exit(0);
}


int main() {
    pthread_t tid1, tid2;


    pthread_mutex_init(&first_mutex, NULL);
    pthread_mutex_init(&second_mutex, NULL);


    pthread_create(&tid1, NULL, do_work_one, NULL);
    pthread_create(&tid2, NULL, do_work_two, NULL);


    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);


    pthread_mutex_destroy(&first_mutex);
    pthread_mutex_destroy(&second_mutex);


    printf("Main: completed successfully.\n");
    return 0;
}

