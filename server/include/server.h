#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <errno.h>
#include <arpa/inet.h>
#include <algorithm>

class Server {
private:
 int tcp_socket;
 int udp_socket;
 const int port;
 struct sockaddr_in addr_server;

public:
  Server();
  ~Server();
  void init_listening();
};

#endif
