#include <stdio.h>
#include <pthread.h>
void* task(void * arg) {
    printf("Thread running: message = %s\n", (char*)arg);
    return NULL;
}
int main() {
    pthread_t tid;
    const char *msg = "Hello froffcm thread";
    if (pthread_create(&tid, NULL, task, (void*)msg) != 0) {
        perror("pthread_create");
        return 1;
    }
    pthread_join(tid, NULL);
    printf("Thread joined, exiting main.\n");
    return 0;
}
