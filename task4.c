#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    char line[1024];
    int len = 0;
    char c;
    while (len < 1023 && read(0, &c, 1) == 1) {
        line[len++] = c;
        if (c == '\n') break;
    }
    line[len] = '\0';

    char out[1100];
    int n = sprintf(out, "PID=%d: %s", getpid(), line);
    if (out[n - 1] != '\n') out[n++] = '\n';
    write(fd, out, n);

    /* With O_APPEND, every write first moves the file offset to the end of the
       file and then writes, so after each write the offset sits just past the
       new data. SEEK_CUR therefore returns the new file size, which keeps growing. */
    printf("Offset: %ld\n", (long)lseek(fd, 0, SEEK_CUR));
    close(fd);
    return 0;
}
