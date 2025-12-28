#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
    int fd;
    char buffer[128];
    ssize_t n;
    /* Ensure sample.txt exists or create it */
    fd = open("sample.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    /* Write a sample line */
    char *ptr = "asdfsadf";
    write(fd, ptr, strlen(ptr));
    write(fd, "This is a sample file for UNIX I/O.\n", 36);
    /* Move to start and read */
    lseek(fd, 0, SEEK_SET);
    n = read(fd, buffer, sizeof(buffer)-1);
    if (n < 0) {
        perror("read");
        close(fd);
        return 1;
    }
    buffer[n] = '\0';
    printf("Read %zd bytes:\n%s", n, buffer);
    close(fd);
    return 0;
}
