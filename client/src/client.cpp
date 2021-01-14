#include "client.h"

Client::Client(const char* address, int port) : address(address), port(port) {

 addr_server.sin_family = AF_INET;
 if (inet_pton(AF_INET, address, &addr_server.sin_addr) <= 0) {
  perror("ERROR in address");
  exit(EXIT_FAILURE);
 }
 addr_server.sin_port = htons(port);
}

Client::~Client() {
}
