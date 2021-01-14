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
 const int port;
 const char *address;
protected:
 struct sockaddr_in addr_server;
 void error(const char *error_msg);
public:
  Client(const char* address, int port);
  virtual ~Client();
  virtual void init_requesting() = 0;
};

#endif
