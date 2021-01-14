#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "client.h"

class TcpClient : public Client {
private:
 int sckt;
public:
 TcpClient(const char* address = "127.0.0.1", int port = 8080);
 virtual ~TcpClient();
 virtual void init_requesting() override;
};

#endif
