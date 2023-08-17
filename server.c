#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define MAX_CLIENTS 5

void handleClient(int clientSocket) {
    char buffer[1024];
    int bytesReceived;

    while (1) {
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            perror("Error receiving data");
            break;
        }

        buffer[bytesReceived] = '\0';
        if (strcmp(buffer, "ping") == 0) {
            printf("Received ping from client %d\n", clientSocket);
            send(clientSocket, "pong", 4, 0);
        }
    }

    close(clientSocket);
    printf("Client %d disconnected\n", clientSocket);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(struct sockaddr_in);

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Error creating socket");
        return 1;
    }

    // Bind socket
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error binding socket");
        return 1;
    }

    // Listen for clients
    listen(serverSocket, MAX_CLIENTS);
    printf("Server listening on port %d...\n", PORT);

    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
        if (clientSocket < 0) {
            perror("Error accepting client connection");
            continue;
        }

        printf("Client %d connected\n", clientSocket);

        // Create a new process to handle the client
        if (fork() == 0) {
            close(serverSocket);
            handleClient(clientSocket);
            exit(0);
        }

        close(clientSocket);
    }

    return 0;
}

