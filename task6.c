#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("numbers.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char line[16];
    for (int i = 1; i <= 10; i++) {
        int n = sprintf(line, "%d\n", i);
        write(fd, line, n);
    }
    close(fd);

    fd = open("numbers.txt", O_RDWR);
    char c;
    int lines = 0;
    off_t pos = 0, start = 0, end = 0;
    while (read(fd, &c, 1) == 1) {
        pos++;
        if (c == '\n') {
            lines++;
            if (lines == 3) start = pos;
            if (lines == 4) { end = pos; break; }
        }
    }

    char rest[1024];
    lseek(fd, end, SEEK_SET);
    int restLen = read(fd, rest, sizeof(rest));

    lseek(fd, start, SEEK_SET);
    write(fd, "100\n", 4);
    write(fd, rest, restLen);

    char buf[1024];
    lseek(fd, 0, SEEK_SET);
    int n = read(fd, buf, sizeof(buf));
    write(1, buf, n);
    close(fd);
    return 0;
}
