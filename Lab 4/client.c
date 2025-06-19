#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1" // Change to server IP if testing across machines
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char *message = "Hello from UDP client";
    char buffer[BUFFER_SIZE];
    socklen_t len;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    len = sizeof(servaddr);

    // Send message to server
    sendto(sockfd, (const char *)message, strlen(message), 0, (const struct sockaddr *)&servaddr, len);
    printf("Message sent to server\n");

    // Receive response
    int n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    printf("Server says: %s\n", buffer);
 close(sockfd);
    return 0;
}

    close(sockfd);
    return 0;
}