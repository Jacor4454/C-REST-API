#ifndef CLASS_HTTP_H
#define CLASS_HTTP_H

#include <sys/socket.h>
#include <sys/time.h>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <unordered_map>

#include "APIresponces/Base.h"
#include "APIresponces/File.h"
#include "APIresponces/Func.h"
#include "APIresponces/FakeSON.h"

#include "../logging/logging.h"

typedef enum{
    GET,
    POST,
    PUT,
    DELETE
} APIActions;

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
    std::unordered_map<std::string, Responce::Base*> GET;
    std::unordered_map<std::string, Responce::Base*> POST;

    public:
    HTTPServer(std::string, int);
    ~HTTPServer();

    void handleCon();
    void POSTurlEncoded(std::unordered_map<std::string, std::string>& headers, int clientSocket, Responce::Base* thing);
    void respond(Responce::Base* thing, int clientSocket);
    void addAPI(std::string, Responce::Base*, APIActions);
};

#endif