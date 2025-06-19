#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd1[2], fd2[2];
    pid_t pid;
    int number = 5;

    pipe(fd1);
    pipe(fd2);
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
        wait(NULL); // Wait for child to finish

        int result;
        read(fd2[0], &result, sizeof(result));
        printf("Parent received after wait: %d\n", result);

        close(fd1[1]);
        close(fd2[0]);
    }

    return 0;
}
