#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num_clients;
    int child_count = 0;  // For Task 5: to track number of child processes

    printf("Enter the number of client processes to create: ");
    scanf("%d", &num_clients);

    for (int i = 0; i < num_clients; i++) {
        pid_t pid = fork();

        if (pid < 0) {  // Task 4: Handling fork() failures
            perror("Fork failed");
            continue;  // Continue creating other child processes even if one fork fails
        }

        if (pid == 0) {  // Child process
            printf("Child Process: Handling request.\n");
            printf("My PID = %d, My Parent's PID = %d\n", getpid(), getppid());  // Task 5: Displaying process information
            sleep(2);  // Task 3: Simulate client request handling
            exit(0);   // Child exits after finishing
        } else {  // Parent process
            child_count++;  // Task 5: Counting how many children created
        }
    }

    // Parent process waits for all child processes (Task 2 and Task 1 synchronization)
    for (int i = 0; i < child_count; i++) {
        int status;
        pid_t child_pid = wait(&status);  // Blocking until child terminates
        if (child_pid > 0) {
            printf("Parent: Client with PID = %d has finished handling the request.\n", child_pid);
        }
    }

    // After all children have finished
    printf("Parent: Total number of child processes created = %d\n", child_count);  // Task 5: Final count

    return 0;
}
