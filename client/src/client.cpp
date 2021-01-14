#include "client.h"

Client::Client() : address("127.0.0.1"), port(8080) {

 struct hostent *server;

 sckt = socket(AF_INET, SOCK_STREAM, 0);
 if (sckt < 0) {
  perror("ERROR opening socket");
  exit(EXIT_FAILURE);
 }

 server = gethostbyname("localhost");
 if (server = nullptr) {
  perror("ERROR finding the server");
  exit(EXIT_FAILURE);
 }

 bzero((char *) &addr_server, sizeof(addr_server));
 addr_server.sin_family = AF_INET;
 if (inet_pton(AF_INET, address, &addr_server.sin_addr) <= 0) {
  perror("ERROR in address");
  exit(EXIT_FAILURE);
 }
 addr_server.sin_port = htons(port);

 if (connect(sckt, (struct sockaddr*)&addr_server, sizeof(addr_server)) < 0) {
  perror("ERROR connecting");
  exit(EXIT_FAILURE);
 }
}

Client::~Client() {
 close(sckt);
}

void Client::init_requesting() {
 int count;
 char buffer[1024];
 while (true) {
  printf("Please enter the message:\n");
  bzero(buffer, 1024);
  count = -1;
  fgets(buffer, 1024, stdin);
  count = write(sckt, buffer, strlen(buffer));
  if (count < 0) {
   perror("ERROR writing to socket");
   exit(EXIT_FAILURE);
  }
  count = read(sckt, buffer, 1024);
  if (count < 0) {
   perror("ERROR reading from socket");
   exit(EXIT_FAILURE);
  }
  printf("Server response:\n%s", buffer);
 }
}
