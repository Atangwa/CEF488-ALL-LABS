#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    pid_t pid = fork();

    if (pid == 0) {
        // Child
        close(fd1[1]);
        close(fd2[0]);

        int nums[3];
        read(fd1[0], nums, sizeof(nums));

        int sum = nums[0] + nums[1] + nums[2];
        write(fd2[1], &sum, sizeof(sum));

        close(fd1[0]);
        close(fd2[1]);
    } else {
        // Parent
        close(fd1[0]);
        close(fd2[1]);

        int nums[3] = {1, 2, 3};
        write(fd1[1], nums, sizeof(nums));

        wait(NULL); // Wait for child

        int result;
        read(fd2[0], &result, sizeof(result));
        printf("Sum received from child: %d\n", result);

        close(fd1[1]);
        close(fd2[0]);
    }

    return 0;
}
