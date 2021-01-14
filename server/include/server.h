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
#include "data_processor.h"

class Server {
private:
 int tcp_socket;//socket for tcp connections
 int udp_socket;//socket for udp connections
 const int port;//server port
 struct sockaddr_in addr_server;//full server address
 DataProcessor data_processor;//object for data processing

 void error(const char *error_msg);
public:
  Server(int port = 8080);
  ~Server();
  void init_listening();
};

#endif
