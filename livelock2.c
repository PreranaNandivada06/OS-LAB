#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


pthread_mutex_t first_mutex;
pthread_mutex_t second_mutex;


void *do_work_one(void *param) {
    while (1) {
        pthread_mutex_lock(&first_mutex);
        printf("Thread 1: locked first_mutex\n");


        if (pthread_mutex_trylock(&second_mutex) == 0) {
            printf("Thread 1: locked second_mutex\n");
            printf("Thread 1: doing some work...\n");
            sleep(1);
            pthread_mutex_unlock(&second_mutex);
            pthread_mutex_unlock(&first_mutex);
            printf("Thread 1: released both locks\n");
            break;
        } else {
            printf("Thread 1: couldn't lock second_mutex, retrying...\n");
            pthread_mutex_unlock(&first_mutex);
            sleep(1); // both threads sleep same time → livelock likely
        }
    }
    pthread_exit(0);
}


void *do_work_two(void *param) {
    while (1) {
        pthread_mutex_lock(&second_mutex);
        printf("Thread 2: locked second_mutex\n");


        if (pthread_mutex_trylock(&first_mutex) == 0) {
            printf("Thread 2: locked first_mutex\n");
            printf("Thread 2: doing some work...\n");
            sleep(1);
            pthread_mutex_unlock(&first_mutex);
            pthread_mutex_unlock(&second_mutex);
            printf("Thread 2: released both locks\n");
            break;
        } else {
            printf("Thread 2: couldn't lock first_mutex, retrying...\n");
            pthread_mutex_unlock(&second_mutex);
            sleep(1); // same sleep time → livelock risk
        }
    }
    pthread_exit(0);
}


int main() {
    pthread_t t1, t2;


    pthread_mutex_init(&first_mutex, NULL);
    pthread_mutex_init(&second_mutex, NULL);


    pthread_create(&t1, NULL, do_work_one, NULL);
    pthread_create(&t2, NULL, do_work_two, NULL);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);


    pthread_mutex_destroy(&first_mutex);
    pthread_mutex_destroy(&second_mutex);


    printf("Main: done.\n");
    return 0;
}

