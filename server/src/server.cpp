#include "server.h"

void Server::error(const char *error_msg) {
 perror(error_msg);
 exit(EXIT_FAILURE);
}

Server::Server() : port(8080) {

 tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
 if (tcp_socket < 0) {
  error("ERROR opening socket");
 }

 int opt = 1;
 if (setsockopt(tcp_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0) {
  error("ERROR in setting socket opts");
 }

 bzero((char*)&addr_server, sizeof(addr_server));
 addr_server.sin_family = AF_INET;
 addr_server.sin_port = htons(port);
 addr_server.sin_addr.s_addr = INADDR_ANY;

 if (bind(tcp_socket, (struct sockaddr *)&addr_server, sizeof(addr_server)) < 0) {
  error("ERROR on binding tcp socket");
 }

 udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
 if (bind(udp_socket, (struct sockaddr *)&addr_server, sizeof(addr_server)) < 0) {
  error("ERROR on binding udp socket");
 }
}

Server::~Server() {
 close(tcp_socket);
 close(udp_socket);
}

void Server::init_listening() {

 fd_set read_sockets;
 int sckt_client;
 int max_sd;
 int sd;
 int max_clients = 30;
 struct sockaddr_in addr_client;
 int activity;
 char buffer[1024] = {0};
 int count;

 const char* response_message = "Message received. \n";
 socklen_t addr_len = sizeof(addr_client);

 int client_socket[30];
 for (int i = 0; i < max_clients; i++) {
  client_socket[i] = 0;
 }

 listen(tcp_socket, 5);

 while(true) {

  FD_ZERO(&read_sockets);
  FD_SET(tcp_socket, &read_sockets);
  FD_SET(udp_socket, &read_sockets);
  max_sd = std::max(tcp_socket, udp_socket);

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
    continue;
  }

  if (FD_ISSET(tcp_socket, &read_sockets)) {
   if ((sckt_client = accept(tcp_socket, (struct sockaddr*)&addr_client, &addr_len)) < 0) {
    error("ERROR on accept");
   }

   for (int i = 0; i < max_clients; i++) {
    if (client_socket[i] == 0) {
     client_socket[i] = sckt_client;
     break;
    }
   }
  }

  if (FD_ISSET(udp_socket, &read_sockets)) {
   bzero(buffer, sizeof(buffer));
   count = recvfrom(udp_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr_client, &addr_len);
   if (count < 0) {
     error("ERROR reading from socket");
    }
   printf("Received message:\n%s", buffer);
   std::string response = data_processor.process_data(buffer);
   const char* resp_c = response.c_str();
   count = sendto(udp_socket, resp_c, strlen(resp_c), 0, (struct sockaddr*)&addr_client, addr_len);
   if (count < 0) {
    error("ERROR writing to socket");
   }
  }

  for (int i = 0; i < max_clients; i++) {
   sd = client_socket[i];
   
   if (FD_ISSET(sd, &read_sockets)) {
    bzero(buffer, sizeof(buffer));
    count = read(sd, buffer, 1024);
    if (count == 0) {
     close(sd);
     client_socket[i] = 0;
    } else {
     printf("Received message:\n%s", buffer);
     std::string response = data_processor.process_data(buffer);
     const char* resp_c = response.c_str();
     count = write(sd, resp_c, strlen(resp_c));
     if (count < 0) {
      error("ERROR writing to socket");
     }
    }
   }
  }

 }
}
