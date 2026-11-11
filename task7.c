#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char p1[256], p2[256];
    printf("Enter first file path: ");
    scanf("%255s", p1);
    printf("Enter second file path: ");
    scanf("%255s", p2);

    int f1 = open(p1, O_RDONLY);
    int f2 = open(p2, O_RDONLY);

    char b1[4096], b2[4096];
    long index = 0;
    while (1) {
        int n1 = read(f1, b1, sizeof(b1));
        int n2 = read(f2, b2, sizeof(b2));
        int min = n1 < n2 ? n1 : n2;

        for (int i = 0; i < min; i++) {
            if (b1[i] != b2[i]) {
                printf("Files differ at byte %ld\n", index + i);
                return 1;
            }
        }
        index += min;

        if (n1 != n2) {
            printf("Files differ at byte %ld\n", index);
            return 1;
        }
        if (n1 == 0) break;
    }

    printf("Files are identical\n");
    return 0;
}
