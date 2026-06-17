#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {

	int sockfd;
	struct sockaddr_in server_addr, client_addr;
	char buffer[BUFFER_SIZE];
	socklen_t client_len = sizeof(client_addr);


	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if(sockfd < 0){
		perror("socket connection");
		exit(EXIT_FAILURE);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	memset(&client_addr, 0, sizeof(client_addr));

	// configure server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	// Bind socket
	if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		perror("bind");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	printf("UDP Server listening on port %d...\n", PORT);

	while(1){
		// Returns the number of bytes read
		int n = recvfrom(sockfd, buffer, BUFFER_SIZE-1, 0, (struct sockaddr *)&client_addr, &client_len);

		if(n < 0){
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}

		buffer[n] = '\0';

		printf("Received from %s:%d -> %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

		char *reply = "Message Received(server)";

        sendto(sockfd, reply, strlen(reply), 0, (struct sockaddr *)&client_addr, client_len);
    }

    close(sockfd);
    return 0;
}
