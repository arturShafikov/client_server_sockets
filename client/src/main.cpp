#include "client.h"
#include "tcp_client.h"
#include "udp_client.h"
#include <string>

int main(int argc, char* argv[]) {
  Client* client;
  if (argc < 2) {
   printf("Client type is not specified. Starting TCP client...\n");
   client = new TcpClient();
  } else if (std::string(argv[1]) == "tcp") {
   printf("Starting TCP client...\n");
   client = new TcpClient();
  } else if (std::string(argv[1]) == "udp") {
   printf("Starting UDP client...\n");
   client = new UdpClient();
  } else {
   printf("Client type is invalid. Starting TCP client...\n");
   client = new TcpClient();
  }
  client->init_requesting();
  return 0;
}
