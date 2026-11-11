#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26);
    close(fd);

    fd = open("data.txt", O_RDWR);
    printf("Size: %ld\n", (long)lseek(fd, 0, SEEK_END));

    ftruncate(fd, 10);
    printf("New size: %ld\n", (long)lseek(fd, 0, SEEK_END));

    lseek(fd, 0, SEEK_SET);
    char buf[32];
    int n = read(fd, buf, sizeof(buf));
    buf[n] = '\0';
    printf("%s\n", buf);
    close(fd);
    return 0;
}
