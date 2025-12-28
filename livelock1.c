#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
pthread_mutex_t first_mutex;
pthread_mutex_t second_mutex;
void *do_work_one(void *param) {
    int done = 0;
    while (!done) {
        // Lock first mutex
        pthread_mutex_lock(&first_mutex);
        printf("Thread 1: Locked first_mutex\n");
        // Try to lock second mutex (non-blocking)
        if (pthread_mutex_trylock(&second_mutex) == 0) {
            printf("Thread 1: Locked second_mutex\n");
            // --- Critical Section ---
            printf("Thread 1: Doing some work...\n");
            sleep(1);
            // ------------------------
            pthread_mutex_unlock(&second_mutex);
            pthread_mutex_unlock(&first_mutex);
            done = 1;  // success
            printf("Thread 1: Released both locks\n");
        } else {
            // Could not get second_mutex → release first and retry
            printf("Thread 1: Could not lock second_mutex, retrying...\n");
            pthread_mutex_unlock(&first_mutex);
            sleep(1);  // give time to other thread
        }
    }
    pthread_exit(0);
}
void *do_work_two(void *param) {
    int done = 0;
    while (!done) {
        // Lock second mutex
        pthread_mutex_lock(&second_mutex);
        printf("Thread 2: Locked second_mutex\n");
        // Try to lock first mutex (non-blocking)
        if (pthread_mutex_trylock(&first_mutex) == 0) {
            printf("Thread 2: Locked first_mutex\n");
            // --- Critical Section ---
            printf("Thread 2: Doing some work...\n");
            sleep(1);
            // ------------------------
            pthread_mutex_unlock(&first_mutex);
            pthread_mutex_unlock(&second_mutex);
            done = 1;  // success
            printf("Thread 2: Released both locks\n");
        } else {
            // Could not get first_mutex → release second and retry
            printf("Thread 2: Could not lock first_mutex, retrying...\n");
            pthread_mutex_unlock(&second_mutex);
            sleep(1);
        }
    }

    pthread_exit(0);
}
int main() {
    pthread_t tid1, tid2;
    // Initialize both mutexes
    pthread_mutex_init(&first_mutex, NULL);
    pthread_mutex_init(&second_mutex, NULL);
    // Create both threads
    pthread_create(&tid1, NULL, do_work_one, NULL);
    pthread_create(&tid2, NULL, do_work_two, NULL);
    // Wait for both threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    // Clean up
    pthread_mutex_destroy(&first_mutex);
    pthread_mutex_destroy(&second_mutex);
    printf("Main: All threads completed successfully.\n");
    return 0;
}

