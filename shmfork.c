#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main() {
    pid_t pid;
    int shmid, *shvar;
    key_t key = ftok(".", 45);
    // Create shared memory
    shmid = shmget(key, sizeof(int), 0664 | IPC_CREAT);
    printf("Key=%d ........Shmid=%d\n", key, shmid);
    // Attach shared memory
    shvar = shmat(shmid, NULL, 0);
    *shvar = 10;
    printf("Initial value of *shvar = %d\n", *shvar);
    pid = fork();
    if (pid == 0) {
        // Child process
        sleep(10); // simulate delay
        *shvar = *shvar + 90;
        printf("Child updated *shvar = %d\n", *shvar);
        exit(0);
    } else {
        // Parent process
        wait(NULL);  // Wait for child to complete
        printf("Parent sees *shvar (before child updates) = %d\n", *shvar);
        sleep(2); // Give child time to update
        printf("Parent sees *shvar (after delay) = %d\n", *shvar);
    }
    // Detach and remove shared memory
    shmdt(shvar);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

