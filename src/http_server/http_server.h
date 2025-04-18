#ifndef CLASS_HTTP_H
#define CLASS_HTTP_H

#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

class HTTPServer{
    std::string ipAddress;
    int port;
    int serverSocket;
    long incomingMessage;
    sockaddr_in serverAddress;
    unsigned int serverAddressLen;
    std::string serverMessage;

    public:
    HTTPServer(std::string ip_address, int port);
    ~HTTPServer();
};

#endif