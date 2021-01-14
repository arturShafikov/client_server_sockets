#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "client.h"

class TcpClient : public Client {
private:
 int sckt;
 virtual int write_to_socket(int length) override;
 virtual int read_from_socket(int length) override;
public:
 TcpClient(const char* address = "127.0.0.1", int port = 8080);
 virtual ~TcpClient();
};

#endif
