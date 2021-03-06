#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 4455

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    char resv_buffer[1024];

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    printf("Created \n");
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(PORT);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("Connected \n");

    strcpy(buffer, "Hello");
    send(clientSocket, buffer, strlen(buffer), 0);

    recv(clientSocket, resv_buffer, 1024, 0);
    printf("Received: %s\n", resv_buffer);

    return 0;
}