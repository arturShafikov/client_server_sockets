#include "client.h"

void Client::error(const char *error_msg) {
 perror(error_msg);
 exit(EXIT_FAILURE);
}

Client::Client(const char* address, int port) : address(address), port(port) {

 addr_server.sin_family = AF_INET;
 if (inet_pton(AF_INET, address, &addr_server.sin_addr) <= 0) {
  error("ERROR in address");
 }
 addr_server.sin_port = htons(port);

 addr_len = sizeof(addr_server);
}

Client::~Client() {
}

void Client::init_requesting() {
 int count;
 while (true) {
  printf("Please enter the message:\n");
  bzero(buffer, 1024);
  fgets(buffer, 1024, stdin);
  count = write_to_socket(strlen(buffer));
  if (count < 0) {
   error("ERROR writing to socket");
  }
  bzero(buffer, 1024);
  count = read_from_socket(sizeof(buffer));
  if (count < 0) {
   error("ERROR reading from socket");
  }
  printf("Server response:\n%s\n", buffer);
 }
}
