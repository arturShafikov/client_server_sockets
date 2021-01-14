#include "tcp_client.h"

TcpClient::TcpClient(const char* address, int port) : Client(address, port) {
 sckt = socket(AF_INET, SOCK_STREAM, 0);
 if (sckt < 0) {
  error("ERROR opening socket");
 }

 if (connect(sckt, (struct sockaddr*)&addr_server, sizeof(addr_server)) < 0) {
  error("ERROR connecting");
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
  fgets(buffer, 1024, stdin);
  count = write(sckt, buffer, strlen(buffer));
  if (count < 0) {
   error("ERROR writing to socket");
  }
  bzero(buffer, 1024);
  count = read(sckt, buffer, 1024);
  if (count < 0) {
   error("ERROR reading from socket");
  }
  printf("Server response:\n%s\n", buffer);
 }
}
