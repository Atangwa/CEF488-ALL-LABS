#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    int fd1[2], fd2[2];
    pid_t pid;
    int number = 5;

    pipe(fd1); // Parent to child
    pipe(fd2); // Child to parent

    pid = fork();

    if (pid == 0) {
        // Child
        close(fd1[1]);
        close(fd2[0]);

        int received;
        read(fd1[0], &received, sizeof(received));
        received *= 2;
        write(fd2[1], &received, sizeof(received));

        close(fd1[0]);
        close(fd2[1]);
    } else {
        // Parent
        close(fd1[0]);
        close(fd2[1]);

        write(fd1[1], &number, sizeof(number));
        int result;
        read(fd2[0], &result, sizeof(result));
        printf("Parent received: %d\n", result);

        close(fd1[1]);
        close(fd2[0]);
    }

    return 0;
}
