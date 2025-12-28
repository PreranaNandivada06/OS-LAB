#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child (PID %d): Running exec...\n", getpid());
        execlp("/bin/echo", "echo", "Hello from exec in Child!", NULL);
        printf("This wont print if exec works\n");
    }
    else {
        sleep(2);  // Ensures child becomes zombie for a moment
        printf("Parent (PID %d): Waiting for child using waitpid...\n", getpid());
        waitpid(pid, NULL, 0);  // Reaps zombie child
        printf("Parent: Reaped zombie child!\n");
    }
    return 0;
}
