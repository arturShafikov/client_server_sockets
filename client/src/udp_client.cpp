#include "udp_client.h"

UdpClient::UdpClient(const char* address, int port) : Client(address, port) {
 sckt = socket(AF_INET, SOCK_DGRAM, 0);
 if (sckt < 0) {
  error("ERROR opening socket");
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
  fgets(buffer, 1024, stdin);
  count = sendto(sckt, buffer, strlen(buffer), 0, (struct sockaddr*)&addr_server, addr_len);
  if (count < 0) {
   error("ERROR writing to socket");
  }
  bzero(buffer, 1024);
  count = recvfrom(sckt, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr_server, &addr_len);
  if (count < 0) {
   error("ERROR reading from socket");
  }
  printf("Server response:\n%s\n", buffer);
 }
}
