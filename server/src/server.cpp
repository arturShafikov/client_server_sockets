#include "server.h"

Server::Server() : port(8080) {

 sckt_server = socket(AF_INET, SOCK_STREAM, 0);
 if (sckt_server < 0) {
  perror("ERROR opening socket");
  exit(EXIT_FAILURE);
 }

 int opt = 1;
 if (setsockopt(sckt_server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0) {
  perror("ERROR in setting socket opts");
  exit(EXIT_FAILURE);
 }

 bzero((char*)&addr_server, sizeof(addr_server));
 addr_server.sin_family = AF_INET;
 addr_server.sin_port = htons(port);
 addr_server.sin_addr.s_addr = INADDR_ANY;

 if (bind(sckt_server, (struct sockaddr *)&addr_server, sizeof(addr_server)) < 0) {
  perror("ERROR on binding");
  exit(EXIT_FAILURE);
 } 
}

Server::~Server() {
 close(sckt_server);
}

void Server::init_listening() {

 int count;
 char buffer[1024];
 struct sockaddr_in addr_client;
 int sckt_client;

 listen(sckt_server, 5);

 int addr_len = sizeof(addr_client);
 while(std::strcmp(buffer, "exit") != 0) {
  sckt_client = -1;
  bzero((char*)&addr_client, addr_len);
  count = -1;

  sckt_client = accept(sckt_server, (struct sockaddr*)&addr_client, (socklen_t*)&addr_len);
  printf("WOW\n");
  if (sckt_client < 0) {
   perror("ERROR on accept");
   exit(EXIT_FAILURE);
  }
 
  bzero(buffer, 1024);
  count = read(sckt_client, buffer, 1024);
  if (count < 0) {
   perror("ERROR reading from socket");
   exit(EXIT_FAILURE);
  }
  printf("Received message:\n%s", buffer);

  count = write(sckt_client, "Message received\n", 16);
  if (count < 0) {
   perror("ERROR writing to socket");
   exit(EXIT_FAILURE);
  }
 }
 
 close(sckt_client);
}
