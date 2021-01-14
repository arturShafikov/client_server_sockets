#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
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
 char buffer[1024];
 socklen_t addr_len;

 void error(const char *error_msg);
 virtual int write_to_socket(int length) = 0;
 virtual int read_from_socket(int length) = 0;
public:
  Client(const char* address, int port);
  virtual ~Client();
  void init_requesting();
};

#endif
