#include "tcp_client.h"

TcpClient::TcpClient(const char* address, int port) : Client(address, port) {
 sckt = socket(AF_INET, SOCK_STREAM, 0);
 if (sckt < 0) {
  error("ERROR opening socket");
 }

 if (connect(sckt, (struct sockaddr*)&addr_server, addr_len) < 0) {
  error("ERROR connecting");
 }
}

TcpClient::~TcpClient() {
 close(sckt);
}

int TcpClient::write_to_socket(int length) {
 return write(sckt, buffer, length);
}

int TcpClient::read_from_socket(int length) {
 return read(sckt, buffer, length);
}
