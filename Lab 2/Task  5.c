#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

struct Result {
    int sum;
    float average;
};

int main() {
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    pid_t pid = fork();

    if (pid == 0) {
        // Child
        close(fd1[1]);
        close(fd2[0]);

        int nums[4];
        read(fd1[0], nums, sizeof(nums));

        int sum = 0;
        for (int i = 0; i < 4; i++) sum += nums[i];
        struct Result res;
        res.sum = sum;
        res.average = sum / 4.0;

        write(fd2[1], &res, sizeof(res));

        close(fd1[0]);
        close(fd2[1]);
    } else {
        // Parent
        close(fd1[0]);
        close(fd2[1]);

        int nums[4] = {1000, 20, 30, 40};
        write(fd1[1], nums, sizeof(nums));

        wait(NULL);

        struct Result res;
        read(fd2[0], &res, sizeof(res));
        printf("Sum: %d, Average: %.2f\n", res.sum, res.average);

        close(fd1[1]);
        close(fd2[0]);
    }

    return 0;
}
