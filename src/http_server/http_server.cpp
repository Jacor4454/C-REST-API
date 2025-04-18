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
        std::cout << "fail1\n";

    // define parameters
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // bind
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // test
    listen(serverSocket, 5);
    std::cout << "listerning...\n";
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if(clientSocket < 0)
        std::cout << "fail2\n";
    std::cout << "connected\n";
    #define b_len 1024
    char buffer[b_len] = {0};
    std::stringstream ss;
    std::cout << "recieving...\n";
    int packetindex = 0;
    int cIndex = -1;
    while(cIndex == -1){
        std::cout << "loading packet: " << packetindex << "\n";
        packetindex++;

        recv(clientSocket, buffer, sizeof(buffer), 0);
        cIndex = isEndBuffer(buffer, b_len);

        if(cIndex != -1)
            buffer[cIndex+4] = 0x0;
        ss << buffer;
    }
    std::cout << "Message from client: " << ss.str() << std::endl;

    const char* message = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/plain\r\n"
    "\r\n"
    "Hello"
    ;
    send(clientSocket, message, strlen(message), 0);

}

HTTPServer::~HTTPServer(){
    close(serverSocket);
}
