#include "udp_client.h"

UdpClient::UdpClient(const char* address, int port) : Client(address, port) {
 sckt = socket(AF_INET, SOCK_DGRAM, 0);
 if (sckt < 0) {
  perror("ERROR opening socket");
  exit(EXIT_FAILURE);
 }
}

UdpClient::~UdpClient() {
 close(sckt);
}

void UdpClient::init_requesting() {
 int count;
 char buffer[1024];
 socklen_t addr_len = sizeof(addr_server);
 while (true) {
  printf("Please enter the message:\n");
  bzero(buffer, 1024);
  count = -1;
  fgets(buffer, 1024, stdin);
  count = sendto(sckt, buffer, strlen(buffer), 0, (struct sockaddr*)&addr_server, addr_len);
  if (count < 0) {
   perror("ERROR writing to socket");
   exit(EXIT_FAILURE);
  }
  bzero(buffer, 1024);
  count = recvfrom(sckt, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr_server, &addr_len);
  if (count < 0) {
   perror("ERROR reading from socket");
   exit(EXIT_FAILURE);
  }
  printf("Server response:\n%s\n", buffer);
 }
}
