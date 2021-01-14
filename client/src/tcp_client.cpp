#include "tcp_client.h"

TcpClient::TcpClient(const char* address, int port) : Client(address, port) {
 sckt = socket(AF_INET, SOCK_STREAM, 0);
 if (sckt < 0) {
  perror("ERROR opening socket");
  exit(EXIT_FAILURE);
 }

 if (connect(sckt, (struct sockaddr*)&addr_server, sizeof(addr_server)) < 0) {
  perror("ERROR connecting");
  exit(EXIT_FAILURE);
 }
}

TcpClient::~TcpClient() {
 close(sckt);
}

void TcpClient::init_requesting() {
 int count;
 char buffer[1024];
 while (true) {
  printf("Please enter the message:\n");
  bzero(buffer, 1024);
  count = -1;
  fgets(buffer, 1024, stdin);
  count = write(sckt, buffer, strlen(buffer));
  if (count < 0) {
   perror("ERROR writing to socket");
   exit(EXIT_FAILURE);
  }
  count = read(sckt, buffer, 1024);
  if (count < 0) {
   perror("ERROR reading from socket");
   exit(EXIT_FAILURE);
  }
  printf("Server response:\n%s", buffer);
 }
}
