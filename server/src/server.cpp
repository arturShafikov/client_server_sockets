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

 fd_set read_sockets;
 int max_clients = 30;
 int client_socket[30];
 struct sockaddr_in addr_client;
 int sckt_client;
 int max_sd;
 int sd;
 int activity;
 char buffer[1024] = {0};
 int count;

 const char* welcome_message = "Welcome to the server.\n";
 const char* response_message = "Message received.\n";

 for (int i = 0; i < max_clients; i++) {
  client_socket[i] = 0;
 }

 listen(sckt_server, 5);

 socklen_t addr_len = sizeof(addr_client);
 int pid;
 while(true) {

  FD_ZERO(&read_sockets);
  FD_SET(sckt_server, &read_sockets);
  max_sd = sckt_server;

  for (int i = 0; i < max_clients; i++) {
   sd = client_socket[i];

   if (sd > 0) {
    FD_SET(sd, &read_sockets);
   }

   if (sd > max_sd) {
    max_sd = sd;
   }
  }

  activity = select(max_sd+1, &read_sockets, NULL, NULL, NULL);

  if ((activity < 0) && (errno!=EINTR)) {
    printf("Select error\n");
  }

  if (FD_ISSET(sckt_server, &read_sockets)) {
   if ((sckt_client = accept(sckt_server, (struct sockaddr*)&addr_client, &addr_len)) < 0) {
    perror("ERROR on accept");
    exit(EXIT_FAILURE);
   }

   printf("New connection:\nsocket - %d\nip - %s\nport - %d\n", sckt_client, inet_ntoa(addr_client.sin_addr), ntohs(addr_client.sin_port));

   if (write(sckt_client, welcome_message, strlen(welcome_message)) != strlen(welcome_message)) {
    perror("ERROR in writing welcoming message");
   }

   for (int i = 0; i < max_clients; i++) {
    if (client_socket[i] == 0) {
     client_socket[i] = sckt_client;
     printf("Adding to the list of sockets as %d\n", i);
     break;
    }
   }
  }

  for (int i = 0; i < max_clients; i++) {
   sd = client_socket[i];
   
   if (FD_ISSET(sd, &read_sockets)) {
    count = read(sd, buffer, 1024);
    if (count == 0) {
     printf("Disconnected...");
     close(sd);
     client_socket[i] = 0;
    } else {
     printf("Received message:\n%s", buffer);
     count = write(sd, "Message received\n", 16);
     if (count < 0) {
      perror("ERROR writing to socket");
      exit(EXIT_FAILURE);
     }
    }
   }
  }
 }
}

void Server::generate_response(int sckt) {

 int count;
 char buffer[1024] = {0};

 count = read(sckt, buffer, 1024);
 if (count < 0) {
  perror("ERROR reading from socket");
  exit(EXIT_FAILURE);
 }
 printf("Received message:\n%s", buffer);

 count = write(sckt, "Message received\n", 16);
 if (count < 0) {
  perror("ERROR writing to socket");
  exit(EXIT_FAILURE);
 }
}
