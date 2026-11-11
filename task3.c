#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char path[256];
    printf("Enter file path: ");
    scanf("%255s", path);
    fflush(stdout);

    int fd = open(path, O_RDONLY);
    off_t size = lseek(fd, 0, SEEK_END);

    char c;
    for (off_t pos = size - 1; pos >= 0; pos--) {
        lseek(fd, pos, SEEK_SET);
        read(fd, &c, 1);
        write(1, &c, 1);
    }
    write(1, "\n", 1);
    close(fd);
    return 0;
}
