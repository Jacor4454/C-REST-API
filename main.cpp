#include "src/http_server/http_server.h"
#include <vector>
#include <bits/stdc++.h>

int main(){
    
    HTTPServer myServ("0.0.0.0", 1231);
    myServ.addAPI("/", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/test.html", ".html"));
    myServ.addAPI("/test.css", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/test.css", ".css"));

    static std::vector staticScopeVector = {1,2,3,4,5,6,7,8,9};

    std::function<std::string()> func_ = []() {
        std::stringstream ss;

        ss << "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/json\r\n"
        "\r\n{data: [";

        for(int i : staticScopeVector)
            ss << i << ", ";
        ss << "]}";
        
        return ss.str();
    };

    myServ.addAPI("/data", new Responce::Func(func_));

    while(true){
        myServ.handleCon();
    }

    return 0;
}