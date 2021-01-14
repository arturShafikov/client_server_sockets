#include "client.h"
#include "tcp_client.h"
#include "cstdlib"

int main(int argc, char* argv[]) {
  Client* client = new TcpClient();
  client->init_requesting();
  return 0;
}
