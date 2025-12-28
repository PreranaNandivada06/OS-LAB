#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        sleep(3); // Give time for parent to exit
        printf("Orphan Child (PID %d): Adopted by %d\n", getpid(), getppid());
    }
    else {
        printf("Parent (PID %d): Exiting without wait (Child becomes orphan)\n", getpid());
    }

    if (pid > 0) {
        wait(NULL);  // wait() used just to demonstrate it
        printf("Parent used wait() before terminating\n");
    }

    return 0;
}
 