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

int UdpClient::write_to_socket(int length) {
 return sendto(sckt, buffer, length, 0, (struct sockaddr*)&addr_server, addr_len);
}

int UdpClient::read_from_socket(int length) {
 return recvfrom(sckt, buffer, length, 0, (struct sockaddr*)&addr_server, &addr_len);
}
