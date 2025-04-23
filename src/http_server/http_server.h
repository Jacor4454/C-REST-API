#ifndef CLASS_HTTP_H
#define CLASS_HTTP_H

#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <unordered_map>

#include "APIresponces/Base.h"
#include "APIresponces/File.h"
#include "APIresponces/Func.h"

class HTTPServer{
    // networking things
    std::string ipAddress;  
    int port;
    int serverSocket;
    long incomingMessage;
    sockaddr_in serverAddress;
    unsigned int serverAddressLen;
    std::string serverMessage;

    // responce things
    std::unordered_map<std::string, Responce::Base*> lookup;

    public:
    HTTPServer(std::string, int);
    ~HTTPServer();

    void handleCon();
    void addAPI(std::string, Responce::Base*);
};

#endif