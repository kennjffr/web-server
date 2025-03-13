#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>

#define PORT 80

int main() {

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0) {
    perror("socket");
    return 1;
  }

  printf("socket success\n");

  struct sockaddr_in address;
  int address_len = sizeof(address);

  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  address.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sockfd, (struct sockaddr *)&address, address_len) < 0) {
    perror("bind");
  }
  printf("bind success\n");
 
  if (listen(sockfd, SOMAXCONN) < 0) {
    perror("listen");
  }
  printf("listening");

  for (;;) {
    int listensockfd = accept(sockfd, (struct sockaddr *)&address, (struct socklen_t *) &address_len);

    if (listensockfd < 0) {
      perror("accept fail");
      continue;
    }
    printf("connection accepted\n");

    close(listensockfd);
  }

  return 0;
}