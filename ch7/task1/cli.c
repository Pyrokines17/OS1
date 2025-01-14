#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
	int sockfd;
	struct sockaddr_in servaddr;
	
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
		
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	char c;
		
	do {
		int n, len;
		char* buffer1 = calloc(MAXLINE, sizeof(char));

		if (buffer1 == NULL) {
			perror("calloc failed");
			exit(EXIT_FAILURE);
		}

		scanf("%s", buffer1);
		char* buffer2 = calloc(MAXLINE, sizeof(char));

		if (buffer2 == NULL) {
			perror("calloc failed");
			free(buffer1);
			exit(EXIT_FAILURE);
		}

		sendto(sockfd, (const char *)buffer1, strlen(buffer1), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
		printf("MSG sent\n");
				
		n = recvfrom(sockfd, (char *)buffer2, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		buffer2[n] = '\0';

		printf("Server: %s\n", buffer2);

		if (strcmp(buffer1, "exit") == 0) {
			free(buffer1);
			free(buffer2);
			break;
		} else {
			free(buffer1);
			free(buffer2);
		}
		
	} while (1);
	
	close(sockfd);
	return 0;
}