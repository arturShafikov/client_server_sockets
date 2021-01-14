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
}

Client::~Client() {
}
