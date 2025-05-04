#include "http_server.h"

bool isEndBuffer(std::stringstream& ss){
    const char strmatch[] = "\r\n\r\n";
    std::string s = ss.str();
    int len = s.size();

    for(int i = 0; i < 4; i++){
        if(s[len-4+i] != strmatch[i])
            return false;
    }
    return true;
}

HTTPServer::HTTPServer(std::string ipAddress_, int port_):
    ipAddress(ipAddress_),
    port(port_),
    incomingMessage(),
    serverAddressLen(sizeof(serverAddress))
{
    if(port < 0)
        return;
    
    // make socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0)
        throw std::runtime_error("cannot bind to socket");

    std::stringstream ss;
    ss << "server initialized on port: " << port;
    log::add(ss.str());

    // define parameters
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // bind
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    fcntl(serverSocket, F_SETFL, O_NONBLOCK);

    // start listening
    listen(serverSocket, 10);
    log::add("listening");
}

HTTPServer::~HTTPServer(){
    if(port >= 0)
        close(serverSocket);

    for(auto& [k, v] : GET)
        delete v;
    for(auto& [k, v] : POST)
        delete v;
}

void HTTPServer::addAPI(std::string path, Responce::Base* pointer, APIActions a){
    switch(a){
        case APIActions::GET:
            GET[path] = pointer;
            break;
        case APIActions::POST:
            POST[path] = pointer;
            break;
        // case APIActions::PUT:
        //     lookup[path] = pointer;
        // case APIActions::DELETE:
        //     lookup[path] = pointer;
        default:
            throw std::runtime_error("invalid API action");
    }
}

void HTTPServer::handleCon(){
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    
    if(clientSocket < 0){
        // throw std::runtime_error("accept failed to create conntection");
        // as is non blocking check a few errors and return
        if(errno != EAGAIN && errno != EWOULDBLOCK)
            throw std::runtime_error("accept failed");
        
        return;
    }

    log::add("contact");
    
    char buffer[2] = {0};
    std::stringstream ss;
    bool endIndex = false;
    while(!endIndex){
        // recieve some stoof
        recv(clientSocket, buffer, 1, 0);
        buffer[1] = 0x0;
        ss << buffer;

        // is end of headers?
        endIndex = isEndBuffer(ss);
    }

    std::unordered_map<std::string, std::string> headers;

    std::string req;
    std::getline(ss, req);

    log::add(req);

    std::string s;
    std::string s1;
    char c;
    while(std::getline(ss, s, ':') && s != "\r\n"){
        ss.ignore(1); // ignore whitespace
        std::getline(ss, s1, '\r');
        ss.ignore(1); // ignore newline
        headers[s] = s1;
    }

    std::stringstream ss1(req);
    std::string RESTtype;
    std::string RESTpath;
    std::string RESThttp;
    std::getline(ss1, RESTtype, ' ');
    std::getline(ss1, RESTpath, ' ');
    std::getline(ss1, RESThttp, '\n');
    
    Responce::Base* thing = POST[RESTpath];

    if(RESTtype == "GET"){
        Responce::Base* thing = GET[RESTpath];
        respond(thing, clientSocket);
    }
    if(RESTtype == "POST"){
        // get contents
        if(headers["Content-Type"] == "application/x-www-form-urlencoded"){
            POSTurlEncoded(headers, clientSocket, thing);
        } else {
            log::add("unsupported Content-Type: " + headers["Content-Type"]);
        }
        // respond
        respond(thing, clientSocket);
    }

    close(clientSocket);
}

void HTTPServer::POSTurlEncoded(std::unordered_map<std::string, std::string>& headers, int clientSocket, Responce::Base* thing){

    // get content length
    int con_len = std::atoi(headers["Content-Length"].c_str());

    std::stringstream ss3;
    std::string req;
    req.resize(con_len);
    recv(clientSocket, &req[0], con_len, 0);
    log::add(req);
    
    if(thing == nullptr){
        log::add("invalid path in POST");
        return;
    }

    // convert to hashmap
    std::unordered_map<std::string, std::string> m_req;
    char c = req[0];
    int i = 0;
    while(c != 0x0){
        std::stringstream key;
        std::stringstream value;
        while(c != '='){
            if(c == '%'){
                char cache = 0;
                i++;
                cache = req[i];
                if(cache >= '0' && cache <= '9') cache -= '0';
                else cache -= 'A' - 10;
                cache << 4;
                i++;
                c = req[i];
                if(c >= '0' && c <= '9') c -= '0';
                else c -= 'A' - 10;
                c += cache;
            }
            key << c;
            i++;
            c = req[i];
        }
        i++;
        c = req[i];
        while(c != '&' && c != 0x0){
            if(c == '%'){
                char cache = 0;
                i++;
                cache = req[i];
                if(cache >= '0' && cache <= '9') cache -= '0';
                else cache -= 'A' - 10;
                cache <<= 4;
                i++;
                c = req[i];
                if(c >= '0' && c <= '9') c -= '0';
                else c -= 'A' - 10;
                c += cache;
            }
            value << c;
            i++;
            c = req[i];
        }
        m_req[key.str()] = value.str();
        if(c == '&'){
            i++;
            c = req[i];
        }
    }
    
    thing->Post(m_req);
}

void HTTPServer::respond(Responce::Base* thing, int clientSocket){
    std::vector<unsigned char> message;

    if(thing == nullptr){
        // send responce
        log::add("invalid request");
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
}
