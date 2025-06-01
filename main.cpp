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

    
    HTTPServer myServ("0.0.0.0", 1237);
    myServ.addAPI("/", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/test.html", ".html"), GET);
    myServ.addAPI("/test.css", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/test.css", ".css"), GET);
    myServ.addAPI("/favicon.ico", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/favicon.ico", ".ico"), GET);
    myServ.addAPI("/favicon.png", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/favicon-16x16.png", ".png"), GET);
    myServ.addAPI("/other.svg", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/src/svg/test.svg", ".svg"), GET);

    Responce::JSON* json = new Responce::JSON();
    (*json)["data"] = "[1,2,13,24,64,3,5,76,100,100,100]";
    (*json)["length"] = "11";
    myServ.addAPI("/data.json", json, GET);
    myServ.addAPI("/action_page", json, POST);

    SVG svg;
    PolyLine pl({{0,0},{10,10},{50,90},{600,0}});
    pl.stroke.raw = 0;
    pl.fill.H = 1;
    svg.add(&pl);
    RoundedRect rr({100,100}, {20,20}, {200, 100});
    rr.stroke.R = 255;
    rr.fill.raw = 0;
    rr.fill.B = 255;
    svg.add(&rr);
    RoundedRect rr1({100,100}, {4,4}, {40, 20});
    rr1.stroke.R = 255;
    rr1.fill.raw = 0;
    rr1.fill.B = 255;
    svg.add(&rr1);
    Text t("Hello", {40,400}, 35);
    t.stroke.H = 1;
    t.fill.raw = 0;
    t.fill.G=200;
    svg.add(&t);
    RoundedLine rl({{600,700},{600,500},{50,500},{50,700},{200,700}}, 25);
    rl.stroke.R = 255;
    rl.fill.H = 1;
    svg.add(&rl);
    WordBubble wb({500,500},"Title","footer");
    wb.bubble.stroke.B = 250;
    wb.bubble.fill.raw = 0x8080c0;
    svg.add(&wb);
    myServ.addAPI("/pic.svg", new Responce::TextRest(svg.get(),".svg"), GET);

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