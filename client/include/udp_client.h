#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include "client.h"

class UdpClient : public Client {
private:
 int sckt;
public:
 UdpClient(const char* address = "127.0.0.1", int port = 8080);
 virtual ~UdpClient();
 virtual void init_requesting() override;
};

#endif
