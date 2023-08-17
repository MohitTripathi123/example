#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char message[] = "ping";
    char buffer[1024];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Error creating socket");
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error connecting to server");
        return 1;
    }

    while (1) {
        // Send ping message to server
        if (send(clientSocket, message, strlen(message), 0) < 0) {
            perror("Error sending data");
            break;
        }

        // Receive pong response from server
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            perror("Error receiving data");
            break;
        }

        buffer[bytesReceived] = '\0';
        if (strcmp(buffer, "pong") == 0) {
            printf("Received pong from server\n");
        }

        sleep(1); // Send ping every second
    }

    close(clientSocket);
    return 0;
}

