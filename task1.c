#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char src[256], dst[256], buf[4096];
    printf("Enter source file path: ");
    scanf("%255s", src);
    printf("Enter destination file path: ");
    scanf("%255s", dst);

    int in = open(src, O_RDONLY);
    if (in < 0) { perror("open source"); return 1; }
    int out = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out < 0) { perror("open destination"); close(in); return 1; }

    long total = 0;
    ssize_t n;
    while ((n = read(in, buf, sizeof(buf))) > 0) {
        if (write(out, buf, n) != n) { perror("write"); return 1; }
        total += n;
    }
    if (n < 0) { perror("read"); return 1; }

    printf("Total bytes copied: %ld\n", total);
    close(in);
    close(out);
    return 0;
}
