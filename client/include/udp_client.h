#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include "client.h"

//Udp client class
class UdpClient : public Client {
private:
 int sckt; //socket
 virtual int write_to_socket(int length) override;
 virtual int read_from_socket(int length) override;
public:
 UdpClient(const char* address = "127.0.0.1", int port = 8080);
 virtual ~UdpClient();
};

#endif
