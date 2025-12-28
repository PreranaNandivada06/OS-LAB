#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child: starting work (PID=%d)\n", getpid());
        sleep(2);
        printf("Child: finished work\n");
        exit(0);
    } else {
        printf("Parent: waiting for child (PID=%d)\n", pid);
        wait(NULL);
        printf("Parent: child finished, continuing.\n");
    }
    return 0;
}
