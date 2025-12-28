#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


long var = 5;
int f2();
int f1();
sem_t *sem;


int main() {
    sem = sem_open("/snuc", O_CREAT, 0662, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }


    printf("Parent starts\n");
    pid_t chldpid1, chldpid2;


    if ((chldpid1 = fork()) == 0) {
        // first child
        f2();
        return 0;
    }


    if ((chldpid2 = fork()) == 0) {
        // second child
        f1();
        return 0;
    }


    // parent waits
    wait(NULL);
    wait(NULL);
    fprintf(stderr, "final var:%ld\n", var);


    sem_close(sem);
    sem_unlink("/snuc"); // correct name


    return 0;
}


int f1() {
    long i;
    for (i = 0; i < 20; i++) {
        
        sleep(1);
        sem_wait(sem);
        var = var + 1;
        sem_post(sem);
        fprintf(stderr, "f1 var:%ld\n", var);
        
    }
    return 0;
}


int f2() {
    long i;
    for (i = 0; i < 20; i++) {
       
        sleep(1);
        sem_wait(sem);
        var = var - 1;
        sem_post(sem);
        fprintf(stderr, "f2 var:%ld\n", var);
        
    }
    return 0;
}


