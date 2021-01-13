#include "server.h"
#include <signal.h>

int main(int argc, char* argv[]) {
  signal(SIGCHLD, SIG_IGN);
  Server server;
  server.init_listening();
  return 0;
}
