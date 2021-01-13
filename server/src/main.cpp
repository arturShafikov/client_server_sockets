#include "server.h"
#include "cstdlib"

int main(int argc, char* argv[]) {
  Server server;
  server.init_listening();
  return 0;
}
