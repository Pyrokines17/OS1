#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 5668
#define MAX 1024
#define MAX_CLIENTS 5

int main() {
  char* ip = "127.0.0.1";
  int port = PORT;

  int server_sock, client_sock;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size;

  char buffer[MAX];
  int n;

  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock < 0) {
    perror("[-]Socket error");
    exit(EXIT_FAILURE);
  } else printf("[+]TCP server socket created.\n");

  memset(&server_addr, '\0', sizeof(server_addr));
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
  
  if (n < 0){
    perror("[-]Bind error");
    exit(EXIT_FAILURE);
  } printf("[+]Bind to the port number: %d\n", port);

  listen(server_sock, MAX_CLIENTS);
  printf("Listening...\n");

  while(1) {
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    printf("[+]Client connected.\n");

	  pid_t res = fork();

    if (res == -1) {
      perror("Error in fork");
      exit(EXIT_FAILURE);
    } else if (res == 0) {
        while(1) {
        bzero(buffer, MAX);

        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("Client: %s\n", buffer);

        if (strcmp(buffer, "quit") == 0) {
          printf("Received quit command. Disconnecting client.\n");
          break;
        }

        printf("Server: %s\n", buffer);
        send(client_sock, buffer, strlen(buffer), 0);
      }

      close(client_sock);
      printf("[+]Client disconnected.\n\n");
    } 
  }

  return 0;
}
