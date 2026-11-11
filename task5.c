#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("sparse.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, "START", 5);
    lseek(fd, 1024 * 1024, SEEK_CUR);
    write(fd, "END", 3);
    close(fd);

    fd = open("sparse.bin", O_RDONLY);
    printf("Apparent size: %ld\n", (long)lseek(fd, 0, SEEK_END));
    close(fd);
    return 0;
}

/* The 1 MiB gap skipped with lseek is a "hole": the file system does not
   allocate disk blocks for it, and reading it just returns zeros. Only the
   blocks holding "START" and "END" are stored, so du shows far less disk
   usage than the apparent size. */
