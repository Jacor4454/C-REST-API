#include "http_server.h"

int isEndBuffer(char* buffer, int len){
    const char strmatch[] = "\r\n\r\n";

    for(int i = 0; i < len-4; i++){
        int j;
        for(j = 0; j < 4; j++){
            if(buffer[i+j] != strmatch[j])
                break;
        }
        if(j == 4)
            return i;
    }

    return -1;
}

HTTPServer::HTTPServer(std::string ipAddress_, int port_):
    ipAddress(ipAddress_),
    port(port_),
    incomingMessage(),
    serverAddressLen(sizeof(serverAddress))
{
    // make socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0)
        throw std::runtime_error("cannot bind to socket");

    // define parameters
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // bind
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // test
    listen(serverSocket, 5);

}

HTTPServer::~HTTPServer(){
    close(serverSocket);

    for(auto& [k, v] : lookup)
        delete v;
}

void HTTPServer::addAPI(std::string path, Responce::Base* pointer){
    lookup[path] = pointer;
}

void HTTPServer::handleCon(){
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if(clientSocket < 0)
        throw std::runtime_error("accept failed to create conntection");
    
    #define b_len 1024
    char buffer[b_len] = {0};
    std::stringstream ss;
    int cIndex = -1;
    while(cIndex == -1){
        // recieve some stoof
        recv(clientSocket, buffer, sizeof(buffer), 0);

        // is end of headers?
        cIndex = isEndBuffer(buffer, b_len);
        if(cIndex != -1)
            buffer[cIndex+4] = 0x0;
        ss << buffer;
    }

    std::unordered_map<std::string, std::string> headers;

    std::string req;
    std::getline(ss, req);

    std::cout << req << "\n";

    std::string s;
    std::string s1;
    char c;
    while(std::getline(ss, s, ':') && s != "\r\n"){
        std::getline(ss, s1, '\n');
        headers[s] = s1;
    }

    std::stringstream ss1(req);
    std::string RESTtype;
    std::string RESTpath;
    std::string RESThttp;
    std::getline(ss1, RESTtype, ' ');
    std::getline(ss1, RESTpath, ' ');
    std::getline(ss1, RESThttp, '\n');

    if(RESTtype != "GET")
        throw std::runtime_error("incompatable to GET");

    Responce::Base* thing = lookup[RESTpath];

    std::vector<unsigned char> message;

    if(thing == nullptr){
        // send responce
        std::string s = 
        "HTTP/1.1 404 OK\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n"
        "404 Not Found";
        message.insert(message.end(), s.begin(), s.end());
    } else {
        message = thing->Get();
    }
    
    send(clientSocket, message.data(), message.size() * sizeof(unsigned char), 0);
    close(clientSocket);
}
