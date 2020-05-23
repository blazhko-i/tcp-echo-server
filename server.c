#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

#define PORT 4455

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;

    int newSocket;
    struct sockaddr_in new_Addr;

    socklen_t addr_size;
    char buffer[1024];
    char send_buffer[1024];

    sockfd=socket(PF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, '\0', sizeof(serverAddr));

    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(PORT);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    listen(sockfd, 5);
    addr_size = sizeof(new_Addr);

    newSocket=accept(sockfd, (struct sockaddr*)&new_Addr, &addr_size);

    recv(newSocket, buffer, 1024, 0);
    printf("Received: %s\n", buffer);

    strcpy(send_buffer, buffer);
    send(newSocket, send_buffer, strlen(buffer), 0);

    // Ip адрес
    char str[100];
    inet_ntop(AF_INET, &(new_Addr.sin_addr), str, INET_ADDRSTRLEN);
    printf("%s\n", str);

    return 0;
}