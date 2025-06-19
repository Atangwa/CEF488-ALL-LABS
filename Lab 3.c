#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 100

void create_fifo() {
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
    } else {
        printf("FIFO created successfully.\n");
    }
}

void run_server() {
    int fd;
    char message[BUFFER_SIZE];

    printf("Enter a message to send to the client: ");
    fgets(message, BUFFER_SIZE, stdin);

    // Remove newline character if present
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';
    }

  fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("Server: open for writing");
        return;
    }

    write(fd, message, strlen(message) + 1);  // Include null terminator
    printf("Server: Message sent.\n");

    close(fd);
}

void run_client() {
    int fd;
    char buffer[BUFFER_SIZE];

    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("Client: open for reading");
        return;
    }

    read(fd, buffer, sizeof(buffer));
    printf("Client: Received message: %s\n", buffer);

    close(fd);
}
int main() {
    int choice;

    while (1) {
        printf("\n--- FIFO Communication Menu ---\n");
        printf("1. Create FIFO\n");
        printf("2. Run as Server\n");
        printf("3. Run as Client\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from buffer

        switch (choice) {
            case 1:
                create_fifo();
                break;
            case 2:
                run_server();
                break;
            case 3:
                run_client();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
  }
return 0;
}


