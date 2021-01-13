#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

class Client {
private:
 int sckt;
 const int port;
 const char *address;
 struct sockaddr_in addr_server;
public:
  Client();
  ~Client();
  void init_requesting();
};

#endif
