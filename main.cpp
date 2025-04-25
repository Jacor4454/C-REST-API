#include "src/http_server/http_server.h"
#include <vector>
#include <bits/stdc++.h>

int main(){
    
    HTTPServer myServ("0.0.0.0", 1231);
    myServ.addAPI("/", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/test.html", ".html"));
    myServ.addAPI("/test.css", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/test.css", ".css"));
    myServ.addAPI("/favicon.ico", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/favicon.ico", ".ico"));
    myServ.addAPI("/favicon.png", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/favicon-16x16.png", ".png"));

    std::unordered_map<std::string, std::string> data;
    data["data"] = "[1,2,13,24,64,3,5,76,100,100,100]";
    data["length"] = "11";
    Responce::JSON* json = new Responce::JSON(&data);
    myServ.addAPI("/data.json", json);

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

    return 0;
}