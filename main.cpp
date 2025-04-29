#include "src/http_server/http_server.h"
#include <vector>
#include <bits/stdc++.h>
#include <cstdlib>

void exiting(int i){
    log::add("program terminating");
    log::close();
    exit(0);
}

int main(){

    log::open("log.txt");

    //^C
    signal(SIGINT, exiting);
    //abort()
    signal(SIGABRT, exiting);
    //sent by "kill" command
    signal(SIGTERM, exiting);
    //^Z
    signal(SIGTSTP, exiting);

    
    HTTPServer myServ("0.0.0.0", 1231);
    myServ.addAPI("/", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/test.html", ".html"), GET);
    myServ.addAPI("/test.css", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/test.css", ".css"), GET);
    myServ.addAPI("/favicon.ico", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/favicon.ico", ".ico"), GET);
    myServ.addAPI("/favicon.png", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/favicon-16x16.png", ".png"), GET);

    Responce::JSON* json = new Responce::JSON();
    (*json)["data"] = "[1,2,13,24,64,3,5,76,100,100,100]";
    (*json)["length"] = "11";
    myServ.addAPI("/data.json", json, GET);
    myServ.addAPI("/action_page", json, POST);

    // static std::vector staticScopeVector = {1,2,3,34,100,26,7,18,9};
    // std::function<std::string()> func_ = []() {
    //     std::stringstream ss;

    //     ss << "HTTP/1.1 200 OK\r\n"
    //     "Content-Type: text/json\r\n"
    //     "\r\n{\n\"data\" : [";

    //     for(int i = 0; i < staticScopeVector.size()-1; i++)
    //         ss << staticScopeVector[i] << ", ";
    //     ss << staticScopeVector[staticScopeVector.size()-1];
    //     ss << "],\n";
    //     ss << "\"length\" : " << staticScopeVector.size() << "\n}";
        
    //     return ss.str();
    // };


    while(true){
        myServ.handleCon();
    }

    log::close();

    return 0;
}