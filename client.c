#include <netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t server_len = sizeof(server_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0){
        perror("socket connection");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0){
        perror("inet_pton");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    char *message = "Hello, Server!";

    sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr, server_len);

    int n = recvfrom(sockfd, buffer, BUFFER_SIZE-1, 0, NULL, NULL);

    if(n >= 0){
        buffer[n] = '\0';
        printf("Reply from server: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}