#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    int fd[2];
    pid_t pid;
    int number = 42;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == 0) {
        // Child
        close(fd[1]); // Close write end
        int received;
        read(fd[0], &received, sizeof(received));
        printf("Child received: %d\n", received);
        close(fd[0]);
    } else {
        // Parent
        close(fd[0]); // Close read end
        write(fd[1], &number, sizeof(number));
        close(fd[1]);
    }

    return 0;
}
